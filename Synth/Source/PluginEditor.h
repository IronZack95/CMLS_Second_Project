/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& audioProcessor;

    juce::Slider Amp1;
    juce::Slider Amp2;
    juce::Slider Amp3;
    juce::Slider Amp4;
    juce::Label AmpLabel1;
    juce::Label AmpLabel2;
    juce::Label AmpLabel3;
    juce::Label AmpLabel4;

    juce::Slider Freq2;
    juce::Slider Freq3;
    juce::Slider Freq4;
    juce::Label FreqLabel2;
    juce::Label FreqLabel3;
    juce::Label FreqLabel4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
