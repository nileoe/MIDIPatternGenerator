

/*
  ==============================================================================

    Generators.cpp
    Created: 5 Feb 2025 12:08:59pm
    Author:  Lino Perdrix

  ==============================================================================
*/

//#include "ThreeNGenerator.h"
//
//ThreeNGenerator::ThreeNGenerator(juce::SortedSet<int>& heldNotes, juce::Array<int>& availableNotes)
//    : GenerationAlgorithm(heldNotes, availableNotes)
//{}
//
//const juce::Array<int> ThreeNGenerator::getPattern()
//{
//    juce::Array<int> pattern = {30, 42, 54, 66};
//    return pattern;
//}
//
//int ThreeNGenerator::getAlgorithmId() const
//{
//    return 1;
//}


//
//juce::Array<int> Generators::getNotesHigherThan(juce::SortedSet<int>& heldNotes, const juce::Array<int>& availableNotes)
//{
//    jassert(!heldNotes.isEmpty());
//    const int lowestHeldNote = heldNotes.getFirst();
//    juce::Array<int> pattern;
//    
//    for (const int note : availableNotes)
//    {
//        if (note >= lowestHeldNote)
//        {
//            pattern.add(note);
//        }
//    }
//    return pattern;
//}
//
//juce::Array<int> Generators::threeNPlusOneAlgo(juce::SortedSet<int>& heldNotes, const juce::Array<int>& availableNotes)
//{
//    jassert(!heldNotes.isEmpty());
//    const int lowestHeldNote = heldNotes.getFirst();
//    juce::Array<int> pattern;
//    return pattern;
//}
