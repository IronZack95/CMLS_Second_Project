#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor(SynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), oscSel (audioProcessor.apvts, "OSC1WAVETYPE"), adsr (audioProcessor.apvts), addOsc (audioProcessor.apvts), anim(audioProcessor.Pbuffer) //inizializzatore
{

    setSize(700, 400);
    //AudioProcessorEditor::setResizable(false, false);       // Questo serve a rendere la finestra fissa

    setResizable (false, false);
    //setResizeLimits (250, 150, getWidth(), getHeight());

    centreWithSize (getWidth(), getHeight());

    // Animation settings
    addAndMakeVisible(anim);

    // Addittive synth
    addAndMakeVisible(addOsc);          //l'ordine con cui appaiono è importante per la visibilità di tutti gli elementi

    //Menu' oscillatore
    addAndMakeVisible(oscSel);

    // ADSR
    //oscSelAttachment = std::make_unique< juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);
    addAndMakeVisible(adsr);

}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll(juce::Colours::white);

    //g.setFont (15.0f);
    //g.drawFittedText ("Ciao, sono un cucciolo di synth", getLocalBounds(), juce::Justification::topLeft, 1);
}

void SynthAudioProcessorEditor::resized()
{
    const auto bounds = getLocalBounds();
    // Animation
    anim.setBounds(0, 0, bounds.getWidth(), bounds.getHeight());
    // Addittive Osc
    addOsc.setBounds(0, 0, bounds.getWidth(), bounds.getHeight());        // add osc occupa tutto lo schermo
    // OSC Menu'
    oscSel.setBounds(0, 0, oscSel.BoxWidth, oscSel.BoxHeight);
    oscSel.setCentrePosition(bounds.getWidth() / 2, bounds.getHeight() / 6 - 2 * oscSel.BoxHeight);
    // ADSR Resized
    adsr.setBounds(bounds.getWidth()/2, bounds.getHeight()/2, bounds.getWidth()/2, bounds.getHeight()/2);
    
   
}

void SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    /*
    if (slider == &freq1Slider) {
        audioProcessor.delta2 = freq1Slider.getValue();
    }
    else if (slider == &freq2Slider) {
        audioProcessor.delta3 = freq2Slider.getValue();
    }
    else if (slider == &freq3Slider) {
        audioProcessor.delta4 = freq3Slider.getValue();
    }
    */
}