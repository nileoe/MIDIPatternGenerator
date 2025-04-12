/*
 ==============================================================================
 
 ClickableMidiKeyboard.h
 Created: 21 Jan 2025 2:03:51pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#pragma once

#include "../../Model/Data/PatternSettings.h"
#include <JuceHeader.h>
//#include "AppData.h"

class NoteSetKeyboard  : public juce::MidiKeyboardComponent, public juce::ChangeListener
{
    public:
    NoteSetKeyboard(juce::MidiKeyboardState& state, juce::Range<int> keyboardRange, bool& settingLowestNoteMode, bool& settingHighestNoteMode);
    NoteSetKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey, bool& settingLowestNoteMode, bool& settingHighestNoteMode);
    
    void mouseUpOnKey(int midiNoteNumber, const juce::MouseEvent& e) override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    const juce::Range<int> getRange() const;
    int getLowestKey()                const;
    int getHighestKey()               const;
    const juce::MidiKeyboardState& getKeyboardState()  const;
    
    void resized() override;
    
    private:
    void syncStateWithNoteSet();
    
    void setPatternLowestNote(int lowestNote);
    void setPatternHighestNote(int highestNote);
    
    juce::MidiKeyboardState& state;
    juce::Range<int> range;
    
    bool& settingLowestNoteMode;
    bool& settingHighestNoteMode;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteSetKeyboard)
};
