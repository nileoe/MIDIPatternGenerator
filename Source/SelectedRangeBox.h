/*
  ==============================================================================

    SelectedRangeBox.h
    Created: 22 Jan 2025 9:17:08am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppData.h"
#include "ClickableMidiKeyboard.h"

//==============================================================================
/*
*/
class SelectedRangeBox  : public juce::GroupComponent
{
public:
//    SelectedRangeBox(juce::MidiKeyboardState& keyboardState, int& patternLowestNote, int& patternHighestNote);
    SelectedRangeBox(ClickableMidiKeyboard& keyboard,
                     int& patternLowestNote,
                     int& patternHighestNote);
    void resized() override;

private:
    void updateSelectedRangeText();
    void toggleButton(juce::TextButton* setNoteButton);
    
//    juce::MidiKeyboardState& keyboardState;
    ClickableMidiKeyboard& keyboard;
    int& patternLowestNote;
    int& patternHighestNote;
    
    juce::String selectedRangeString;
    juce::Label selectedRangeLabel;
    juce::TextButton setLowestNoteButton    { "Set lowest note" };
    juce::TextButton setHighestNoteButton   { "Set highest note" };
    bool settingLowestNoteMode  = false;
    bool settingHighestNoteMode = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectedRangeBox)
};

