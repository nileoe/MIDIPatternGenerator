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
//    GenerationAlgorithm();
    virtual ~GenerationAlgorithm() = 0;
    virtual const juce::Array<int> getPattern(juce::SortedSet<int>& heldNotes, juce::Array<int>& availableNotes) = 0;
    
    int getId() const;
    
    private:
    static int nextId;
    int id;
    juce::Array<int> availableNotes;
};
