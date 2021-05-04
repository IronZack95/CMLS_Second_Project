/*
  ==============================================================================

    StyleData.h
    Created: 30 Apr 2021 3:25:52pm
    Author:  Zack

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

//palette
#define back      0xff38373d
#define fore      0xff323137

#define bluScuro        0xff7688a3
#define bluChiaro        0xff90a2b8
#define bluGrigio       0xff5e6671
#define azzurro         0xffd7eff6 
#define azzurroElettrico         0xffd9e1e4
#define azzurroDue         0xff4a86e8

#define grigioBase      0xff848487
#define grigioScuro     0xff2e2c33
#define grigioChiaro    0xffc0c0c2 
#define bluGrigio       0xff5e6671

//colori base
static auto backGround = juce::Colour(back);
static auto foreGround = juce::Colour(fore);

//colore rotary
static auto interno = juce::Colour(grigioScuro);
static auto ring = juce::Colour(grigioChiaro);
static auto contorno = juce::Colour(back);
static auto tick = juce::Colour(azzurro);

//colori Animazione
static auto electric = juce::Colour(azzurro);

class RotaryStyle : public juce::LookAndFeel_V4
{
public:
    RotaryStyle()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    void setColor(int color);
    
private:
    juce::Colour topcolor;

};