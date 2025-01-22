/*
  ==============================================================================

    AppData.h
    Created: 22 Jan 2025 2:58:40pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AppData
{
public:
    static AppData& getInstance();

    const juce::StringArray& getAlgorithms() const;
    const juce::StringArray& getScales() const;
    const juce::StringArray& getRootNotes() const;

private:
    juce::StringArray algorithms;
    juce::StringArray scales;
    juce::StringArray rootNotes;

    AppData() noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppData)
};
