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
: NoteSetKeyboard(state,
                  juce::Range<int>{lowestKey, highestKey},
                  patternNoteSet,
                  settingLowestNoteMode,
                  settingHighestNoteMode)
{
}

NoteSetKeyboard::~NoteSetKeyboard()
{
    removeAllChangeListeners();
}

void NoteSetKeyboard::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    syncStateWithNoteSet();
}


bool NoteSetKeyboard::mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent& e)
{
    if (!(settingLowestNoteMode || settingHighestNoteMode))
    {
        AppData::getInstance().log("No setting mode currently active: ignoring click");
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
    syncStateWithNoteSet();
    return true;
}

void NoteSetKeyboard::syncStateWithNoteSet()
{
    auto& d = AppData::getInstance();
    d.log("Sync notes with state (keyboard), current noteset is");
    d.log(patternNoteSet.getDebugInfo());
    const juce::Array<int>& noteSetNotes = patternNoteSet.getNotesIndices();
    state.allNotesOff(1);
    for (int note : noteSetNotes)
    {
        d.log("activating note " + juce::String(note) + " " + juce::MidiMessage::getMidiNoteName(note, true, true, 0));
        state.noteOn(1, note, 127);
    }
}

void NoteSetKeyboard::setPatternLowestNote(int lowestNote)
{
    auto& d = AppData::getInstance();
    bool setLowestNoteWasSuccessful = patternNoteSet.setLowestNote(lowestNote);
    if (setLowestNoteWasSuccessful)
    {
        settingLowestNoteMode = false;
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
    bool setHighestNoteWasSuccessful = patternNoteSet.setHighestNote(highestNote);
    if (setHighestNoteWasSuccessful)
    {
        settingHighestNoteMode = false;
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
