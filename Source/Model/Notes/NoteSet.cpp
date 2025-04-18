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
    this->lowestNote = 48;
    this->highestNote = 72;
}

NoteSet::NoteSet(Scale scale, RootNote rootNote, int lowestNote, int highestNote) : scale(scale), rootNote(rootNote), lowestNote(lowestNote), highestNote(highestNote)
{
    jassert(lowestNote <= highestNote);
}

NoteSet::NoteSet(Scale scale,
                 RootNote rootNote,
                 juce::Range<int> range) : NoteSet(scale,
                                                   rootNote,
                                                   range.getStart(),
                                                   range.getEnd())
{
}

const juce::Array<int> NoteSet::getNoteIndices() const
{
    juce::Array<int> notes;
    
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
    const juce::Array<int> noteIndices = getNoteIndices();
    for (int noteIndex : noteIndices)
    {
        noteNames.add(juce::MidiMessage::getMidiNoteName(noteIndex, true, true, true));
    }
    return noteNames;
}

int NoteSet::getNoteCount() const
{
    return getNoteIndices().size();
}

const Scale             NoteSet::getScale()         const { return scale; }
const RootNote          NoteSet::getRootNote()      const { return rootNote; };
const juce::Range<int>  NoteSet::getRange()         const { return juce::Range<int>{lowestNote, highestNote}; }
int                     NoteSet::getLowestNote()    const { return lowestNote; }
int                     NoteSet::getHighestNote()   const { return highestNote; }

void NoteSet::setScale(Scale scale)
{
    this->scale = scale;
    sendChangeMessage();
}
void NoteSet::setRootNote(RootNote rootNote)
{
    this->rootNote = rootNote;
    sendChangeMessage();
}

bool NoteSet::setLowestNote(int lowestNote)
{
    if (lowestNote > highestNote)
        return false;
    this->lowestNote = lowestNote;
    sendChangeMessage();
    return true;
}
bool NoteSet::setHighestNote(int highestNote)
{
    if (highestNote < lowestNote)
        return false;
    this->highestNote = highestNote;
    sendChangeMessage();
    return true;
}
void NoteSet::setRange(juce::Range<int> range)
{
    this->lowestNote = range.getStart();
    this->highestNote = range.getEnd();
    sendChangeMessage();
}

const juce::String NoteSet::getDebugInfo() const
{
    juce::String info;
    info += "############ NOTESET INFO ############\n";
    info += "Scale used: " + scale.getName() + " (" + scale.getCategory() + ")" + "\n";
    info += "Root note: " + rootNote.getName() + " (offset = " + juce::String(rootNote.getOffsetFromC()) + ")\n";
    info += "Noteset range: " + juce::MidiMessage::getMidiNoteName(lowestNote, true, true, 0) + " - ";
    info += juce::MidiMessage::getMidiNoteName(highestNote, true, true, 0) + "\n";
    info += "Notes:\n";
    auto noteNames   = getNoteNames();
    auto noteIndices = getNoteIndices();
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

const int NoteSet::findOctaveC(int note)
{
    // In MIDI note mapping, C notes are mapped to multiples of 12: 0, 12, 24, 36, ... up to 120.
    // Using floor division, the line below effectively returns the C at or below the provided note (number).
    return (note / 12) * 12;
}


