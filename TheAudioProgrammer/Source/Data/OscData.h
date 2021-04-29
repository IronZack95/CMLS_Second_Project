/*
  ==============================================================================

    OscData.h
    Created: 28 Apr 2021 6:25:32pm
    Author:  Zack

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int MidiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
};