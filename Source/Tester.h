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
    const static void testNoteSetAndScale()
    {
//        const auto& data = AppData::getInstance();
//        const auto scales          = data.getScales();
//        const auto algorithms      = data.getAlgorithms();
//        const auto rootNotes       = data.getRootNotes();
//        
//        const int lowestNote = 24;
//        const int highestNote = 45;
//        
//        std::cout << "lowest note\t(" << lowestNote << "):\t" << juce::MidiMessage::getMidiNoteName(lowestNote, true, true, true) << "\n";
//        std::cout << "highest note\t(" << highestNote << "):\t" << juce::MidiMessage::getMidiNoteName(highestNote, true, true, true) << "\n";
//
////        const Scale* majorScale = data.getScaleById(1);
//        const Scale* pentaMajorScale = data.getScaleById(5);
////        const Scale* chroScale  = data.getScaleById(6);
//        
////        const RootNote* c_rn = data.getRootNoteByOffsetFromC(0);
////        const RootNote* d_rn = data.getRootNoteByOffsetFromC(2);
//        const RootNote* b_rn = data.getRootNoteByOffsetFromC(11);
//
//        const NoteSet ns {*pentaMajorScale, *b_rn, lowestNote, highestNote};
//        ns.printInfo();
    }
    const static void testKeyboard()
    {
//        void ClickableMidiKeyboard::resized()
//        {
//            setAvailableRange (lowestKey, highestKey);
//            int whiteKeyCount = (highestKey - lowestKey + 1) *  (7.0 / 12.0);
//            //        std::cout << "highest key:" << highestKey << "\n";
//            //        std::cout << "lowest key:" << lowestKey << "\n";
//            //        std::cout << "white key count: " << whiteKeyCount << "\n";   // 12
//            float whiteKeyWidth = getWidth() / whiteKeyCount;
//            //        std::cout << "\n\n";
//            //        std::cout << "total key count: " << highestKey - lowestKey + 1 << "\n";   // 12
//            //        std::cout << "white key count: " << whiteKeyCount << "\n";   // 12
//            //        std::cout << "piano width: " << getWidth() << "\n";                 // 770
//            //        std::cout << "white key Width: " << whiteKeyWidth << "\n";                      // 64 (note: is 770 (width) divided by 12 (key count))
//            //        std::cout << "total keyboard width: " << getTotalKeyboardWidth() << "\n"; // 448
//            setKeyWidth (whiteKeyWidth);
//        }
    }
};
