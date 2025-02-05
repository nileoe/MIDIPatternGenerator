

/*
  ==============================================================================

    Generators.cpp
    Created: 5 Feb 2025 12:08:59pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "Generators.h"

juce::Array<int> Generators::getNotesHigherThan(juce::SortedSet<int>& heldNotes, const juce::Array<int>& availableNotes)
{
    jassert(!heldNotes.isEmpty());
    const int lowestHeldNote = heldNotes.getFirst();
    juce::Array<int> pattern;
    
    for (const int note : availableNotes)
    {
        if (note >= lowestHeldNote)
        {
            pattern.add(note);
        }
    }
    return pattern;
}
