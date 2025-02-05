/*
  ==============================================================================

    GenerationMethodsBox.h
    Created: 20 Jan 2025 9:58:15am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RoundRadioButton.h"
#include "AppData.h"

class GenerationMethodsBox  : public juce::GroupComponent
{
    public:
    GenerationMethodsBox (int radioGroupId);
    void updateToggleState (juce::ToggleButton* button); // TODO use
    void resized() override;
    
    private:
    RoundRadioButton    algorithmButton          { "Generate from Algorithm" },
                        melodyButton             { "Generate from Input Melody" };
    juce::ComboBox      algorithmMenu;
    juce::TextButton    selectMelodyButton       { "Select Melody" };
    juce::TextButton    editAlgorithmButton      { "Algorithm Settings" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenerationMethodsBox)
};

