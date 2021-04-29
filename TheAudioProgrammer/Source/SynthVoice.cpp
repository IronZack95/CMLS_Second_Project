#include "SynthVoice.h"
#include "PluginProcessor.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);       //qui è dove processo la nota midi
    /*
    osc2.setWaveFrequency(midiNoteNumber+3);
    osc3.setWaveFrequency(midiNoteNumber+5);
    osc4.setWaveFrequency(midiNoteNumber+7);
    */
    adsr.noteOn();                              //qui è dove inizia l'envelope dell'ADSR

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

    // inizializzo il Primo Oscillatore
    osc.prepareToPlay(spec);
    gain.prepare(spec);
    //osc.setFrequency(220.0f);     // frequenza del primo oscillatore
    gain.setGainLinear(0.3f);  
    /*
    // inizializzo gli oscillatori additivi
    osc2.prepareToPlay(spec);
    gain2.prepare(spec);
    //osc.setFrequency(220.0f);     // frequenza del primo oscillatore
    gain2.setGainLinear(0.3f);

    osc3.prepareToPlay(spec);
    gain3.prepare(spec);
    //osc.setFrequency(220.0f);     // frequenza del primo oscillatore
    gain3.setGainLinear(0.3f);

    osc4.prepareToPlay(spec);
    gain4.prepare(spec);
    //osc.setFrequency(220.0f);     // frequenza del primo oscillatore
    gain4.setGainLinear(0.3f);
    */

    isPrepared = true; // ok siamo pronti a partire
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)    //serve a chiamare la classe che si occupa di fare l'update di tutti i parametri
{
    adsr.updateADSR(attack, decay, sustain, release);
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
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    // Primo Oscillatore, controllato via midi                              //Renderizzo il prossimo audio Block  
    osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    /*
    osc2.getNextAudioBlock(audioBlock);
    //osc2.setFrequency(440.0);
    gain2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    osc3.getNextAudioBlock(audioBlock);
    gain3.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    osc4.getNextAudioBlock(audioBlock);
    gain4.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    */

    /*
    // Secondo oscillatore, controllato via Delta
    osc2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc2.setFrequency(osc.getFrequency() + delta2);

    // Terzo oscillatore, controllato via Delta
    osc3.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain3.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc3.setFrequency(osc.getFrequency() + delta3);

    // Quarto oscillatore, controllato via Delta
    osc4.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain4.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc4.setFrequency(osc.getFrequency() + delta4);
    */
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