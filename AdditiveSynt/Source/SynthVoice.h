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
    void updateDelta(const float delta);
    void updateGain(const float gain);
    
    OscData& getOscillator() { return oscillatore; }        // questo serve a comunicare con la funzione OscData che contiene tutti i parametri degli oscillatori

    float delta_freq;

private:

    AdsrData adsr;                          // Creo oggetto ADSR
    juce::AudioBuffer<float> synthBuffer;   //creo un nuovo buffer vuoto in modo tale da evitare i "click" generati assieme alle note.
                     
    OscData oscillatore;                    // Creo oggetto OSCILLATORE --> contiene dati sia della Frequenza che di Gain

    bool isPrepared = false;    //serve a stabilire che il synt è pronto a funzionare

};