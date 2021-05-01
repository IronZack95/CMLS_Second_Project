/*
  ==============================================================================

    OscComponent.h
    Created: 28 Apr 2021 7:04:10pm
    Author:  Zack

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId);       //il primo argomento deve fare riferimento al tree value
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    const int BoxWidth = 100;
    const int BoxHeight = 20;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
