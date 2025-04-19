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

juce::String RandomizerGenerator::getName() const
{
    return "Randomizer";
}
juce::String RandomizerGenerator::getDescription() const
{
    return "Generates a random sequence of notes starting from your last pressed key. The pattern uses notes from the selected scale and range, favouring the keys currently being held.";
}

const juce::Array<int> RandomizerGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const
{
    auto& patternSettings = PatternSettings::getInstance();
    int length = patternSettings.getLengthInNotes();
    bool allowOffkeyInputNotes = patternSettings.doesAllowOffKeyInput();
    juce::Array<int> pattern;
    
    juce::Array<int> availableNotes;
    availableNotes.addArray(targetNotes);
    
    juce::Array<int> weightedPool = availableNotes;
    juce::Array<int> usableHeldNotes;
    
    for (auto heldNote : heldNotes)
    {
        // Only add held notes that are either in targetNotes or allowed as off-key input
        if (targetNotes.contains(heldNote) || allowOffkeyInputNotes)
        {
            usableHeldNotes.add(heldNote);
            
            // Increase the number of held notes in the weighed pool to increase their likelyhood
            for (int i = 0; i < 5; ++i)
            {
                weightedPool.add(heldNote);
            }
        }
    }
    
    // Use lastPressedKey as the starting note if it's a valid note
    if (lastPressedKey >= 0 && lastPressedKey <= 127)
    {
        if (targetNotes.contains(lastPressedKey) ||
            (allowOffkeyInputNotes && heldNotes.contains(lastPressedKey)))
        {
            pattern.add(lastPressedKey);
        }
        else
        {
            // If lastPressedKey is not valid, pick a random note
            if (!availableNotes.isEmpty())
            {
                pattern.add(availableNotes[juce::Random::getSystemRandom().nextInt(availableNotes.size())]);
            }
        }
    }
    
    // Fill the rest of the pattern
    for (auto i = pattern.size(); i < length; ++i)
    {
        if (weightedPool.isEmpty())
            break;
        
        // Get a random note from the weighted pool
        int randomIndex = juce::Random::getSystemRandom().nextInt(weightedPool.size());
        int selectedNote = weightedPool[randomIndex];
        
        pattern.add(selectedNote);
    }
    
    jassert(length == pattern.size());
    return pattern;
}
