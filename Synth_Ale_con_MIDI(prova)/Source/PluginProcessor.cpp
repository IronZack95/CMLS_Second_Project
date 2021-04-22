/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define SAMPLE_RATE (44100)
#ifndef M_PI
#define M_PI (3.14159265)
#endif

//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()

#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

SynthAudioProcessor::~SynthAudioProcessor()
{
}

//==============================================================================
const juce::String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    fase = 0.0;
    fase2 = 0.0;
    fase3 = 0.0;
    fase4 = 0.0;
    Amplificazione = 0.0;
    Amplificazione2 = 0.0;
    Amplificazione3 = 0.0;
    Amplificazione4 = 0.0;
    Frequenza = 440.0;
    delta2 = 0.0;
    delta3 = 0.0;
    delta4 = 0.0;

    //Roba per il FM_Synth
    amp = 1.0;
    phase = 2.0;
    car_freq = 0.0;
    mod_freq = 0.0;
    mod_phase = 1.0;
    mod_index = 0.0;

}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /*
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...

    }
    */

    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    float amplitude_now = Amplificazione;
    float amplitude_now2 = Amplificazione2;
    float amplitude_now3 = Amplificazione3;
    float amplitude_now4 = Amplificazione4;
    float freq_now = car_freq;
    int numSamples = buffer.getNumSamples();


    //Roba per il FM_Synth
    float mod;
    juce::MidiMessage m;
    int time;

    for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
    {
        if (m.isNoteOn())
        {
            amp = 0.1;
            car_freq = m.getMidiNoteInHertz(m.getNoteNumber());
        }
        else if (m.isNoteOff())
        {
            amp = 0.0;
        }
        else if (m.isAftertouch())
        {
        }
        else if (m.isPitchWheel())
        {
        }
    }

    for (int i = 0; i < numSamples; ++i) {

        mod = mod_index * (float)sin((double)mod_phase);

        channelDataL[i] = amp * (amplitude_now * (float)sin((double)mod_phase + mod) + amplitude_now2* (float)sin((double)fase2) + amplitude_now3 * (float)sin((double)fase3) +amplitude_now4 * (float)sin((double)fase4));
        channelDataR[i] = channelDataL[i];

        /*phase += (float)(M_PI * 2. * (((double)freq_now / (double)
            SAMPLE_RATE)));
        if (phase >= M_PI * 2.) phase -= M_PI * 2.;*/

        mod_phase += (float)(M_PI * 2. * ((double)freq_now / (double)
            SAMPLE_RATE));
        if (mod_phase >= M_PI * 2.) mod_phase -= M_PI * 2.;

        fase2 += (float)(M_PI * 2. * (((double)(freq_now + delta2)/ (double)
            SAMPLE_RATE)));
        if (fase2 > M_PI * 2.) fase2 -= M_PI * 2.;

        fase3 += (float)(M_PI * 2. * (((double)(freq_now + delta3) / (double)
            SAMPLE_RATE)));
        if (fase3 > M_PI * 2.) fase3 -= M_PI * 2.;

        fase4 += (float)(M_PI * 2. * (((double)(freq_now + delta4) / (double)
            SAMPLE_RATE)));
        if (fase4 > M_PI * 2.) fase4 -= M_PI * 2.;
    }


    /*for (int i = 0; i < numSamples; ++i) {

        channelDataL[i] = amplitude_now * (float)sin((double)fase) + amplitude_now2* (float)sin((double)fase2) + amplitude_now3 * (float)sin((double)fase3) +amplitude_now4 * (float)sin((double)fase4);
        channelDataR[i] = channelDataL[i];
 
        fase += (float)(M_PI * 2. * (((double)freq_now / (double)
            SAMPLE_RATE)));
        if (fase > M_PI * 2.) fase -= M_PI * 2.;

        fase2 += (float)(M_PI * 2. * (((double)(freq_now + delta2)/ (double)
            SAMPLE_RATE)));
        if (fase2 > M_PI * 2.) fase2 -= M_PI * 2.;

        fase3 += (float)(M_PI * 2. * (((double)(freq_now + delta3) / (double)
            SAMPLE_RATE)));
        if (fase3 > M_PI * 2.) fase3 -= M_PI * 2.;

        fase4 += (float)(M_PI * 2. * (((double)(freq_now + delta4) / (double)
            SAMPLE_RATE)));
        if (fase4 > M_PI * 2.) fase4 -= M_PI * 2.;

    }*/

    

}

//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}
