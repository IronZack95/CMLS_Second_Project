#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor(SynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), osc (audioProcessor.apvts, "OSC1WAVETYPE"), adsr (audioProcessor.apvts), addOsc (audioProcessor.apvts) //inizializzatore
{

    setSize(400, 300);

    //Menu' oscillatore
    addAndMakeVisible(osc);

    // ADSR
    //oscSelAttachment = std::make_unique< juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);
    addAndMakeVisible(adsr);

    // Addittive synth
    addAndMakeVisible(addOsc);

}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Ciao, sono un cucciolo di synth", getLocalBounds(), juce::Justification::topLeft, 1);
}

void SynthAudioProcessorEditor::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getWidth() / 4 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);
    // OSC Menu'
    osc.setBounds(10, 10, 100, 30);
    // ADSR Resized
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    // Addittive Osc
    addOsc.setBounds(0, 50, getWidth() / 2, getHeight() -50);

    
    /*
    //Slider delle frequenze
    freq1Slider.setBounds(sliderStartX, sliderStartY + 200, sliderWidth, sliderHeight);
    freq2Slider.setBounds(freq1Slider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    freq3Slider.setBounds(freq2Slider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    */
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