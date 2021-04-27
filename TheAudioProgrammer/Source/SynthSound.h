/*
  ==============================================================================

    SourceSound.h
    Created: 27 Apr 2021 12:20:15am
    Author:  Zack

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound 
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};