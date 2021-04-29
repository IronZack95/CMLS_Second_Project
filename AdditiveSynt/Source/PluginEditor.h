#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthVoice.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/AddittiveComponent.h"

//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

    
private:  

    // 
    SynthAudioProcessor& audioProcessor;
    OscComponent oscSel;                       // rendo visibile il componente oscillatore
    AdsrComponent adsr;                     // rendo visibile l'ADSR
    AddittiveComponent addOsc;              // rendo visibili i controlli degli oscillatori additivi

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};