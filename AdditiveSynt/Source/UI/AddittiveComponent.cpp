/*
  ==============================================================================

    AddittiveComponent.cpp
    Created: 28 Apr 2021 9:40:37pm
    Author:  Zack

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AddittiveComponent.h"

//==============================================================================
AddittiveComponent::AddittiveComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    freq2Attachment = std::make_unique<SliderAttachment>(apvts, "FREQ2", freq2Slider);
    freq3Attachment = std::make_unique<SliderAttachment>(apvts, "FREQ3", freq3Slider);
    freq4Attachment = std::make_unique<SliderAttachment>(apvts, "FREQ4", freq4Slider);

    setSliderParams(freq2Slider);
    setSliderParams(freq3Slider);
    setSliderParams(freq4Slider);

    Gain1Attachment = std::make_unique<SliderAttachment>(apvts, "GAIN1", Gain1);
    Gain2Attachment = std::make_unique<SliderAttachment>(apvts, "GAIN2", Gain2);
    Gain3Attachment = std::make_unique<SliderAttachment>(apvts, "GAIN3", Gain3);
    Gain4Attachment = std::make_unique<SliderAttachment>(apvts, "GAIN4", Gain4);

    setSliderParams(Gain1);
    setSliderParams(Gain2);
    setSliderParams(Gain3);
    setSliderParams(Gain4);
}

AddittiveComponent::~AddittiveComponent()
{
}

void AddittiveComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AddittiveComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 5 - padding;
    const auto sliderHeight = bounds.getWidth() / 2;
    const auto sliderStartX = 0;
    const auto sliderStartYline1 = 0;
    const auto sliderStartYline2 = bounds.getHeight() / 2;

    Gain1.setBounds(sliderStartX,                       sliderStartYline2, sliderWidth, sliderHeight);
    Gain2.setBounds(Gain1.getRight() + padding,         sliderStartYline2, sliderWidth, sliderHeight);
    Gain3.setBounds(Gain2.getRight() + padding,         sliderStartYline2, sliderWidth, sliderHeight);
    Gain4.setBounds(Gain3.getRight() + padding,         sliderStartYline2, sliderWidth, sliderHeight);

    freq2Slider.setBounds(Gain1.getRight() + padding,   sliderStartYline1, sliderWidth, sliderHeight);
    freq3Slider.setBounds(Gain2.getRight() + padding,   sliderStartYline1, sliderWidth, sliderHeight);
    freq4Slider.setBounds(Gain3.getRight() + padding,   sliderStartYline1, sliderWidth, sliderHeight );


}

void AddittiveComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}