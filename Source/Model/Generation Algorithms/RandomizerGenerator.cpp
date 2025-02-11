/*
  ==============================================================================

    Randomizer.cpp
    Created: 5 Feb 2025 1:45:33pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "RandomizerGenerator.h"
#include "../Data/PatternSettings.h"
#include <random>

RandomizerGenerator::RandomizerGenerator(int id) : GenerationAlgorithm(id) {}

// const juce::Array<int> RandomizerGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes) const
const juce::Array<int> RandomizerGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const
{
    DBG ("Getting pattern for Randomizer");
    int length = PatternSettings::getInstance().getLengthInNotes();
    juce::Array<int> pattern;
    
    juce::Array<int> offsets = {0, 1, 2, 1, 0, -1, -2, -1};
    for (auto i = 0; i < length; ++i)
    {
        pattern.add(lastPressedKey + offsets[i % offsets.size()]);
    }
    
    DBG ("finished creating pattern:");
    for (auto note : pattern)
    {
        DBG (juce::MidiMessage::getMidiNoteName(note, true, true, 0));
    }
    
    return pattern;
}


juce::String RandomizerGenerator::getName() const
{
    return "Randomizer";
}
