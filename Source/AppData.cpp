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

//AppData::AppData() noexcept : algorithms(juce::StringArray()), scales(juce::Array<Scale>()), rootNotes(juce::Array<RootNote>())
AppData::AppData() noexcept
{
    algorithms.add("Algo 1");
    algorithms.add("Algo 2");
    algorithms.add("Algo 3");
    algorithms.add("Algo 4");

    
    scales.add (Scale{"major",           juce::Array<int>{0, 2, 4, 5, 7, 9, 11}, "7 notes standard"});
    scales.add (Scale{"melodic minor",   juce::Array<int>{0, 2, 3, 5, 7, 9, 11}, "7 notes standard"});
    scales.add (Scale{"natural minor",   juce::Array<int>{0, 2, 3, 5, 7, 8, 10}, "7 notes standard"});
    scales.add (Scale{"harmonic minor",  juce::Array<int>{0, 2, 3, 5, 7, 9, 11}});

    rootNotes.add (RootNote{"C",     0});
    rootNotes.add (RootNote{"C#/Db", 1});
    rootNotes.add (RootNote{"D",     2});
    rootNotes.add (RootNote{"D#/Eb", 3});
    rootNotes.add (RootNote{"E",     4});
    rootNotes.add (RootNote{"F",     5});
    rootNotes.add (RootNote{"F#/Gb", 6});
    rootNotes.add (RootNote{"G",     7});
    rootNotes.add (RootNote{"G#/Ab", 8});
    rootNotes.add (RootNote{"A",     9});
    rootNotes.add (RootNote{"A#/Bb", 10});
    rootNotes.add (RootNote{"B",     11});
}

const juce::StringArray&        AppData::getAlgorithms()    const { return algorithms; }
const juce::Array<Scale>&       AppData::getScales()        const { return scales; }
const juce::Array<RootNote>&    AppData::getRootNotes()     const { return rootNotes; }

void AppData::addScale(Scale scale)
{
    scales.add(scale);
}
