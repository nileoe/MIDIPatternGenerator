/*
 ==============================================================================
 
 ClickableMidiKeyboard.h
 Created: 21 Jan 2025 2:03:51pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

class ClickableMidiKeyboard  : public juce::MidiKeyboardComponent
{
    public:
    ClickableMidiKeyboard(juce::MidiKeyboardState& state, juce::Range<int> range);
    ClickableMidiKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey);

    bool mouseDownOnKey (int midiNoteNumber, const juce::MouseEvent& e) override;
//    void paint (juce::Graphics& g) override;

    const juce::Range<int> getRange() const;
    int getLowestKey()                const;
    int getHighestKey()               const;
    const juce::MidiKeyboardState& getKeyboardState()  const;
    
    void resized() override;
    
    private:
    juce::MidiKeyboardState& state;
    juce::Range<int> range;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClickableMidiKeyboard)
};


