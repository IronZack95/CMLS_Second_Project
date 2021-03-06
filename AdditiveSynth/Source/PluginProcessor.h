#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"

//==============================================================================
/**
*       QUESTO � IL CERCELLO PRINCIPALE DEL PLUGIN
*/
class SynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthAudioProcessor();
    ~SynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts; // creo l'oggetto tree state

    juce::AudioBuffer<float> Pbuffer;


private:


    juce::Synthesiser synth;    // MAIN SYNTH

    juce::Synthesiser synth2;   // SYNTH ADDITIVI
    juce::Synthesiser synth3;
    juce::Synthesiser synth4;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters(); // oggetto tree state

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};
