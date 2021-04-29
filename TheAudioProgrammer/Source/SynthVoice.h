#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"


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

    void update(const float attack, const float decay, const float sustain, const float release);           //serve per fare l'update di tutti i parametri
    
    OscData& getOscillator() { return osc; }        // questo serve a comunicare con la funzione OscData che contiene tutti i parametri degli oscillatori


    float delta2;
    float delta3;
    float delta4;

private:

    // Classi per ADSR
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;   //creo un nuovo buffer vuoto in modo tale da evitare i "click" generati assieme alle note.
                     
    // Creo classe che gestisce l'oscillatore principale
    OscData osc;
    juce::dsp::Gain<float> gain;

    /*
    // Oscillatori additivi
    OscData osc2;
    juce::dsp::Gain<float> gain2;
    OscData osc3;
    juce::dsp::Gain<float> gain3;
    OscData osc4;
    juce::dsp::Gain<float> gain4;
    */

    bool isPrepared = false;    //serve a stabilire che il synt è pronto a funzionare

    /*
    //secondo oscillatore
    juce::dsp::Oscillator<float> osc2{ [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain2;

    //terzo oscillatore
    juce::dsp::Oscillator<float> osc3{ [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain3;

    //quarto oscillatore
    juce::dsp::Oscillator<float> osc4{ [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain4;
    */
};