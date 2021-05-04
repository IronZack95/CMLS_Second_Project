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
    //g.fillAll(juce::Colours::black);
}

void AddittiveComponent::resized()
{
    const auto division = 6;
    //const auto bounds = getLocalBounds().reduced(division);
    const auto padding = 15;
    const auto bounds = getLocalBounds();
    const auto WidthDivision = bounds.getWidth() / division;
    const auto HeightDivision = bounds.getHeight() / division;
    const auto Width2 = 1.6f * WidthDivision;
    const auto Height2 = 1.6f * HeightDivision;
    const auto Width1 = 2.5f * WidthDivision;
    const auto Height1 = 2.5f * HeightDivision;

    Gain1.setBounds(WidthDivision, HeightDivision, Width1, Height1);
    Gain1.setCentrePosition(bounds.getWidth() / 2, bounds.getHeight() / 2);      // bottone grande   

    Gain2.setBounds( WidthDivision, HeightDivision, Width2, Height2);
    Gain2.setCentrePosition(2 * WidthDivision, HeightDivision);
    Gain3.setBounds( WidthDivision, HeightDivision, Width2, Height2);
    Gain3.setCentrePosition(4* WidthDivision, HeightDivision);
    Gain4.setBounds(WidthDivision, HeightDivision, Width2, Height2);
    Gain4.setCentrePosition(2* WidthDivision, 5*HeightDivision);

    freq2Slider.setBounds(WidthDivision, HeightDivision, Width2, Height2);
    freq2Slider.setCentrePosition( WidthDivision, 2*HeightDivision);
    freq3Slider.setBounds(WidthDivision, HeightDivision, Width2, Height2);
    freq3Slider.setCentrePosition(5*WidthDivision, 2*HeightDivision);
    freq4Slider.setBounds(WidthDivision, HeightDivision, Width2, Height2);
    freq4Slider.setCentrePosition(WidthDivision, 4*HeightDivision);

}

void AddittiveComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);
    addAndMakeVisible(slider);
    slider.setLookAndFeel(&rotary);
}