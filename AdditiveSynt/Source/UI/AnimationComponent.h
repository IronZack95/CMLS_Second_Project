/*
  ==============================================================================

    AnimationComponent.h
    Created: 1 May 2021 2:39:56am
    Author:  Zack

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "StyleData.h"

#define numberOfDots 60         // numero di punti sulla geometria
#define dotDist  0.06f          // distanza tra i punti nell'animazione
#define fps 60                 //frame per secondo

//==============================================================================
class Animation : public juce::AnimatedAppComponent
{
public:
    //==============================================================================

    Animation(juce::AudioBuffer<float>&);

    void update() override;

    void paint(juce::Graphics& g) override;

    void resized() override;

    void setNote(juce::AudioBuffer<float>&);
    
private:
    int numSamples;
    int numChannel;

    float velRotazione = 0.33f;         //
    float PrintVect[numberOfDots];           //vettore che contiene i punti proiettati sulla geometria
    
    juce::AudioBuffer<float>& buffer;   // faccio riferimento all'oggetto buffer esistente
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Animation)
};
