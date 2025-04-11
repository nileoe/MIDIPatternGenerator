/*
  ==============================================================================

    GenerationAlgorithm.h
    Created: 4 Feb 2025 6:56:48pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

//#include "./Data/PatternSettings.h"
#include <JuceHeader.h>

class GenerationAlgorithm
{
    public:
    GenerationAlgorithm(int id) : id(id)
    {
    }

    virtual ~GenerationAlgorithm() {}
    
    virtual const juce::Array<int> getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const = 0;
    
    virtual juce::String getName()        const = 0;
    virtual juce::String getDescription() const = 0;

    int getId() const
    {
        return id;
    }
    
    private:
    int id;
};

