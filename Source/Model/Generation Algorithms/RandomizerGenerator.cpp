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

// const juce::Array<int> RandomizerGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes) const
const juce::Array<int> RandomizerGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const
{
    DBG ("Getting pattern for Randomizer");
    int length = PatternSettings::getInstance().getLengthInNotes();
    juce::Array<int> pattern;
    
//    juce::Array<int> offsets = {0, 1, 2, 1, 0, -1, -2, -1};
    for (auto i = 0; i < length; ++i)
    {
//        pattern.add(lastPressedKey + offsets[i % offsets.size()]);
        pattern.add(lastPressedKey + i);
    }
    
    if (length == pattern.size())
    {
        DBG ("Finished pattern of length " << length << " (expected length matches)");
    }
    else
    {
        DBG ("Wrong pattern length: expected " << length << ", got " << pattern.size());
        jassertfalse;
    }
//    for (auto note : pattern)
//    {
//        DBG (juce::MidiMessage::getMidiNoteName(note, true, true, 0)); // TODO
//    }
    
    return pattern;
}


juce::String RandomizerGenerator::getName() const
{
    return "Randomizer";
}
