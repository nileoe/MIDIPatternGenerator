/*
  ==============================================================================

    SelectedRangeBox.h
    Created: 22 Jan 2025 9:17:08am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "AppData.h"
#include "../MIDI/NoteSetKeyboard.h"

class SelectedRangeBox  : public juce::GroupComponent, public juce::ChangeListener
{
public:
    SelectedRangeBox(NoteSetKeyboard& keyboard, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode);
    void resized() override;
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    
private:
    void updateSelectedRangeText();
    void toggleButton(juce::TextButton* setNoteButton);
    void resetButton(juce::TextButton* setNoteButton);
    
    NoteSetKeyboard& keyboard;
    NoteSet& patternNoteSet;
    
    juce::String selectedRangeString;
    juce::Label selectedRangeLabel;
    juce::TextButton setLowestNoteButton    { "Set lowest note" };
    juce::TextButton setHighestNoteButton   { "Set highest note" };
    
    bool& settingLowestNoteMode;
    bool& settingHighestNoteMode;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectedRangeBox)
};

