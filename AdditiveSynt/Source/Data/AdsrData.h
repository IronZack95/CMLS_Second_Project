/*
  ==============================================================================

    AdsrData.h
    Created: 28 Apr 2021 3:45:22pm
    Author:  Zack

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrData  : public juce::ADSR
{
public:
    void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release);

private:

    juce::ADSR::Parameters adsrParams;
};
