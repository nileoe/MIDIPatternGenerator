/*
  ==============================================================================

    Randomizer.cpp
    Created: 5 Feb 2025 1:45:33pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "RandomizerGenerator.h"
#include <random>

//RandomizerGenerator::~GenerationAlgorithm() {}

//RandomizerGenerator::RandomizerGenerator() {}

//RandomizerGenerator::RandomizerGenerator(juce::SortedSet<int>& heldNotes, juce::Array<int>& availableNotes)
//    : GenerationAlgorithm(heldNotes, availableNotes)
//
//RandomizerGenerator::RandomizerGenerator(juce::SortedSet<int>& heldNotes, juce::Array<int>& targetNotes)
//    : heldNotes(heldNotes), targetNotes(targetNotes)
//{}

juce::Array<int> RandomizerGenerator::getPattern()
{
    juce::Array<int> pattern = {24, 36, 48, 60};
    return pattern;
}

int RandomizerGenerator::getAlgorithmId() const
{
    return 1;
}
