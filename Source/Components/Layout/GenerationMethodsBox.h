/*
  ==============================================================================

    GenerationMethodsBox.h
    Created: 20 Jan 2025 9:58:15am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "../UI/RoundRadioButton.h"
#include "../../Model/Data/AppData.h"
#include "../../Model/GenerationAlgorithm.h"
#include "../../PluginProcessor.h"
#include <JuceHeader.h>

class GenerationMethodsBox  : public juce::GroupComponent, public juce::ChangeBroadcaster
{
    public:
    GenerationMethodsBox (int radioGroupId, ArpAlgoAudioProcessor& processor);
    void updateToggleState (juce::ToggleButton* button); // TODO use
    void resized() override;
    
    private:
    void handleAlgorithmChange();
    ArpAlgoAudioProcessor& audioProcessor;
    
    juce::Label algorithmLabel {"algorithmLabel", "Select generation algorithm" };
    juce::ComboBox      algorithmMenu;
    juce::TextButton    editAlgorithmButton      { "Algorithm Settings" };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenerationMethodsBox)
};

