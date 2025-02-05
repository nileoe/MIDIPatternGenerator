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
    setColour(juce::MidiKeyboardComponent::keyDownOverlayColourId,
              juce::Colour(152, 188, 196));
    setColour(juce::MidiKeyboardComponent::mouseOverKeyOverlayColourId,
              juce::Colour(212, 248, 255));
}

NoteSetKeyboard::NoteSetKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode)
: NoteSetKeyboard(state,
                  juce::Range<int>{lowestKey, highestKey},
                  patternNoteSet,
                  settingLowestNoteMode,
                  settingHighestNoteMode)
{
}

void NoteSetKeyboard::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    syncStateWithNoteSet();
}


bool NoteSetKeyboard::mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent& e)
{
    if (!(settingLowestNoteMode || settingHighestNoteMode))
    {
        DBG ("No setting mode currently active: ignoring click");
        return false;
    }
    if (settingLowestNoteMode)
    {
        setPatternLowestNote(midiNoteNumber);
    }
    else if (settingHighestNoteMode)
    {
        setPatternHighestNote(midiNoteNumber);
    }
    sendChangeMessage();
    return true;
}

void NoteSetKeyboard::syncStateWithNoteSet()
{
    const juce::Array<int>& noteSetNotes = patternNoteSet.getNotesIndices();
    state.allNotesOff(1);
    for (int note : noteSetNotes)
    {
        float velocity = note % 2 == 0 ? 0.2f : 1.0f;
//        state.noteOn(1, note, 1.0f);
        state.noteOn(1, note, velocity);
    }
}

void NoteSetKeyboard::setPatternLowestNote(int lowestNote)
{
    bool setLowestNoteWasSuccessful = patternNoteSet.setLowestNote(lowestNote);
    if (setLowestNoteWasSuccessful)
    {
        settingLowestNoteMode = false;
        return;
    }
    else
    {
        return;
    }
}
void NoteSetKeyboard::setPatternHighestNote(int highestNote)
{
    bool setHighestNoteWasSuccessful = patternNoteSet.setHighestNote(highestNote);
    if (setHighestNoteWasSuccessful)
    {
        settingHighestNoteMode = false;
        return;
    }
    else
    {
        return;
    }
}

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
