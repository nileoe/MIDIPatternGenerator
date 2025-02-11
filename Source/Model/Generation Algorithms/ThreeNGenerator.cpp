
#include "ThreeNGenerator.h"

ThreeNGenerator::ThreeNGenerator(int id) : GenerationAlgorithm(id) {}

const juce::Array<int> ThreeNGenerator::getPattern(juce::SortedSet<int> heldNotes, juce::Array<int> targetNotes, int lastPressedKey) const
{
    DBG ("Getting pattern for ThreeN");
    juce::Array<int> pattern = {30, 42, 54, 66};
    return pattern;
}

juce::String ThreeNGenerator::getName() const
{
    return "Three N Plus One";
}
