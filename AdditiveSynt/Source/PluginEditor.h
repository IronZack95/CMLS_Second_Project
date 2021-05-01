#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthVoice.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/AddittiveComponent.h"
#include "UI/StyleData.h"
#include "UI/AnimationComponent.h"

//==============================================================================
/**
*/
//palette
#define grigioBase 0xff848487
#define grigioScuro 0xff2e2c33
#define grigioChiaro 0xffc0c0c2 
#define bluGrigio 0xff5e6671
#define azzurro  0xffd7eff6 
#define bluGrigio 0xff3e5076

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
    Animation anim;
    AddittiveComponent addOsc;              // rendo visibili i controlli degli oscillatori additivi
    OscComponent oscSel;                       // rendo visibile il componente oscillatore
    AdsrComponent adsr;                     // rendo visibile l'ADSR



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};