/*
  ==============================================================================

    PatternGeneratingUnitTester.h
    Created: 17 Apr 2025 5:22:42pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

class PatternGeneratingUnitTester : public juce::UnitTest
{
    public:
    PatternGeneratingUnitTester() : UnitTest ("Generation Algorithm Tests") {}
    
    void runTest() override
    {
        juce::SortedSet<int> heldNotesSample;
        heldNotesSample.add(36);
        heldNotesSample.add(40);
        heldNotesSample.add(43);
        juce::Array<int> targetNoteSample { 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92 };
        juce::Array<int> testTargetNotes = targetNoteSample;
        auto& patternSettings = PatternSettings::getInstance();

        const int lastPressedKey = 55;
        const RandomizerGenerator randomizer {1};
        const ThreeNGenerator threeN {2};

        beginTest("Testing the Randomizer algorithm successful pattern generation and respect of maximum length constraints");
        juce::Array<int> randoPattern  = randomizer.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (randoPattern.size() != 0);
        expect (randoPattern.size() <= patternSettings.getLengthInNotes());
        
        patternSettings.setLength(5);
        randoPattern  = randomizer.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (randoPattern.size() != 0);
        expect (randoPattern.size() <= patternSettings.getLengthInNotes());
        
        patternSettings.setLength(1);
        randoPattern  = randomizer.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (randoPattern.size() != 0);
        expect (randoPattern.size() <= patternSettings.getLengthInNotes());

        beginTest("Testing the ThreeN algorithm successful pattern generation and respect of maximum length constraints");
        juce::Array<int> threeNPattern  = threeN.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (threeNPattern.size() != 0);
        expect (threeNPattern.size() <= patternSettings.getLengthInNotes());
        
        patternSettings.setLength(5);
        threeNPattern  = threeN.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (threeNPattern.size() != 0);
        expect (threeNPattern.size() <= patternSettings.getLengthInNotes());
        
        patternSettings.setLength(1);
        threeNPattern  = threeN.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (threeNPattern.size() != 0);
        expect (threeNPattern.size() <= patternSettings.getLengthInNotes());

        beginTest("Testing Randomizer pattern target notes range tolerance");
        testTargetNotes = targetNoteSample;
        expect (patternFitsInTargetRange(randoPattern, testTargetNotes));
        testTargetNotes = { 1 };
        randoPattern  = randomizer.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (patternFitsInTargetRange(randoPattern, testTargetNotes));
        
        testTargetNotes = { 1, 127 };
        randoPattern  = randomizer.getPattern (heldNotesSample, testTargetNotes, lastPressedKey);
        expect (patternFitsInTargetRange(randoPattern, testTargetNotes));
        
        beginTest("Testing ThreeN pattern target notes range tolerance");
        testTargetNotes = targetNoteSample;
        expect (patternFitsInTargetRange(threeNPattern, testTargetNotes));
        testTargetNotes = { 1 };
        threeNPattern = threeN.getPattern (heldNotesSample, targetNoteSample, lastPressedKey);
        expect (patternFitsInTargetRange(threeNPattern, targetNoteSample));
        
        testTargetNotes = { 1, 127 };
        threeNPattern = threeN.getPattern (heldNotesSample, targetNoteSample, lastPressedKey);
        expect (patternFitsInTargetRange(threeNPattern, targetNoteSample));
    }
    
    private:
    bool patternFitsInTargetRange(juce::Array<int> pattern, juce::Array<int> targetRange)
    {
        for (auto note : pattern)
        {
            if (!targetRange.contains(note))
                return false;
        }
        return true;
    }
};

static PatternGeneratingUnitTester patternGeneratingUnitTester;
