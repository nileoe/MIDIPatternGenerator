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
#include <JuceHeader.h>

//==============================================================================
/*
*/
class AlgorithmSettingsBox  : public juce::GroupComponent, public juce::ChangeListener, public juce::Timer
{
public:
    AlgorithmSettingsBox(ArpAlgoAudioProcessor& p);

    void resized() override;
    
    void timerCallback() override;
    
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void log(juce::String dbgText, bool shouldAppendNewline = true);

private:
    void syncTextWithCurrentAlgorithm();
    juce::TextEditor debugBox;
    ArpAlgoAudioProcessor& processor;
    
    juce::Label bpmLabel { "bpmLabel", "Unable to get project BPM"};
    juce::Label speedMenuLabel { "speedMenuLabel", "Pattern note speed"};
    juce::ComboBox speedMenu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgorithmSettingsBox)
};
