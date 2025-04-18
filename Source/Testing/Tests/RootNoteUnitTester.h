/*
  ==============================================================================

    RootNoteUnitTester.h
    Created: 17 Apr 2025 5:19:49pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

class RootNoteUnitTester : public juce::UnitTest
{
    public:
    RootNoteUnitTester() : UnitTest ("RootNote class unit test") {}
    
    void runTest() override
    {
        beginTest("Testing class members access");
        RootNote rootNote1("C", 0);
        expect (rootNote1.getName() == "C");
        expect (rootNote1.getOffsetFromC() == 0);
        expect (rootNote1.getId() > 0);
        
        RootNote rootNote2("D", 2);
        expect (rootNote2.getName() == "D");
        expect (rootNote2.getOffsetFromC() == 2);
        expect (rootNote2.getId() > rootNote1.getId());
    }
};

static RootNoteUnitTester rootNoteUnitTester;

