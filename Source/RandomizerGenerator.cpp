/*
  ==============================================================================

    Randomizer.cpp
    Created: 5 Feb 2025 1:45:33pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "RandomizerGenerator.h"
#include <random>

RandomizerGenerator::RandomizerGenerator(int id) : GenerationAlgorithm(id) {}

const juce::Array<int> RandomizerGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes) const
{
    DBG ("Getting pattern for Randomizer");
    juce::Array<int> pattern = {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70};
    return pattern;
}


juce::String RandomizerGenerator::getName() const
{
    return "Randomizer";
}
