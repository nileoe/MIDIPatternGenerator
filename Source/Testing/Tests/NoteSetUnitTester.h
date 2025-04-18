/*
  ==============================================================================

    NoteSetUnitTester.h
    Created: 17 Apr 2025 5:20:21pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

class NoteSetUnitTester : public juce::UnitTest
{
    public:
    NoteSetUnitTester() : UnitTest ("NoteSet class unit test") {}
    
    void runTest() override
       {
           RootNote testRn { "E", 4 };
           Scale testSc { "Harmonic Minor", juce::Array<int>{0, 2, 3, 5, 7, 9, 11}, "7 notes Major and Minor" };
           NoteSet noteSet { testSc, testRn, 21, 108 };

           beginTest("Testing class members access");
           expect (noteSet.getRootNote().getName() == "E");
           expect (noteSet.getRootNote().getOffsetFromC() == 4);
           expect (noteSet.getScale().getName() == "Harmonic Minor");
           expect (noteSet.getLowestNote() == 21);
           expect (noteSet.getHighestNote() == 108);
           expect (noteSet.getRange().getStart() == 21);
           expect (noteSet.getRange().getEnd() == 108);

           beginTest("Testing setters and range adjustments");
           noteSet.setLowestNote(24);
           expect (noteSet.getLowestNote() == 24);
           noteSet.setHighestNote(100);
           expect (noteSet.getHighestNote() == 100);

           juce::Range<int> newRange(24, 45);
           noteSet.setRange(newRange);
           expect (noteSet.getRange().getStart() == 24);
           expect (noteSet.getRange().getEnd() == 45);

           beginTest("Testing note count and debug info");
           expect (noteSet.getNoteCount() > 0);
           const juce::String debugInfo = noteSet.getDebugInfo();
           expect (!debugInfo.isEmpty());
           
           beginTest("Testing note indices with normal range and scale");
           juce::Array<int> expectedIndices { 25, 27, 28, 30, 31, 33, 35, 37, 39, 40, 42, 43, 45 };
           juce::Array<int> actualIndices = noteSet.getNoteIndices();

           expect (actualIndices.size() == expectedIndices.size());
           arraysMatch(actualIndices, expectedIndices);
           
           noteSet.setLowestNote(5);
           noteSet.setHighestNote(5);
           expect (noteSet.getNoteIndices().size() == 0);

           resetToMaxRange(&noteSet);
           
           beginTest("Testing setting valid and invalid lowest and highest notes");
           noteSet.setLowestNote(10);
           noteSet.setHighestNote(127);
           expect (noteSet.getLowestNote() == 10);
           expect (noteSet.getHighestNote() == 127);
           expect (!noteSet.setHighestNote(5));
           noteSet.setHighestNote(80);
           expect (!noteSet.setLowestNote(100));
           
           beginTest("Testing setting invalid range");
           expect (!noteSet.setLowestNote(-1));
           expect (!noteSet.setHighestNote(128));
       }
    
    private:
    bool arraysMatch(juce::Array<int> array1, juce::Array<int> array2)
    {
        for (int i = 0; i < array1.size(); ++i)
        {
            if (array1[i] != array2[i])
                return false;
        }
        return true;
    }
    void resetToMaxRange(NoteSet* ns)
    {
        ns->setLowestNote(0);
        ns->setHighestNote(127);
    }
};

static NoteSetUnitTester noteSetUnitTester;
