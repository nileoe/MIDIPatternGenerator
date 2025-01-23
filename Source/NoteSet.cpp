/*
  ==============================================================================

    NoteSet.cpp
    Created: 22 Jan 2025 6:25:02pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "NoteSet.h"

NoteSet::NoteSet(Scale scale, int lowestNote, int highestNote) : scale(scale), range(juce::Range(lowestNote, highestNote))
{
}
NoteSet::NoteSet(Scale scale, juce::Range<int> range) : scale(scale), range(range)
{
}

const Scale NoteSet::getScale() const
{
    return scale;
}
int NoteSet::getHighestNote() const
{
    return range.getEnd();
}
int NoteSet::getLowestNote() const
{
    return range.getStart();
}
const juce::Range<int> NoteSet::getRange() const
{
    return range;
}
