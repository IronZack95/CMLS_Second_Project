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
    prepare (spec);
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
            initialise([](float x) {return std::sin(x); });
            break;
        case 1:
            // Saw Wave
            initialise([](float x) {return x / juce::MathConstants<float>::pi; });
            break;
        case 2:
            // Square Wave
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse;       // se la scelta non è stata fatta blocca l'esecuzione
            break;
    }

}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));  // qui dico di controllare qual'è la nota in ingresso e settare la frequenza dell'oscillatore su quella

}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float> (block));
}