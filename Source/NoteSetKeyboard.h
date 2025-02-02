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
    NoteSetKeyboard(juce::MidiKeyboardState& state, juce::Range<int> keyboardRange, NoteSet& patternNoteSet);
    NoteSetKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey, NoteSet& patternNoteSet);
    
    bool mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent& e) override
    {
        auto& d = AppData::getInstance();
        d.log("note played");
        d.log(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 0));
        d.log(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 1));
        d.log(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 2));
        d.log(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 3));
        d.log(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 4));
        d.log(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 5));
        return true;
    }

//    std::function<void(int)> onMouseDownOnKey;
//
//      bool mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent& e) override
//      {
//          if (onMouseDownOnKey)
//              onMouseDownOnKey(midiNoteNumber);
//          return true;
//      }
    
    const juce::Range<int> getRange() const;
    int getLowestKey()                const;
    int getHighestKey()               const;
    const juce::MidiKeyboardState& getKeyboardState()  const;
    
    void resized() override;
    
    private:
    juce::MidiKeyboardState& state;
    juce::Range<int> range;
    NoteSet& patternNoteSet;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteSetKeyboard)
};
