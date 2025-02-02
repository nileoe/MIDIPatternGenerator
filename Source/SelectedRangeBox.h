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
#include "NoteSetKeyboard.h"

//==============================================================================
/*
*/
class SelectedRangeBox  : public juce::GroupComponent
{
public:
    SelectedRangeBox(NoteSetKeyboard& keyboard, NoteSet& patternNoteSet);
    void resized() override;
//    void handleKeyboardEvent(int midiNoteNumber); // todo const?
    
private:
    void updateSelectedRangeText();
    void toggleButton(juce::TextButton* setNoteButton);
    
    NoteSetKeyboard& keyboard;
    NoteSet& patternNoteSet;
    
    juce::String selectedRangeString;
    juce::Label selectedRangeLabel;
    juce::TextButton setLowestNoteButton    { "Set lowest note" };
    juce::TextButton setHighestNoteButton   { "Set highest note" };
    bool settingLowestNoteMode  = false;
    bool settingHighestNoteMode = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectedRangeBox)
};

