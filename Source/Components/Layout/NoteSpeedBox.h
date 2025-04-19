/*
  ==============================================================================

    AlgorithmSettingsBox.h
    Created: 13 Feb 2025 1:52:32pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

//#include "../../Model/Data/AppData.h"
#include "../../PluginProcessor.h"
#include "../../Model/Notes/NoteValue.h"
#include "../../Model/Data/PatternSettings.h"
#include <JuceHeader.h>

//==============================================================================
class NoteSpeedBox  : public juce::GroupComponent, public juce::ChangeListener, public juce::Timer
{
public:
    NoteSpeedBox(ArpAlgoAudioProcessor& p);

    void resized() override;
    
    void timerCallback() override;
    
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void log(juce::String dbgText, bool shouldAppendNewline = true);

private:
    void handleSpeedMenuChange();
    void handleMergeRepeatNotesChange();
    void populateSpeedMenu();
    NoteValue getSelectedSpeedValue();
    
    void syncTextWithCurrentAlgorithm();
    juce::TextEditor debugBox;
    ArpAlgoAudioProcessor& processor;
    
    juce::Label bpmLabel { "bpmLabel", "Project BPM:"};
    juce::Label bpmValueLabel { "bpmValueLabel", "Not found"};
    juce::Label speedMenuLabel { "speedMenuLabel", "Min. note duration"};
    juce::ComboBox speedMenu;
    juce::ToggleButton mergeRepeatedNotesCheckBox { "Merge repeated notes" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteSpeedBox)
};
