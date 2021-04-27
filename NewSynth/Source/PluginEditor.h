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
    
    void setSliderParams(juce::Slider& slider);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::ComboBox oscSelector;
    
    // vado ad attaccare i valori dei parametri agli stlider nella UI

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;

    SynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};