/*
  ==============================================================================

    ScaleAndHarmonyBox.h
    Created: 22 Jan 2025 10:40:42am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RoundRadioButton.h"
#include "AppData.h"
#include "NoteSet.h"

class ScaleAndHarmonyBox  : public juce::GroupComponent
{
public:
    ScaleAndHarmonyBox(int scaleHarmonyRadioId, NoteSet& patternNoteSet);
    
    void updateToggleState();
    
    void resized() override;
    

private:
    void updatePatternRootNote();
    void updatePatternScale();

    NoteSet&            patternNoteSet;
    
    RoundRadioButton    useHarmonyRadioButton       { "Use existing harmony to set available pitches" },
                        useScaleRadioButton         { "Choose scale" };
    
    juce::ToggleButton  strictModeTickbox           { "Strict mode" };
    
    juce::ToggleButton  useCustomScaleTickbox;
    juce::ComboBox      rootNoteMenu,
                        scaleMenu;
    juce::TextButton    customScaleButton           { "Use custom scale" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleAndHarmonyBox)
};
