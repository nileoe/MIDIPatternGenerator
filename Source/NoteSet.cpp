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

const juce::Array<int> NoteSet::getNotesIndices() const
{
    juce::Array<int> notes;
    int startNote = range.getStart();
    for (int i = startNote; i <= range.getEnd(); ++i)
    {
        int notePositionInOctave = (i - startNote) % 12;
        if (scale.isNoteInScale(notePositionInOctave))
        {
            notes.add (i);
        }
    }
    return notes;
}
const juce::StringArray NoteSet::getNoteNames() const
{
    juce::StringArray noteNames;
    const juce::Array<int> noteIndices = getNotesIndices();
    for (int noteIndex : noteIndices)
    {
//        noteNames.add(juce::MidiMessage::getMidiNoteName(noteIndex, true, true, true);); // ??????
        noteNames.add(juce::MidiMessage::getMidiNoteName(noteIndex, true, true, false));
    }
    return noteNames;
}

const Scale             NoteSet::getScale()         const { return scale; }
int                     NoteSet::getLowestNote()    const { return range.getStart(); }
int                     NoteSet::getHighestNote()   const { return range.getEnd(); }
const juce::Range<int>  NoteSet::getRange()         const { return range; }
