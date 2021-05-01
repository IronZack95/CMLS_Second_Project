/*
  ==============================================================================

    StyleData.cpp
    Created: 30 Apr 2021 3:25:52pm
    Author:  Zack

  ==============================================================================
*/

#include "StyleData.h"


void RotaryStyle::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    float diameter = juce::jmin(width, height) * 0.9;
    float radius = diameter / 2;
    float centreX = x + width / 2;
    float centreY = y + height / 2;
    float rx = centreX - radius;
    float ry = centreY - radius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    juce::Rectangle<float> dialArea(rx, ry, diameter, diameter);
    g.setColour(interno);
    g.fillEllipse(dialArea);

    juce::Rectangle<float> dialArea2(rx + diameter/4, ry + diameter / 4, diameter/2, diameter/2);
    g.setColour(contorno);
    g.fillEllipse(dialArea2);

    g.setColour(tick);
    juce::Path dialThick;
    dialThick.addRectangle(0, -radius, 4.0f, radius * 0.33);
    //dialThick.addEllipse(0, -radius, radius * 0.33, radius * 0.33);
    g.fillPath(dialThick, juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(contorno);
    g.drawEllipse(rx, ry, diameter, diameter, 2.5f);

    g.setColour(ring);
    g.drawEllipse(rx-1.0f, ry- 1.0f, diameter+2.0f, diameter + 2.0f, 1.0f);
}
