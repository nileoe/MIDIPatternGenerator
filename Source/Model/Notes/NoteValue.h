/*
  ==============================================================================

    NoteValue.h
    Created: 11 Apr 2025 1:14:37pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class NoteValue
{
    public:
    NoteValue();
    NoteValue(juce::String name, double ratioFromBeat);

    const juce::String& getName()   const;
    int getId()                     const;
    double getRatioFromBeat()       const;

    private:
    static int nextId;
    int id;
    juce::String name;
    double ratioFromBeat;
};

