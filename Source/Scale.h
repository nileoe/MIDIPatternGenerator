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
    Scale();
    Scale(const Scale& other);
    Scale(juce::String name, juce::Array<bool>  notePattern, juce::String categoryName = "None");
    Scale(juce::String name, juce::Array<int>   noteIndices, juce::String categoryName = "None");
    
    int                         getId()             const;
    const juce::String&         getName()           const;
    const juce::String&         getCategoryName()   const;
    const juce::Array<int>&     getNoteIndices()    const;
    const juce::Array<bool>&    getNotePattern()    const;
    int                         getNoteCount()      const;
    
    bool isNoteInScale(int note) const;
    void printInfo() const;

    private:
    static int nextId;
    int id;
    juce::String name;
    juce::Array<int> noteIndices;
    juce::Array<bool> notePattern;
    juce::String categoryName;
};

class RootNote
{
    public:
    RootNote();
    RootNote(juce::String name, int offsetFromC);

    const juce::String&         getName()           const;
    int                         getOffsetFromC()         const;
    int                         getId()             const;

    void printInfo() const;

    private:
    static int nextId;
    int id;
    juce::String name;
    int offsetFromC;
};
