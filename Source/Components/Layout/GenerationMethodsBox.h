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
#include "../../Model/Data/PatternSettings.h"
#include "../../Model/GenerationAlgorithm.h"
#include "../../PluginProcessor.h"
#include <JuceHeader.h>

class GenerationMethodsBox  : public juce::GroupComponent, public juce::ChangeBroadcaster
{
    public:
    GenerationMethodsBox (int radioGroupId, ArpAlgoAudioProcessor& processor);
    void updateToggleState (juce::ToggleButton* button);
    void resized() override;
    
    private:
    void handleAlgorithmChange();
    void handleOffKeyButtonChange();
    ArpAlgoAudioProcessor& audioProcessor;
    
    juce::Label algorithmLabel {"algorithmLabel", "Select Algorithm" };
    juce::ComboBox      algorithmMenu;
    juce::TextButton    editAlgorithmButton      { "Algorithm Settings" };
    juce::ToggleButton  allowOffKeyNotesButton ;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenerationMethodsBox)
};

