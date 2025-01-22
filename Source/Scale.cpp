/*
  ==============================================================================

    Scale.cpp
    Created: 22 Jan 2025 4:24:51pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "Scale.h"

Scale::Scale(juce::String name, juce::String categoryName, juce::Array<bool> notePattern) : name(name), categoryName(categoryName), notePattern(notePattern)
{
    // scales must follow the 12-note western system.
    jassert (notePattern.size() == 12);
    // set the note indices
    juce::Array<int> noteIndices;
    for (auto i = 0; i < 12; ++i)
    {
        if (notePattern[i])
        {
            noteIndices.add(i);
        }
    }
}

Scale::Scale(juce::String name, juce::String categoryName, juce::Array<int> noteIndices) : name(name), categoryName(categoryName), noteIndices(noteIndices)
{
    // notes indices must be sorted in (strictly) ascending order and range from 0 to 11 inclusive
    for (int i = 0; i < noteIndices.size() - 1; ++i)
    {
        jassert(noteIndices[i] < noteIndices[i + 1]);
    }
    jassert (noteIndices.getFirst() >= 0);
    jassert (noteIndices.getLast() <= 11);
  
    juce::Array<bool> notePattern(false, 12);
    for (auto noteIndex : noteIndices)
    {
        notePattern.set(noteIndex, true);
    }
}

const juce::String& Scale::getName() const
{
    return name;
}

const juce::String& Scale::getCategoryName() const
{
    return categoryName;
}

const juce::Array<int>&  Scale::getNoteIndices() const
{
    return noteIndices;
}

const juce::Array<bool>& Scale::getNotePattern() const
{
    return notePattern;
}

int Scale::getNoteCount() const
{
    return noteIndices.size();
}

bool Scale::isNoteInScale(int noteIndex) const
{
    jassert (noteIndex >= 0 && noteIndex <= 11);
    for (int scaleNote : noteIndices)
    {
        if (scaleNote == noteIndex)
        {
            return true;
        }
    }
    return false;
}

