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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgorithmSettingsBox)
};
