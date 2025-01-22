/*
  ==============================================================================

    Scale.h
    Created: 22 Jan 2025 4:24:51pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Scale
{
    public:
    Scale(juce::String name, juce::String categoryName, juce::Array<bool> notePattern);
    Scale(juce::String name, juce::String categoryName, juce::Array<int>  noteIndices);

    const juce::String&  getName() const;
    const juce::String&  getCategoryName() const;
    const juce::Array<int>&  getNoteIndices() const;
    const juce::Array<bool>& getNotePattern() const;
    int getNoteCount() const;
    
    bool isNoteInScale(int note) const;

    private:
    juce::String name;
    juce::String categoryName;
    juce::Array<int> noteIndices;
    juce::Array<bool> notePattern;
};
