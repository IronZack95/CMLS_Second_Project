/*
  ==============================================================================

    SynthVoice.h
    Created: 27 Apr 2021 12:19:29am
    Author:  Zack

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

private:
    // Classi per ADSR
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    // Classi per l'oscillatore
    juce::dsp::Oscillator<float> osc { [] (float x) {return std::sin(x); }};
    juce::dsp::Gain<float> gain;

    bool isPrepared = false;    //serve a stabilire che il synt è pronto a funzionare

    //return std:sin (x); //Sine Wave
    // return x /MathConstants<float>::pi; //Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f; // Square Wave
};