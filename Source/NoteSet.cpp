/*
  ==============================================================================

    NoteSet.cpp
    Created: 22 Jan 2025 6:25:02pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "NoteSet.h"

NoteSet::NoteSet(Scale scale, RootNote rootNote, int lowestNote, int highestNote) : scale(scale), rootNote(rootNote), range(juce::Range(lowestNote, highestNote))
{
}
NoteSet::NoteSet(Scale scale, RootNote rootNote, juce::Range<int> range) : scale(scale), rootNote(rootNote), range(range)
{
}

const juce::Array<int> NoteSet::getNotesIndices() const
{
    juce::Array<int> notes;
    const int startNote = range.getStart();
    const int rootNoteOffset = rootNote.getOffsetFromC();
    int octaveC = NoteSet::findOctaveC(startNote);
    int noteIndexInOctave = -1 - rootNoteOffset;
    
    for (int i = octaveC; i <= range.getEnd(); ++i)
    {
        noteIndexInOctave = (noteIndexInOctave + 1) % 12; // todo make this fancy shit
        if (i < startNote)
            continue;
        if (scale.isNoteInScale (noteIndexInOctave))
        {
            notes.add (i);
        }
    }
        
        
//    for (int i = startNote; i <= range.getEnd(); ++i)
//    {
//        int notePositionInOctave = (i - startNote + rootNoteOffset) % 12;
//        if (scale.isNoteInScale(notePositionInOctave))
//        {
//            notes.add (i);
//        }
//    }
    return notes;
}

const juce::StringArray NoteSet::getNoteNames() const
{
    juce::StringArray noteNames;
    const juce::Array<int> noteIndices = getNotesIndices();
    for (int noteIndex : noteIndices)
    {
        noteNames.add(juce::MidiMessage::getMidiNoteName(noteIndex, true, true, true)); // ??????
//        noteNames.add(juce::MidiMessage::getMidiNoteName(noteIndex, true, true, false));
    }
    return noteNames;
}

int NoteSet::getNoteCount() const
{
    return getNotesIndices().size();
}

const Scale             NoteSet::getScale()         const { return scale; }
int                     NoteSet::getLowestNote()    const { return range.getStart(); }
int                     NoteSet::getHighestNote()   const { return range.getEnd(); }
const juce::Range<int>  NoteSet::getRange()         const { return range; }
const RootNote          NoteSet::getRootNote()      const { return rootNote; };

void NoteSet::printInfo() const
{
    std::cout << "############ PRINTING NOTESET INFO ############" << "\n";
    scale.printInfo();
    std::cout << "Scale used: " << scale.getName() << " (" << scale.getCategoryName() << ")" << "\n";
    std::cout << "Root note: " << rootNote.getName() << " (offset = " << rootNote
        .getOffsetFromC() << ")\n";
    std::cout << "Notes:\n";
    auto noteNames   = getNoteNames();
    auto noteIndices = getNotesIndices();
    for (auto i = 0; i < getNoteCount(); ++i)
    {
        std::cout << "\t" << noteIndices[i] << ":\t" << noteNames[i] << "\n";
    }
    std::cout << "\n";
}

int NoteSet::findOctaveC(int note) {
    return note / 12 * 12;
}

