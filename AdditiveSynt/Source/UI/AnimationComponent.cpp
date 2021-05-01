/*
  ==============================================================================

    AnimationComponent.cpp
    Created: 1 May 2021 2:39:56am
    Author:  Zack

  ==============================================================================
*/

#include "AnimationComponent.h"
#include "StyleData.h"

void Animation::update()
{
}

void Animation::paint(juce::Graphics& g)
{

    // colore dello sfondo
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(backGround);
    g.fillAll();

    //colore dei punti
    //g.setColour(getLookAndFeel().findColour(juce::Slider::thumbColourId));
    g.setColour(electric);

    int radiusA = 100;
    int radiusB = radiusA / 15;
    radiusB = 0;
    const auto bounds = getLocalBounds();
    const float deltaX = bounds.getWidth() / 2.0f;
    const float deltaY = bounds.getHeight() / 2.0f;

    const float t = 2 * juce::float_Pi * ((float)getFrameCounter() / fps) * velRotazione;

    juce::Path spinePath; 
    //1.0f * (float)radius * std::sin((float)getFrameCounter() * velRotazione
    //(float)i * 0.06f

    k += 0.02f;
    if (k > 20)
        k = 0;

    //velRotazione += 0.00001;

    for (auto i = 0; i < numberOfDots; ++i)
    {

        float fase = -t + (float)i * dotDist;

        float LFO = (float)radiusB * (std::sin(k * fase) + std::sin(k * fase * 20 + 1)); 

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