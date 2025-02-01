/*
 ==============================================================================
 
 ClickableMidiKeyboard.cpp
 Created: 25 Jan 2025 3:40:53pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "ClickableMidiKeyboard.h"

ClickableMidiKeyboard::ClickableMidiKeyboard(juce::MidiKeyboardState& state, juce::Range<int> range) : juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
range(range)
{
}

ClickableMidiKeyboard::ClickableMidiKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey) : juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
range(juce::Range<int>(lowestKey, highestKey))
{
    jassert(lowestKey < highestKey);
//    state.isNoteOnForChannels(65536, 72);
}

bool ClickableMidiKeyboard::mouseDownOnKey (int midiNoteNumber, const juce::MouseEvent& e)
{
    std::cout << "mouse down on key " << juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, true) << " called" << "\n";
    juce::Rectangle<float> keyRectangle = getRectangleForKey(midiNoteNumber);
    repaint(keyRectangle.toNearestInt());
    return true;
}

const juce::Range<int> ClickableMidiKeyboard::getRange()                 const { return range; }
int ClickableMidiKeyboard::getLowestKey()                                const { return range.getStart(); }
int ClickableMidiKeyboard::getHighestKey()                               const { return range.getEnd(); }
const juce::MidiKeyboardState& ClickableMidiKeyboard::getKeyboardState() const { return state; }

void ClickableMidiKeyboard::resized()
{
    setAvailableRange (range.getStart(), range.getEnd());
    int whiteKeyCount = (range.getLength()) *  (7.0 / 12.0);
    float whiteKeyWidth = getWidth() / whiteKeyCount;
    setKeyWidth (whiteKeyWidth);
}


