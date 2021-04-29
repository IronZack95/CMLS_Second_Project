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
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto Width = bounds.getWidth();
    const auto Height = bounds.getWidth();
    const auto BoxWidth = 100;
    const auto BoxHeight = 20;
    const auto BoxStartX = 10;
    const auto BoxStartY = 10;

    oscWaveSelector.setBounds(10, 10, BoxWidth, BoxHeight);
}
