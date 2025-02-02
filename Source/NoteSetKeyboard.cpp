/*
 ==============================================================================
 
 ClickableMidiKeyboard.cpp
 Created: 25 Jan 2025 3:40:53pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "NoteSetKeyboard.h"

NoteSetKeyboard::NoteSetKeyboard(juce::MidiKeyboardState& state, juce::Range<int> keyboardRange, NoteSet& patternNoteSet) : juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
range(keyboardRange),
patternNoteSet(patternNoteSet)
{
}

NoteSetKeyboard::NoteSetKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey, NoteSet& patternNoteSet) :
juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
range(juce::Range<int>(lowestKey, highestKey)),
patternNoteSet(patternNoteSet)
{
    jassert(lowestKey < highestKey);
//    state.isNoteOnForChannels(65536, 72);
}

//bool ClickableMidiKeyboard::mouseDownOnKey (int midiNoteNumber, const juce::MouseEvent& e)
//{
//    std::cout << "mouse down on key " << juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, true) << " called" << "\n";
//    juce::Rectangle<float> keyRectangle = getRectangleForKey(midiNoteNumber);
//    repaint(keyRectangle.toNearestInt());
//    return true;
//}

const juce::Range<int> NoteSetKeyboard::getRange()                 const { return range; }
int NoteSetKeyboard::getLowestKey()                                const { return range.getStart(); }
int NoteSetKeyboard::getHighestKey()                               const { return range.getEnd(); }
const juce::MidiKeyboardState& NoteSetKeyboard::getKeyboardState() const { return state; }

void NoteSetKeyboard::resized()
{
    setAvailableRange (range.getStart(), range.getEnd());
    int whiteKeyCount = (range.getLength()) *  (7.0 / 12.0);
    float whiteKeyWidth = getWidth() / whiteKeyCount;
    setKeyWidth (whiteKeyWidth);
}


