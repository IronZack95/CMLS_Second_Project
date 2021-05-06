/*
  ==============================================================================

    AnimationComponent.cpp
    Created: 1 May 2021 2:39:56am
    Author:  Zack

  ==============================================================================
*/

#include "AnimationComponent.h"
#include "StyleData.h"

Animation::Animation(juce::AudioBuffer<float>& p): buffer(p)
{
    setFramesPerSecond(fps);

    //velRotazione = 0.04f;

    numChannel = buffer.getNumChannels();
    numSamples = buffer.getNumSamples();

}


void Animation::update()
{
}

void Animation::paint(juce::Graphics& g)
{
    setNote(buffer);                        //ricalcolo l'audio buffer ogni fps
    const auto bounds = getLocalBounds();
    // colore dello sfondo
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(backGround);
    g.fillAll();

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::SynthPlugin4_jpg, BinaryData::SynthPlugin4_jpgSize);
    g.drawImage(background, 0, 0, bounds.getWidth(),bounds.getHeight(),0,0,background.getWidth(),background.getHeight());
    //colore dei punti
    //g.setColour(getLookAndFeel().findColour(juce::Slider::thumbColourId));
    g.setColour(electric);

    int radiusA = 88;
    int radiusB = radiusA / 16;
    //radiusB = 10;

    const float deltaX = bounds.getWidth() / 2.0f;
    const float deltaY = bounds.getHeight() / 2.0f;

    const float t = 2 * juce::float_Pi * ((float)getFrameCounter() / fps) * velRotazione;

    juce::Path spinePath; 
    //1.0f * (float)radius * std::sin((float)getFrameCounter() * velRotazione
    //(float)i * 0.06f

    //velRotazione += 0.00001;

    for (auto i = 0; i < numberOfDots; ++i)
    {

        float fase = -t + (float)i * dotDist;

        float LFO = (float)radiusB * 2 * PrintVect[i];

        float modulo = (float)radiusA + LFO;

        juce::Point<float> p(deltaX + modulo * std::cos(fase),
            deltaY + modulo * std::sin(fase));

        if (i == 0)
            spinePath.startNewSubPath(p);  
        else
            spinePath.lineTo(p);          
    }

    g.strokePath(spinePath, juce::PathStrokeType(4.0f));
}

void Animation::resized()
{
}

void Animation::setNote(juce::AudioBuffer<float>& buffer)
{
    int times =(int)(numSamples / numberOfDots);
    const float *c = buffer.getReadPointer(0, numberOfDots);
    /*
        for (int i,k = 0; i < numberOfDots; ++i) {
            k = i + times;
            PrintVect[i] = c[k];
            if (k > numSamples)                     // sto facendo un resasamples per fare un fit tra il numero di punti e il singolo sample
                break;
        }
    */
        for (int i= 0; i < numberOfDots; ++i) {
            PrintVect[i] = c[i];                     // senza rifasamento, solo i primi campioni
        }
}