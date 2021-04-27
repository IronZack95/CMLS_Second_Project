/*
  ==============================================================================

    SynthVoice.cpp
    Created: 27 Apr 2021 12:19:29am
    Author:  Zack

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));  // qui dico di controllare qual'è la nota in ingresso e settare la frequenza dell'oscillatore su quella
    adsr.noteOn(); //qui è dove inizia l'envelope dell'ADSR
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff(); //qui è dove finisce l'envelope dell'ADSR
}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{


}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{ 
    adsr.setSampleRate(sampleRate);     //inizializzo l'ADSR

    juce::dsp::ProcessSpec spec;        //Inizializzo il suono dell'Oscillatore
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);
    gain.prepare(spec);

    osc.setFrequency(220.0f);
    gain.setGainLinear(0.01f);

    isPrepared = true; // ok siamo pronti a partire
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared); //serve a stabilire che se la variabile non è stata eseguita il progetto si ferma


    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };            //Renderizzo il prossimo audio Block
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples); // dopo che ho caricatro il buffer di uscita con l'output desiderato applico l'ADSR

}
