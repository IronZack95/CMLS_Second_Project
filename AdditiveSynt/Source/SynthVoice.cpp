#include "SynthVoice.h"
#include "PluginProcessor.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    oscillatore.setWaveFrequency(midiNoteNumber , delta_freq);      //qui è dove processo la nota midi
    adsr.noteOn();                                          //qui è dove inizia l'envelope dell'ADSR

}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();                                         //qui è dove finisce l'envelope dell'ADSR

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

    // inizializzo il Primo Oscillatore
    oscillatore.prepareToPlay(spec);
    //osc.setFrequency(220.0f);         // frequenza OPZIONALE dell' oscillatore
    oscillatore.setGain(0.0f);          // inizializzo a zero il volume

    isPrepared = true;                  // ok siamo pronti a partire
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)    
{
    adsr.updateADSR(attack, decay, sustain, release);           //serve a chiamare la classe che si occupa di fare l'update di tutti i parametri
}

void SynthVoice::updateDelta(const float delta)
{
    delta_freq = delta;
}

void SynthVoice::updateGain(const float gain)
{
    oscillatore.setGain(gain);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);                                        //serve a stabilire che se la variabile non è stata eseguita il progetto si ferma

    if (! isVoiceActive())                                      // se la voice selezionata non è attiva skippo
    {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);     //Aggiorno il Synthbuffer che è un buffer di sostegno
    synthBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
                                                                                                
    oscillatore.getNextAudioBlock(audioBlock);                                  //Renderizzo il prossimo audio Block  

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());    // dopo che ho caricatro il buffer di uscita con l'output desiderato applico l'ADSR

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)   //carico le informazioni di synthBuffer sull'outputBuffer
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}