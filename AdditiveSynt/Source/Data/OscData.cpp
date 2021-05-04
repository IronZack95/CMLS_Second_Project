/*
  ==============================================================================

    OscData.cpp
    Created: 28 Apr 2021 6:25:32pm
    Author:  Zack

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) 
{
    osc.prepare (spec);
    gain.prepare(spec);
}

void OscData::setWaveType(const int choice)
{
    //return std:sin (x); //Sine Wave
    // return x /MathConstants<float>::pi; //Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f; // Square Wave

    switch (choice) 
    {
        case 0:
            // Sine Wave
            osc.initialise([](float x) {return std::sin(x); });
            break;
        case 1:
            // Saw Wave
            osc.initialise([](float x) {return x / juce::MathConstants<float>::pi; });
            break;
        case 2:
            // Square Wave
            osc.initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse;       // se la scelta non è stata fatta blocca l'esecuzione
            break;
    }

}

void OscData::setWaveFrequency(const int midiNoteNumber, const float delta)
{
    lastMidiNote = midiNoteNumber;
    double MainFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    double newFreq = MainFreq * std::pow((double)2.0f, (double)delta / 12);         // secondo la formula Freq = note*s^(N/12)
    osc.setFrequency(newFreq);  // qui dico di controllare qual'è la nota in ingresso e settare la frequenza dell'oscillatore su quella

}

void OscData::setWaveFrequencyRuntime(const float delta) {

    setWaveFrequency(lastMidiNote, delta);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    osc.process(juce::dsp::ProcessContextReplacing<float> (block));
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setGain(float newGain)
{
    gain.setGainLinear(newGain);
}