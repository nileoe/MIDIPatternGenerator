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
    GenerationAlgorithm(int id) : id(id)
    {
        DBG ("Created new generation algorithm with id " << id);
    }

    virtual ~GenerationAlgorithm() {}
    
    virtual const juce::Array<int> getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const = 0;
    
    virtual juce::String getName() const = 0;
    
    int getId() const
    {
        return id;
    }
    
    private:
    int id; // mention: no setter for security
};

