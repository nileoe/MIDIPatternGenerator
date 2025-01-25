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
        const auto& data = AppData::getInstance();
        const auto scales          = data.getScales();
        const auto algorithms      = data.getAlgorithms();
        const auto rootNotes       = data.getRootNotes();
        
        const int lowestNote = 16;
        const int highestNote = 39;
        
        std::cout << "lowest note\t(" << lowestNote << "):\t" << juce::MidiMessage::getMidiNoteName(lowestNote, true, true, true) << "\n";
        std::cout << "highest note\t(" << highestNote << "):\t" << juce::MidiMessage::getMidiNoteName(highestNote, true, true, true) << "\n";

        const Scale* majorScale = data.getScaleById(1);
        const Scale* chroScale  = data.getScaleById(5);
        
        const RootNote* c_rn = data.getRootNoteByDegree(0);
        const RootNote* d_rn = data.getRootNoteByDegree(2);
        
        const NoteSet ns {*majorScale, *d_rn, lowestNote, highestNote};
        ns.printInfo();
    }
};
