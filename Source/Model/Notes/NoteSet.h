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
//#include "AppData.h"  // <- Unleashes chaos for some mysterious reason
#include <JuceHeader.h>

class NoteSet : public juce::ChangeBroadcaster
{
    public:
    NoteSet();
    NoteSet(Scale scale, RootNote rootNote, int lowestNote, int highestNote);
    NoteSet(Scale scale, RootNote rootNote, juce::Range<int> range);

    const juce::Array<int>  getNoteIndices()   const;
    const juce::StringArray getNoteNames()      const;
    int getNoteCount() const;

    const Scale getScale()            const;
    const RootNote getRootNote()      const;
    const juce::Range<int> getRange() const;
    int getLowestNote()               const;
    int getHighestNote()              const;
    
    void setScale(Scale);
    void setRootNote(RootNote);
    bool setLowestNote(int lowestNote);
    bool setHighestNote(int highestNote);
    void setRange(juce::Range<int>);

    const juce::String getDebugInfo() const;

    private:
    const static int findOctaveC(int note);
    
    Scale scale;
    RootNote rootNote;
    int lowestNote;
    int highestNote;
};

