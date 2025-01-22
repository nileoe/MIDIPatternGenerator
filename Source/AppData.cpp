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

AppData::AppData() noexcept
:   algorithms { "Algo 1", "Algo 2", "Algo 3", "Algo 4", "Algo 5sldkfjflj" },
    scales { "Major", "Minor", "Pentatonic" },
    rootNotes { "C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B" }
{
}

const juce::StringArray& AppData::getAlgorithms() const { return algorithms; }
const juce::StringArray& AppData::getScales() const { return scales; }
const juce::StringArray& AppData::getRootNotes() const { return rootNotes; }
