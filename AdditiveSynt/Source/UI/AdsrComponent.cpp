/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 28 Apr 2021 3:45:07pm
    Author:  Zack

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);

    setSliderParams(attackSlider);      //customizzazioni e style
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
    const auto division = 3;
    //const auto bounds = getLocalBounds().reduced(division);
    const auto bounds = getLocalBounds();
    const auto WidthDivision = bounds.getWidth() / (division);
    const auto HeightDivision = bounds.getHeight() / (division);
    const auto Width2 = 1.0f * WidthDivision;
    const auto Height2 = 1.0f * HeightDivision;
    const auto Width1 =  0.7f*WidthDivision;
    const auto Height1 = 0.7f* HeightDivision;

    attackSlider.setBounds(WidthDivision, HeightDivision, Width1, Height1);
    attackSlider.setCentrePosition(WidthDivision, HeightDivision);

    decaySlider.setBounds(WidthDivision, HeightDivision, Width2, Height2);
    decaySlider.setCentrePosition(2* WidthDivision, HeightDivision);

    sustainSlider.setBounds(WidthDivision, HeightDivision, Width2, Height2);
    sustainSlider.setCentrePosition(WidthDivision, 2* HeightDivision);

    releaseSlider.setBounds(WidthDivision, HeightDivision, Width1, Height1);
    releaseSlider.setCentrePosition(2* WidthDivision, 2* HeightDivision);

}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);
    addAndMakeVisible(slider);
    slider.setLookAndFeel(&rotary);
}
