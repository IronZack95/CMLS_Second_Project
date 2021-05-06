/*
  ==============================================================================

    OscComponent.cpp
    Created: 28 Apr 2021 7:04:10pm
    Author:  Zack

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    const auto division = 6;
    //const auto bounds = getLocalBounds().reduced(division);
    const auto bounds = getLocalBounds();
    const auto WidthDivision = bounds.getWidth() / division;
    const auto HeightDivision = bounds.getHeight() / division;

    oscWaveSelector.setBounds(0, 0, BoxWidth, BoxHeight);
}
