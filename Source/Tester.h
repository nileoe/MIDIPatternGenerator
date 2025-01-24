/*
  ==============================================================================

    Tester.h
    Created: 24 Jan 2025 9:52:22am
    Author:  Lino Perdrix

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>
#include "AppData.h"
#include "NoteSet.h"

class Tester
{
    public:
    const static void test()
    {
        auto& data = AppData::getInstance();
        auto scales          = data.getScales();
        auto algorithms      = data.getAlgorithms();
        auto rootNotes       = data.getRootNotes();
        
        int lowestNote = 7;
        int highestNote = 39;
        
        int scaleId = 5;

        const Scale* chroScale = data.getScaleById(scaleId);
        if (chroScale != nullptr)
        {
            NoteSet ns {*chroScale, lowestNote, highestNote};
            ns.printInfo();
        }
        else
        {
            std::cout << "scale with id " << scaleId << " not found" << "\n";
        }
        
    }
};
