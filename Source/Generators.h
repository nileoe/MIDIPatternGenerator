/*
  ==============================================================================

    Generators.h
    Created: 5 Feb 2025 12:08:59pm
    Author:  Lino Perdrix

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>

class Generators
{
    public:
    static juce::Array<int> getNotesHigherThan(juce::SortedSet<int>& heldNotes, const juce::Array<int>& availableNotes);
};
