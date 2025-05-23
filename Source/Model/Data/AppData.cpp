/*
  ==============================================================================

    AppData.cpp
    Created: 22 Jan 2025 2:58:40pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "AppData.h"

AppData& AppData::getInstance()
{
    static AppData instance;
    return instance;
}

AppData::~AppData()
{
    for (GenerationAlgorithm* algo : generationAlgorithms)
    {
        delete (algo); // using new so u musts delete them
    }
}

AppData::AppData() noexcept
{
    addRootNotesData();
    addScaleData();
    addNoteValues();
    addGenerationAlgorithms();
}

void AppData::addRootNotesData()
{
    rootNotes.add (RootNote{ "C",     0 });
    rootNotes.add (RootNote{ "C#/Db", 1 });
    rootNotes.add (RootNote{ "D",     2 });
    rootNotes.add (RootNote{ "D#/Eb", 3 });
    rootNotes.add (RootNote{ "E",     4 });
    rootNotes.add (RootNote{ "F",     5 });
    rootNotes.add (RootNote{ "F#/Gb", 6 });
    rootNotes.add (RootNote{ "G",     7 });
    rootNotes.add (RootNote{ "G#/Ab", 8 });
    rootNotes.add (RootNote{ "A",     9 });
    rootNotes.add (RootNote{ "A#/Bb", 10 });
    rootNotes.add (RootNote{ "B",     11 });
}
void AppData::addScaleData()
{
    scales.add (Scale{ "Major",              juce::Array<int>{0, 2, 4, 5, 7, 9, 11},                 "7 notes Major and Minor" });
    scales.add (Scale{ "Melodic Minor",      juce::Array<int>{0, 2, 3, 5, 7, 9, 11},                 "7 notes Major and Minor" });
    scales.add (Scale{ "Natural Minor",      juce::Array<int>{0, 2, 3, 5, 7, 8, 10},                 "7 notes Major and Minor" });
    scales.add (Scale{ "Harmonic Minor",     juce::Array<int>{0, 2, 3, 5, 7, 8, 11},                 "7 notes Major and Minor" });
    scales.add (Scale{ "Harmonic Minor #4",  juce::Array<int>{0, 2, 3, 6, 7, 8, 11},                 "7 notes Major and Minor" });
    scales.add (Scale{ "Pentatonic Major",   juce::Array<int>{0, 2, 4, 7, 9},                        "5 notes standard" });
    scales.add (Scale{ "Chromatic",          juce::Array<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, "Miscellaneous" });
}
void AppData::addNoteValues()
{
    noteValues.add(NoteValue { "Whole notes",            4.0,      false });
    noteValues.add(NoteValue { "Half notes",             2.0,      false });
    noteValues.add(NoteValue { "Quarter notes",          1.0,      false });
    noteValues.add(NoteValue { "8th notes",              0.5,      false });
    noteValues.add(NoteValue { "16th notes",             0.25,     false });
    noteValues.add(NoteValue { "32th notes",             0.125,    false });
    noteValues.add(NoteValue { "Quarter notes triplets", 2.0/3.0,  true });
    noteValues.add(NoteValue { "8th notes triplets",     1.0/3.0,  true });
    noteValues.add(NoteValue { "16th notes triplets",    1.0/6.0,  true });
    noteValues.add(NoteValue { "32th notes triplets",    1.0/12.0, true });
}
void AppData::addGenerationAlgorithms()
{
    int id = 1;
    generationAlgorithms.add (new RandomizerGenerator {id ++});
    generationAlgorithms.add (new ThreeNGenerator     {id ++});
}

const juce::Array<int> AppData::getPattern(juce::SortedSet<int> heldNotes, int lastPressedKey) const
{
    juce::Array<int> targetNotes = PatternSettings::getInstance().getNoteSet().getNoteIndices();
    return getSelectedGenerator()->getPattern(heldNotes, targetNotes, lastPressedKey);
//    return juce::Array<int>();
}

const GenerationAlgorithm* AppData::getSelectedGenerator() const
{
    for (GenerationAlgorithm* algo : generationAlgorithms)
    {
        if (algo->getId() == selectedAlgorithmId)
            return algo;
    }
    return generationAlgorithms.getFirst();
}

juce::String AppData::getSelectedGeneratorName() const
{
    return getSelectedGenerator()->getName();
}


const juce::Array<Scale>&       AppData::getScales()        const { return scales; }
const juce::Array<RootNote>&    AppData::getRootNotes()     const { return rootNotes; }
const juce::Array<NoteValue>    AppData::getNoteValues()    const { return noteValues; }
const juce::Array<GenerationAlgorithm*>& AppData::getGenerationAlgorithms() const
{
    return generationAlgorithms;
}


void AppData::addScale(Scale scale)
{
    scales.add(scale);
}

const Scale* AppData::getScaleById(int id) const
{
    for (const Scale& s : scales)
    {
        if (s.getId() == id)
            return &s;
    }
    return nullptr;
}

const RootNote* AppData::getRootNoteById (int id) const
{
    for (const RootNote& rn : rootNotes)
    {
        if (rn.getId() == id)
            return &rn;
    }
    return nullptr;
}

const RootNote* AppData::getRootNoteByOffsetFromC (int degree) const
{
    for (const RootNote& rn : rootNotes)
    {
        if (rn.getOffsetFromC() == degree)
            return &rn;
    }
    return nullptr;
}

int AppData::getSelectedAlgorithmId() const
{
    return selectedAlgorithmId;
}

void AppData::setSelectedAlgorithmId(int id)
{
    selectedAlgorithmId = id;
}
