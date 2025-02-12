
#include "ThreeNGenerator.h"

ThreeNGenerator::ThreeNGenerator(int id) : GenerationAlgorithm(id) {}

juce::String ThreeNGenerator::getName() const
{
    return "Three N Plus One";
}

const juce::Array<int> ThreeNGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const
{
    DBG ("GETTING PATTERN FOR THREE_N");
    auto& settings = PatternSettings::getInstance();
    juce::Array<int> pattern;
    int patternLength = settings.getLengthInNotes();
    int targetNotesSize = targetNotes.size();
    
    int index = targetNotes.indexOf(lastPressedKey);
    if (index == -1)
        // lastPressedKey does not belong to the noteset
        index = findClosestValidNoteIndex (targetNotes, index);
    
    for (auto i = 0; i < patternLength; ++i)
    {
        if (index < 0)
        {
            DBG ("index is negative: " << index);
            jassertfalse;
        }
        
        pattern.add (targetNotes[(index - 1) % targetNotesSize]);
        DBG ("index is " << index << "\t % (adjusted for) noteset size = " << index % targetNotesSize << ": " << juce::MidiMessage::getMidiNoteName (index, true, true, 0));
        index = getNextIndex(index);
    }
    
    DBG ("FINISHED PATTERN:");
    return pattern;
}

int ThreeNGenerator::getNextIndex(int currentIndex) const
{
    return currentIndex % 2 == 0 ? (currentIndex / 2) : (3 * currentIndex + 1);
}

int ThreeNGenerator::findClosestValidNoteIndex(juce::Array<int> notes, int targetNote) const
{
    DBG ("targetNote not in set: " << juce::MidiMessage::getMidiNoteName(targetNote, true, true, 0));
    // binary search
    int notesLength = notes.size();
    int low = 0;
    int high = notesLength - 1;

    // Handle edge cases
    if (notesLength == 0)
        return -1; // Return -1 if notes array is empty

    if (targetNote <= notes[0])
        return notes[0]; // Return the first element if targetNote is less than or equal to the first element

    if (targetNote >= notes[high])
        return notes[high]; // Return the last element if targetNote is greater than or equal to the last element

    // Binary search for the closest note
    while (low <= high)
    {
        int middle = (low + high) / 2;

        if (notes[middle] == targetNote)
            return notes[middle]; // Return the targetNote if it's exactly found

        if (notes[middle] < targetNote)
            low = middle + 1;
        else
            high = middle - 1;
    }
    
    // Find the closest of the two potential closest values
    int closestLow = notes[high];
    int closestHigh = notes[low];
    
    if (targetNote - closestLow <= closestHigh - targetNote)
    {
        DBG ("returning " << juce::MidiMessage::getMidiNoteName(closestLow, true, true, 0));
        return closestLow;
    }
    else
    {
        DBG ("returning " << juce::MidiMessage::getMidiNoteName(closestHigh, true, true, 0));
        return closestHigh;
    }
}
