/*
  ==============================================================================

    RootNote.h
    Created: 2 Feb 2025 8:46:04pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RootNote
{
    public:
    RootNote();
    RootNote(juce::String name, int offsetFromC);

    const juce::String& getName()   const;
    int getOffsetFromC()            const;
    int getId()                     const;

    void printInfo() const;

    private:
    static int nextId;
    int id;
    juce::String name;
    int offsetFromC;
};

