#include "PluginProcessor.h"
#include "PluginEditor.h"

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
                       ), apvts(*this, nullptr, "Parameters", createParameters()) // qui devo inizializzare l'oggetto tree state
#endif
{
    for (auto i = 0; i < 4; ++i)
    {
        synth.addVoice(new SynthVoice());   // MAIN SYNTH
        synth.addSound(new SynthSound());

        synth2.addVoice(new SynthVoice());   // SYNTH ADDITIVI
        synth2.addSound(new SynthSound());

        synth3.addVoice(new SynthVoice());
        synth3.addSound(new SynthSound());

        synth4.addVoice(new SynthVoice());
        synth4.addSound(new SynthSound());

    }

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
    synth.setCurrentPlaybackSampleRate(sampleRate);                                             // MAIN SYNTH

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))                          // Se sono riuscito a puntare la synth voice giusta allora..
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());     // ..il mio puntatore va a preparare la voce in questione
        }
    }

    synth2.setCurrentPlaybackSampleRate(sampleRate);                                            // ADDITTIVE SYNTH

    for (int i = 0; i < synth2.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth2.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    synth3.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth3.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth3.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    synth4.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth4.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth4.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
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
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))                  // Qui dentro metto i parametri che vanno aggiornati costantemente
        {

            // LFO

            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");                       //riferimenti alla classe ValueTreeState
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // OSC controls
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            //ADD OSC
            auto& gain = *apvts.getRawParameterValue("GAIN1");

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());   //i metodi load servono perchè le variabili non sono semplici float ma atomic
            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->updateGain(gain.load());
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());               // questo chiama il "renderNextBlock"


    for (int i = 0; i < synth2.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth2.getVoice(i)))
        {

            // LFO

            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // OSC controls
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            //ADD OSC
            auto& gain = *apvts.getRawParameterValue("GAIN2");
            auto& delta = *apvts.getRawParameterValue("FREQ2");

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->updateDelta(delta.load());
            voice->updateGain(gain.load());
        }
    }

    synth2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    for (int i = 0; i < synth3.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth3.getVoice(i)))
        {

            // LFO

            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // OSC controls
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            //ADD OSC
            auto& gain = *apvts.getRawParameterValue("GAIN3");
            auto& delta = *apvts.getRawParameterValue("FREQ3");

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->updateDelta(delta.load());
            voice->updateGain(gain.load());
        }
    }

    synth3.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    for (int i = 0; i < synth4.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth4.getVoice(i)))
        {

            // LFO

            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // OSC controls
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            //ADD OSC
            auto& gain = *apvts.getRawParameterValue("GAIN4");
            auto& delta = *apvts.getRawParameterValue("FREQ4");

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->updateDelta(delta.load());
            voice->updateGain(gain.load());
        }
    }

    synth4.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    Pbuffer = buffer;       // serve a copiare il buffer per l'animazione

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

// Value Tree

juce::AudioProcessorValueTreeState::ParameterLayout SynthAudioProcessor::createParameters()
{
    // DATA SIDE
    // Combobox: Per selezionare il tipo di oscillatore
    // Attack - float
    // Decay - float
    // Sustain - float
    // Release - float

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params; //riempio questo vettore con i paramentri dei valori

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.207f)); // l'ultimo parametro è il default

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.351f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.1f, 3.0f, }, 1.064f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.759f));

    // OSC Select

    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{ "Sine","Saw","Square" }, 0));

    // OSC
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FREQ2", "Freq 2", juce::NormalisableRange<float>{-5.0f, 5.0f, }, 0.0f)); // imposto i delta a 0

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FREQ3", "Freq 3", juce::NormalisableRange<float>{-5.0f, 5.0f, }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FREQ4", "Freq 4", juce::NormalisableRange<float>{-5.0f, 5.0f, }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN1", "Gain 1", juce::NormalisableRange<float>{0.0f, 0.25f, }, 0.2f));   // volo il primo volume non a 0

    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN2", "Gain 2", juce::NormalisableRange<float>{0.0f, 0.25f, }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN3", "Gain 3", juce::NormalisableRange<float>{0.0f, 0.25f, }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN4", "Gain 4", juce::NormalisableRange<float>{0.0f, 0.25f, }, 0.0f));

    return {params.begin(), params.end() }; // ritorno con il vettore di paramentri
}
