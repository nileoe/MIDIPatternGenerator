/*
  ==============================================================================

    Randomizer.h
    Created: 5 Feb 2025 1:45:33pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "GenerationAlgorithm.h"
#include <JuceHeader.h>

class RandomizerGenerator // : public GenerationAlgorithm
{
    public:
    juce::Array<int> getPattern();// override;
    int getAlgorithmId() const;// override;
    
    private:
    static int id;
//    juce::SortedSet<int>& heldNotes;
//    juce::Array<int>& targetNotes;
};
