
#include "ThreeNGenerator.h"

ThreeNGenerator::ThreeNGenerator(int id) : GenerationAlgorithm(id) {}

juce::String ThreeNGenerator::getName() const
{
    return "Three N Plus One";
}
juce::String ThreeNGenerator::getDescription() const
{
    return "Follows a specific number sequence to jump between notes, forming a fixed size pattern using your last pressed key and the allowed notes.";
}

const juce::Array<int> ThreeNGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const
{
    auto& settings = PatternSettings::getInstance();
    juce::Array<int> patternIndexes;
    int patternLength = settings.getLengthInNotes();
    if (settings.doesAllowOffKeyInput())
    {
        for (int note : heldNotes)
        {
            if (!targetNotes.contains(note))
            {
                targetNotes.add(note);
            }
        }
    }
    int targetNotesSize = targetNotes.size();
    
    int index = findClosestValidNoteIndex (targetNotes, lastPressedKey);
    
    for (auto i = 0; i < patternLength; ++i)
    {
        if (index < 0)
        {
            DBG ("Error: index is negative: " << index);
            jassertfalse;
        }
        
        if (index == 1) break;
        patternIndexes.add (index);
        DBG ("Index is " << index);
        index = getNextIndex(index);
    }
    
    // fit into range
    double maxObtainedIndex = findMaximumElement(patternIndexes);
    int maxAvailableIndex = targetNotesSize - 1;
    double modifier = (double) maxAvailableIndex / (double) maxObtainedIndex;
    DBG ("max obtained index:\t" << maxObtainedIndex);
    DBG ("max available index:\t" << maxAvailableIndex);
    DBG ("modifier:\t\t*" << modifier << " (/" << (double) 1/modifier << ")");

    
    juce::Array<int> pattern;
    for (int index : patternIndexes)
    {
        int adjustedIndex = index * modifier;
        pattern.add(targetNotes[adjustedIndex]);
        DBG ("added new index, from " << index << " to " << adjustedIndex);
    }
    

    DBG ("\n############### finished pattern ###############");
    return pattern;
}

int ThreeNGenerator::getNextIndex(int currentIndex) const
{
    return currentIndex % 2 == 0 ? (currentIndex / 2) : (3 * currentIndex + 1);
}

int ThreeNGenerator::findClosestValidNoteIndex(juce::Array<int> notes, int targetNote) const
{
    int notesLength = notes.size();
    jassert(notesLength != 0);
    // binary search
    int low = 0;
    int high = notesLength - 1;

    if (targetNote <= notes[0])
        return notes[0];

    if (targetNote >= notes[high])
        return notes[high];

    while (low <= high)
    {
        int middle = (low + high) / 2;
        
        if (notes[middle] == targetNote)
            return notes[middle];

        if (notes[middle] < targetNote)
            low = middle + 1;
        else
            high = middle - 1;
    }
    
    // Find the closest of the two potential closest values
    int closestLow = notes[high];
    int closestHigh = notes[low];
    
    int closest = (targetNote - closestLow <= closestHigh - targetNote) ? closestLow : closestHigh;
    
    DBG ("targetNote " << juce::MidiMessage::getMidiNoteName(targetNote, true, true, 0) << " not in set: returning closest match in noteset:" << juce::MidiMessage::getMidiNoteName(closest, true, true, 0));
    
    return closest;
}

int ThreeNGenerator::findMaximumElement (juce::Array<int> arr) const
{
    jassert (!arr.isEmpty());
    int max = arr[0];
    for (int n : arr)
    {
        max = juce::jmax(max, n);
    }
    return max;
}
