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
class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& audioProcessor;

    juce::Slider Amp1;
    juce::Slider Amp2;
    juce::Slider Amp3;
    juce::Slider Amp4;
    juce::Label LabelAmp1;
    juce::Label LabelAmp2;
    juce::Label LabelAmp3;
    juce::Label LabelAmp4;

    juce::Slider Delta2;
    juce::Slider Delta3;
    juce::Slider Delta4;
    juce::Label LabelDelta2;
    juce::Label LabelDelta3;
    juce::Label LabelDelta4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthAudioProcessorEditor)
};
