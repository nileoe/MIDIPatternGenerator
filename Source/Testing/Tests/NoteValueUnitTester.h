/*
  ==============================================================================

    NoteValueUnitTester.h
    Created: 17 Apr 2025 5:20:35pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

class NoteValueUnitTester : public juce::UnitTest
{
    public:
    NoteValueUnitTester() : UnitTest ("NoteValue class unit test") {}
    
    void runTest() override
    {
        beginTest("Testing class members access");
        NoteValue noteValue1("eight note", 4, false);
        expect (noteValue1.getName() == "eight note");
        expect (4 == noteValue1.getRatioFromBeat());
        expect (!noteValue1.isTriplet());
        expect (noteValue1.getId() > 0);
        
        NoteValue noteValue2("eight note", 4, false);
        expect (noteValue1.getId() < noteValue2.getId());

        beginTest("Testing a variety of ratios for floating point imprecisions");
        NoteValue ratioTest1 { "x", 0.1, false };
        NoteValue ratioTest2 { "x", 0.01, false };
        NoteValue ratioTest3 { "x", 0.001, false };
        NoteValue ratioTest4 { "x", 0.0001, false };
        NoteValue ratioTest5 { "x", 0.00001, false };
        
        expect (0.1 == ratioTest1.getRatioFromBeat());
        expect (0.01 == ratioTest2.getRatioFromBeat());
        expect (0.001 == ratioTest3.getRatioFromBeat());
        expect (0.0001 == ratioTest4.getRatioFromBeat());
        expect (0.00001 == ratioTest5.getRatioFromBeat());
    }
};

static NoteValueUnitTester noteValueUnitTester;
