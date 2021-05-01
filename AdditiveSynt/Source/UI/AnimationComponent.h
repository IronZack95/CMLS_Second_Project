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

//==============================================================================
class Animation : public juce::AnimatedAppComponent
{
public:
    float k;
    float velRotazione = 0.33f;
    int fps = 60;
    const float dotDist = 0.06f;
    const int numberOfDots = 60;
    //==============================================================================
    Animation()
    {
        setFramesPerSecond(fps);
        k = 0;
        //velRotazione = 0.04f;
    }

    void update() override;

    void paint(juce::Graphics& g) override;

    void resized() override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Animation)
};
