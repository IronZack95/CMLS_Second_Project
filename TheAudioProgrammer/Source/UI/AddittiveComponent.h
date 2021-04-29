/*
  ==============================================================================

    AddittiveComponent.h
    Created: 28 Apr 2021 9:40:37pm
    Author:  Zack

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AddittiveComponent  : public juce::Component
{
public:
    AddittiveComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AddittiveComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setSliderParams(juce::Slider& slider);

    juce::Slider freq2Slider;
    juce::Slider freq3Slider;
    juce::Slider freq4Slider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; 

    std::unique_ptr<SliderAttachment> freq2Attachment;
    std::unique_ptr<SliderAttachment> freq3Attachment;
    std::unique_ptr<SliderAttachment> freq4Attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddittiveComponent)
};
