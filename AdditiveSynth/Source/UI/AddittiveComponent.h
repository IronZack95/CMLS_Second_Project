/*
  ==============================================================================

    AddittiveComponent.h
    Created: 28 Apr 2021 9:40:37pm
    Author:  Zack

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StyleData.h"

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

    void setSliderParams(juce::Slider& slider, RotaryStyle& rot);

    juce::Slider freq2Slider;
    juce::Slider freq3Slider;
    juce::Slider freq4Slider;

    juce::Slider Gain1;
    juce::Slider Gain2;
    juce::Slider Gain3;
    juce::Slider Gain4;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; 

    std::unique_ptr<SliderAttachment> freq2Attachment;
    std::unique_ptr<SliderAttachment> freq3Attachment;
    std::unique_ptr<SliderAttachment> freq4Attachment;

    std::unique_ptr<SliderAttachment> Gain1Attachment;
    std::unique_ptr<SliderAttachment> Gain2Attachment;
    std::unique_ptr<SliderAttachment> Gain3Attachment;
    std::unique_ptr<SliderAttachment> Gain4Attachment;

    RotaryStyle rotary;
    RotaryStyle rotary2;
    RotaryStyle rotary3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddittiveComponent)
};
