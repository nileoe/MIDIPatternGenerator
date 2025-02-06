/*
  ==============================================================================

    Generators.h
    Created: 5 Feb 2025 12:08:59pm
    Author:  Lino Perdrix

  ==============================================================================
*/


#pragma once

#include "GenerationAlgorithm.h"
#include <JuceHeader.h>

class ThreeNGenerator : public GenerationAlgorithm
{
    public:
    ThreeNGenerator(int id);
    
    juce::String getName() const override;
    
    const juce::Array<int> getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes) const override;
};
