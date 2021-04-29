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
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getWidth();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    freq2Slider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    freq3Slider.setBounds(freq2Slider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    freq4Slider.setBounds(freq3Slider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void AddittiveComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}