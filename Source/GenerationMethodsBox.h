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
#include "NoteSet.h"

class GenerationMethodsBox  : public juce::GroupComponent
{
    public:
    GenerationMethodsBox (int radioGroupId, NoteSet& patternNoteSet);
    void updateToggleState (juce::ToggleButton* button); // TODO use
    void resized() override;
    
    private:
    NoteSet&            patternNoteSet;
    RoundRadioButton    algorithmButton          { "Generate from Algorithm" },
                        melodyButton             { "Generate from Input Melody" };
    juce::ComboBox      algorithmMenu;
    juce::TextButton    selectMelodyButton       { "Select Melody" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenerationMethodsBox)
};

