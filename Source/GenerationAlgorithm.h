/*
  ==============================================================================

    GenerationAlgorithm.h
    Created: 4 Feb 2025 6:56:48pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class GenerationAlgorithm
{
    public:
    GenerationAlgorithm();
    const juce::Array<int> getPattern(juce::SortedSet<int>& heldNotes, juce::Array<int>& targetNotes) const;
    
    int getId() const;
    
    private:
    static int nextId;
    int id;
};
