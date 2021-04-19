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
    setSize(360, 300);
    Amp1.setSliderStyle(juce::Slider::LinearBarVertical);
    Amp1.setRange(0.0, 1.0, 0.001);
    Amp1.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp1.setPopupDisplayEnabled(true, false, this);
    Amp1.setTextValueSuffix(" Amp 1");
    Amp1.setValue(1.0);

    Amp2.setSliderStyle(juce::Slider::LinearBarVertical);
    Amp2.setRange(0.0, 1.0, 0.001);
    Amp2.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp2.setPopupDisplayEnabled(true, false, this);
    Amp2.setTextValueSuffix(" Amp 2");
    Amp2.setValue(1.0);

    Amp3.setSliderStyle(juce::Slider::LinearBarVertical);
    Amp3.setRange(0.0, 1.0, 0.001);
    Amp3.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp3.setPopupDisplayEnabled(true, false, this);
    Amp3.setTextValueSuffix(" Amp 3");
    Amp3.setValue(1.0);

    Amp4.setSliderStyle(juce::Slider::LinearBarVertical);
    Amp4.setRange(0.0, 1.0, 0.001);
    Amp4.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp4.setPopupDisplayEnabled(true, false, this);
    Amp4.setTextValueSuffix(" Amp 4");
    Amp4.setValue(1.0);

    Delta2.setSliderStyle(juce::Slider::LinearBarVertical);
    Delta2.setRange(0.0, 1000.0, 1.0);
    Delta2.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Delta2.setPopupDisplayEnabled(true, false, this);
    Delta2.setTextValueSuffix(" Delta 2");
    Delta2.setValue(1.0);

    Delta3.setSliderStyle(juce::Slider::LinearBarVertical);
    Delta3.setRange(0.0, 1000.0, 1.0);
    Delta3.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Delta3.setPopupDisplayEnabled(true, false, this);
    Delta3.setTextValueSuffix(" Delta 3");
    Delta3.setValue(1.0);

    Delta4.setSliderStyle(juce::Slider::LinearBarVertical);
    Delta4.setRange(0.0, 1000.0, 1.0);
    Delta4.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Delta4.setPopupDisplayEnabled(true, false, this);
    Delta4.setTextValueSuffix(" Delta 4");
    Delta4.setValue(1.0);


    addAndMakeVisible(&Amp1);
    addAndMakeVisible(&Amp2);
    addAndMakeVisible(&Amp3);
    addAndMakeVisible(&Amp4);

    addAndMakeVisible(&Delta2);
    addAndMakeVisible(&Delta3);
    addAndMakeVisible(&Delta4);
    
    Amp1.addListener(this);
    Amp2.addListener(this);
    Amp3.addListener(this);
    Amp4.addListener(this);
    Delta2.addListener(this);
    Delta3.addListener(this);
    Delta4.addListener(this);
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
    g.drawFittedText ("Hell World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Amp1.setBounds(40, 30, 20, getHeight() - 60);
    Amp2.setBounds(80, 30, 20, getHeight() - 60);
    Amp3.setBounds(120, 30, 20, getHeight() - 60);
    Amp4.setBounds(160, 30, 20, getHeight() - 60);

    Delta2.setBounds(240, 30, 20, getHeight() - 60);
    Delta3.setBounds(280, 30, 20, getHeight() - 60);
    Delta4.setBounds(320, 30, 20, getHeight() - 60);

}

// Creata da noi per attaccare lo Slider
void SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if (slider == &Amp1) {
        audioProcessor.Amplificazione = Amp1.getValue();
    }
    else if (slider == &Amp2) {
        audioProcessor.Amplificazione2 = Amp2.getValue();
    }
    else if (slider == &Amp3) {
        audioProcessor.Amplificazione3 = Amp3.getValue();
    }
    else if (slider == &Amp4) {
        audioProcessor.Amplificazione4 = Amp4.getValue();
    }
    else if (slider == &Delta2) {
        audioProcessor.delta2 = Delta2.getValue();
    }
    else if (slider == &Delta3) {
        audioProcessor.delta3 = Delta3.getValue();
    }
    else if (slider == &Delta4) {
        audioProcessor.delta4 = Delta4.getValue();
    }
}
