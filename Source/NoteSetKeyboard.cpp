/*
 ==============================================================================
 
 ClickableMidiKeyboard.cpp
 Created: 25 Jan 2025 3:40:53pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "NoteSetKeyboard.h"

NoteSetKeyboard::NoteSetKeyboard(juce::MidiKeyboardState& state, juce::Range<int> keyboardRange, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode)
: juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
range(keyboardRange),
patternNoteSet(patternNoteSet),
settingLowestNoteMode(settingLowestNoteMode),
settingHighestNoteMode(settingHighestNoteMode)
{
}

NoteSetKeyboard::NoteSetKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode)
: juce::MidiKeyboardComponent (state, juce::MidiKeyboardComponent::horizontalKeyboard),
state(state),
range(juce::Range<int>(lowestKey, highestKey)),
patternNoteSet(patternNoteSet),
settingLowestNoteMode(settingLowestNoteMode),
settingHighestNoteMode(settingHighestNoteMode)
{
    jassert(lowestKey < highestKey);
}

bool NoteSetKeyboard::mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent& e)
{
    auto& d = AppData::getInstance();
    if (settingLowestNoteMode)
    {
        setPatternLowestNote(midiNoteNumber);
        return true;
    }
    else if (settingHighestNoteMode)
    {
        setPatternHighestNote(midiNoteNumber);
        return true;
    }
    d.log("doing nothing, no low or high mode selected");
    return false;
}


void NoteSetKeyboard::setPatternLowestNote(int lowestNote)
{
    auto& d = AppData::getInstance();
    bool setLowNoteResult = patternNoteSet.setLowestNote(lowestNote);
    if (setLowNoteResult)
    {
        d.log("set low note to ", false);
        d.log(juce::MidiMessage::getMidiNoteName(lowestNote, true, true, 1));
        d.log(patternNoteSet.getDebugInfo());
        return;
    }
    else
    {
        d.log("failed to set lowest note ", false);
        d.log(juce::String(lowestNote));
        d.log("highest note: ", false);
        d.log(juce::String(patternNoteSet.getHighestNote()));
        return;
    }
}
void NoteSetKeyboard::setPatternHighestNote(int highestNote)
{
    auto& d = AppData::getInstance();
    bool setHighNoteResult = patternNoteSet.setHighestNote(highestNote);
    if (setHighNoteResult)
    {
        d.log("set high note to ", false);
        d.log(juce::MidiMessage::getMidiNoteName(highestNote, true, true, 1));
        d.log(patternNoteSet.getDebugInfo());
        return;
    }
    else
    {
        d.log("failed to set highest note ", false);
        d.log(juce::String(highestNote));
        d.log("lowest note: ", false);
        d.log(juce::String(patternNoteSet.getLowestNote()));
        return;
    }
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
