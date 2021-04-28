#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));  // qui dico di controllare qual'è la nota in ingresso e settare la frequenza dell'oscillatore su quella
    adsr.noteOn(); //qui è dove inizia l'envelope dell'ADSR
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff(); //qui è dove finisce l'envelope dell'ADSR

    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{


}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{ 
    adsr.setSampleRate(sampleRate);     //inizializzo l'ADSR

    juce::dsp::ProcessSpec spec;        //Inizializzo il suono dell'Oscillatore
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);
    gain.prepare(spec);
    //osc.setFrequency(220.0f);
    gain.setGainLinear(0.3f);  

    delta2 = 250.0f;
    osc2.prepare(spec);
    gain2.prepare(spec);    
    gain2.setGainLinear(0.3f);

    isPrepared = true; // ok siamo pronti a partire
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    adsr.setParameters(adsrParams);   
}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared); //serve a stabilire che se la variabile non è stata eseguita il progetto si ferma

    if (! isVoiceActive())  // se la voice selezionata non è attiva skippo
    {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); //Aggiorno il Synthbuffer che è un buffer di sostegno
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };            //Renderizzo il prossimo audio Block  
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    osc2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc2.setFrequency(osc.getFrequency() + delta2);

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples()); // dopo che ho caricatro il buffer di uscita con l'output desiderato applico l'ADSR

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)      //carico le informazioni di synthBuffer sull'outputBuffer
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}