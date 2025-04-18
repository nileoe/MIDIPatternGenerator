/*
  ==============================================================================

    ScaleUnitTester.h
    Created: 17 Apr 2025 4:00:21pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

class ScaleUnitTester : public juce::UnitTest
{
    public:
    ScaleUnitTester() : UnitTest ("Scale class unit test") {}
    
    void runTest() override
    {
        beginTest("Testing integer array constructor and members access");
        Scale major1 { "Major Scale 1", juce::Array<int>{0, 2, 4, 5, 7, 9, 11}, "7 notes Major and Minor" };
        expect (major1.getName() == "Major Scale 1");
        expect (major1.getCategory() == "7 notes Major and Minor");
        expect (major1.doesNoteDegreeBelongToScale(0));
        expect (major1.doesNoteDegreeBelongToScale(5));
        expect (!major1.doesNoteDegreeBelongToScale(1));
        expect (!major1.doesNoteDegreeBelongToScale(10));

        beginTest("Testing boolean array constructor and members access");
        Scale major2{ "Major Scale 2", juce::Array<bool>{true, false, true, false, true, true, false, true, false, true, false, true}, "7 notes Major and Minor" };
        expect (major2.doesNoteDegreeBelongToScale(0));
        expect (major2.doesNoteDegreeBelongToScale(5));
        expect (!major2.doesNoteDegreeBelongToScale(1));
        expect (!major2.doesNoteDegreeBelongToScale(10));
        
        beginTest("Testing 2 constructors equivalence");
        expect (major1.getName() == major2.getName());
        expect (major1.getCategory() == major2.getCategory());
        expect (major1.getNoteIndices() == major2.getNoteIndices());
        expect (major1.getNotePattern() == major2.getNotePattern());
        expect (major1.getNoteCount() == major2.getNoteCount());
    }
};

static ScaleUnitTester scaleTest;
