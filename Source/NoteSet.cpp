/*
  ==============================================================================

    NoteSet.cpp
    Created: 22 Jan 2025 6:25:02pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "NoteSet.h"

NoteSet::NoteSet()
{
//    auto& d = AppData::getInstance();
//    scale = d.getDefaultScale();
//
//    Scale scale;
//    RootNote rootNote;
//    juce::Range<int> range;
}

NoteSet::NoteSet(Scale scale, RootNote rootNote, int lowestNote, int highestNote) : scale(scale), rootNote(rootNote), lowestNote(lowestNote), highestNote(highestNote)
{
    jassert(lowestNote <= highestNote);
}

NoteSet::NoteSet(Scale scale, RootNote rootNote, juce::Range<int> range) : scale(scale), rootNote(rootNote)
{
    this->lowestNote  = range.getStart();
    this->highestNote = range.getEnd();
}

const juce::Array<int> NoteSet::getNotesIndices() const
{
    juce::Array<int> notes;
    
//    const int startNote = range.getStart();
    const int rootNoteOffset = rootNote.getOffsetFromC();
    int octaveC = NoteSet::findOctaveC(lowestNote);
    int noteIndexInOctave = -1 - rootNoteOffset;
    if (noteIndexInOctave < 0)
    {
        noteIndexInOctave += 12;
    }
    
    noteIndexInOctave += lowestNote - octaveC;
    for (int i = lowestNote; i <= highestNote; ++i)
    {
        noteIndexInOctave = (++ noteIndexInOctave) % 12;
        if (scale.doesNoteDegreeBelongToScale (noteIndexInOctave))
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
        noteNames.add(juce::MidiMessage::getMidiNoteName(noteIndex, true, true, true));
    }
    return noteNames;
}

int NoteSet::getNoteCount() const
{
    return getNotesIndices().size();
}

const Scale             NoteSet::getScale()         const { return scale; }
const RootNote          NoteSet::getRootNote()      const { return rootNote; };
const juce::Range<int>  NoteSet::getRange()         const { return juce::Range<int>{lowestNote, highestNote}; }
int                     NoteSet::getLowestNote()    const { return lowestNote; }
int                     NoteSet::getHighestNote()   const { return highestNote; }

void NoteSet::setScale(Scale scale)                 { this->scale = scale; }
void NoteSet::setRootNote(RootNote rootNote)        { this->rootNote = rootNote; }
void NoteSet::setLowestNote(int lowestNote)         { this->lowestNote = lowestNote; }
void NoteSet::setHighestNote(int highestNote)       { this->highestNote = highestNote; }
void NoteSet::setRange(juce::Range<int> range)
{
    this->lowestNote = range.getStart();
    this->highestNote = range.getEnd();
}

const juce::String NoteSet::getDebugInfo() const
{
    juce::String info;
    info += "############ PRINTING NOTESET INFO ############\n";
    info += "Scale used: " + scale.getName() + " (" + scale.getCategoryName() + ")" + "\n";
    info += "Root note: " + rootNote.getName() + " (offset = " + juce::String(rootNote.getOffsetFromC()) + ")\n";
    info += "Notes:\n";
    auto noteNames   = getNoteNames();
    auto noteIndices = getNotesIndices();
    if (noteIndices.size() == 0)
    {
        info += "No notes";
    }
    else
    {
        for (auto i = 0; i < getNoteCount(); ++i)
        {
            info += "\t" + juce::String(noteIndices[i]) + ":\t" + juce::String(noteNames[i]) + "\n";
        }
        info += "\n";
    }
    return info;
}

int NoteSet::findOctaveC(int note) {
    // In MIDI note mapping, C notes are 0, 12, 24, 36 ... up to 120. Using floor division,
    // the line below effectively returns the C at or below the provided note index.
    return (note / 12) * 12;
}


