/*
  ==============================================================================

    Randomizer.h
    Created: 5 Feb 2025 1:45:33pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "../Data/PatternSettings.h"
#include "../GenerationAlgorithm.h"
#include <JuceHeader.h>

class RandomizerGenerator : public GenerationAlgorithm
{
    public:
    RandomizerGenerator(int id);
    
    juce::String getName()        const override;
    juce::String getDescription() const override;

    const juce::Array<int> getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const override;
};
