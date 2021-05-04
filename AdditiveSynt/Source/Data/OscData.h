/*
  ==============================================================================

    OscData.h
    Created: 28 Apr 2021 6:25:32pm
    Author:  Zack

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

// Questa classe è figlia sia di Oscillatr DSP che di Gain DSP così posso controllare in maniera unica i driver dei miei oscillatori

class OscData : public juce::dsp::Oscillator<float>, public juce::dsp::Gain<float>
{
public:
    // Variabili di OSC
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int MidiNoteNumber, const float delta);
    void setWaveFrequencyRuntime(const float delta);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

    // Variabili di GAIN
    void setGain(float newGain);

private:
    int lastMidiNote;
    juce::dsp::Oscillator<float> osc;       //creo oscillatore e relativo gain
    juce::dsp::Gain<float> gain;
};