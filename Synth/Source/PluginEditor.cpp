/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    Amp1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    Amp1.setRange(0.0, 127.0, 1.0);
    Amp1.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp1.setPopupDisplayEnabled(true, false, this);
    Amp1.setTextValueSuffix(" of velocity");
    Amp1.setValue(1.0);
    addAndMakeVisible(&Amp1);
    //  midiVelocity.addListener(this);

    setSize (800, 300);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Amp1.setBounds(40, 30, 20, getHeight() - 60);

}
