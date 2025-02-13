/*
  ==============================================================================

    Generators.h
    Created: 5 Feb 2025 12:08:59pm
    Author:  Lino Perdrix

  ==============================================================================
*/


#pragma once

#include "../Data/PatternSettings.h"
#include "../GenerationAlgorithm.h"
#include <JuceHeader.h>

class ThreeNGenerator : public GenerationAlgorithm
{
    public:
    ThreeNGenerator(int id);
    juce::String getName() const override;
    const juce::Array<int> getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const override;
    
    private:
    int findClosestValidNoteIndex (juce::Array<int> notes, int targetNote) const;
    int getNextIndex (int currentIndex) const;
    int findMaximumElement (juce::Array<int> arr) const;
};
