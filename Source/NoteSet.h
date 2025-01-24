/*
  ==============================================================================

    NoteSet.h
    Created: 22 Jan 2025 6:25:02pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Scale.h"

class NoteSet
{
    public:
//    NoteSet();
    NoteSet(Scale scale, int lowestNote, int highestNote);
    NoteSet(Scale scale, juce::Range<int> range);

    const juce::Array<int>  getNotesIndices()   const;
    const juce::StringArray getNoteNames()      const;
    
    const Scale             getScale()          const;
    int                     getLowestNote()     const;
    int                     getHighestNote()    const;
    const juce::Range<int>  getRange()          const;

    private:
    Scale scale;
    juce::Range<int> range;
};
