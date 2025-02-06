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
    juce::Array<int> pattern = {24, 36, 48, 60};
    return pattern;
}


juce::String RandomizerGenerator::getName() const
{
    return "Randomizer";
}
