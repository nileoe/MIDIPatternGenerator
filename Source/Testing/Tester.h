/*
  ==============================================================================

    Tester.h
    Created: 6 Feb 2025 12:05:14pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "../Model/GenerationAlgorithm.h"
#include "../Model/Generation Algorithms/ThreeNGenerator.h"
#include "../Model/Generation Algorithms/RandomizerGenerator.h"

class Tester
{
    public:
    Tester()
    {
        DBG ("TEST");
        
        juce::Array<GenerationAlgorithm*> arr;
        
        int id = 1;
        
        arr.add(new RandomizerGenerator{id++});
        arr.add(new ThreeNGenerator{id++});
        
        for (GenerationAlgorithm* algo : arr)
        {
            DBG (algo->getId());
            DBG (algo->getName());
            DBG ("");
        }
    }
};
