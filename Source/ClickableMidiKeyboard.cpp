/*
 ==============================================================================
 
 ClickableMidiKeyboard.cpp
 Created: 25 Jan 2025 3:40:53pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "ClickableMidiKeyboard.h"

ClickableMidiKeyboard::ClickableMidiKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey) : juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
lowestKey(lowestKey),
highestKey(highestKey)
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

// void paint (juce::Graphics& g)
// {
// }
    

const juce::Range<int> ClickableMidiKeyboard::getRange()                 const { return juce::Range<int>(lowestKey, highestKey); }
int ClickableMidiKeyboard::getLowestKey()                                const { return lowestKey; }
int ClickableMidiKeyboard::getHighestKey()                               const { return highestKey; }
const juce::MidiKeyboardState& ClickableMidiKeyboard::getKeyboardState() const { return state; }

void ClickableMidiKeyboard::resized()
{
    setAvailableRange (lowestKey, highestKey);
    int whiteKeyCount = (highestKey - lowestKey + 1) *  (7.0 / 12.0);
    float whiteKeyWidth = getWidth() / whiteKeyCount;
    setKeyWidth (whiteKeyWidth);
}


