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
    void updateADSR(const float attack, const float decay, const float sustain, const float release);           //serve per controllare l'ADSR

private:
    // Classi per ADSR
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    juce::AudioBuffer<float> synthBuffer;   //creo un nuovo buffer vuoto in modo tale da evitare i "click" generati assieme alle note.
                                            //Questi sono dovuti al fatto che la fase della sinusoide non è perfettamente a zero quando premo la nota.
                                            // 
    // Classi per l'oscillatore
    juce::dsp::Oscillator<float> osc { [] (float x) {return std::sin(x); }};
    juce::dsp::Gain<float> gain;

    bool isPrepared = false;    //serve a stabilire che il synt è pronto a funzionare

    //return std:sin (x); //Sine Wave
    // return x /MathConstants<float>::pi; //Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f; // Square Wave
};