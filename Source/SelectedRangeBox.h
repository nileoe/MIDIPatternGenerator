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

//==============================================================================
/*
*/
class SelectedRangeBox  : public juce::GroupComponent
{
public:
    SelectedRangeBox(juce::MidiKeyboardState& keyboardState, int& patternLowestNote, int& patternHighestNote);
    void resized() override;

private:
    void updateSelectedRangeText();
    void toggleButton(juce::TextButton* setNoteButton);
    
    juce::MidiKeyboardState& keyboardState;
    int& patternLowestNote;
    int& patternHighestNote;
    
    juce::String selectedRangeString;
    juce::Label selectedRangeLabel;
    juce::TextButton setLowestNoteButton    { "Set lowest note" };
    juce::TextButton setHighestNoteButton   { "Set highest note" };
    
    juce::String activeButtonMessage { "Click note on on-screen keyboard" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectedRangeBox)
};

