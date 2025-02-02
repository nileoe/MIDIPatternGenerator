/*
  ==============================================================================

    NoteSet.h
    Created: 22 Jan 2025 6:25:02pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "Scale.h"
#include "RootNote.h"
//#include "AppData.h" // <- Unleashes chaos
#include <JuceHeader.h>

class NoteSet
{
    public:
    NoteSet();
    NoteSet(Scale scale, RootNote rootNote, int lowestNote, int highestNote);
    NoteSet(Scale scale, RootNote rootNote, juce::Range<int> range);

    const juce::Array<int>  getNotesIndices()   const;
    const juce::StringArray getNoteNames()      const;
    int getNoteCount() const;

    const Scale getScale()            const;
    const RootNote getRootNote()      const;
    const juce::Range<int> getRange() const;
    int getLowestNote()               const;
    int getHighestNote()              const;
    
    void setScale(Scale);
    void setRootNote(RootNote);
    void setLowestNote(int lowestNote);
    void setHighestNote(int highestNote);
    void setRange(juce::Range<int>);

    const juce::String getDebugInfo() const;

    private:
    static int findOctaveC(int note);
    
    Scale scale;
    RootNote rootNote;
    int lowestNote;
    int highestNote;
//    juce::Range<int> range;
};

