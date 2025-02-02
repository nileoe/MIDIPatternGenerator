/*
 ==============================================================================
 
 ClickableMidiKeyboard.h
 Created: 21 Jan 2025 2:03:51pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "NoteSet.h"
#include "AppData.h"

class NoteSetKeyboard  : public juce::MidiKeyboardComponent
{
    public:
    NoteSetKeyboard(juce::MidiKeyboardState& state, juce::Range<int> keyboardRange, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode);
    NoteSetKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode);

    bool mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent& e) override;

    const juce::Range<int> getRange() const;
    int getLowestKey()                const;
    int getHighestKey()               const;
    const juce::MidiKeyboardState& getKeyboardState()  const;
    
    void resized() override;
    
    private:
    void setPatternLowestNote(int lowestNote);
    void setPatternHighestNote(int highestNote);
    
    juce::MidiKeyboardState& state;
    juce::Range<int> range;
    NoteSet& patternNoteSet;
    
    bool& settingLowestNoteMode;
    bool& settingHighestNoteMode;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteSetKeyboard)
};
