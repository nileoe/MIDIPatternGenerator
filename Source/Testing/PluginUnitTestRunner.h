/*
  ==============================================================================

    TestRunner.h
    Created: 17 Apr 2025 4:18:43pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once
#include "./Tests/RootNoteUnitTester.h"
#include "./Tests/NoteValueUnitTester.h"
#include "./Tests/ScaleUnitTester.h"
#include "./Tests/NoteSetUnitTester.h"
#include "./Tests/PatternGenerationUnitTester.h"

class PluginUnitTestRunner: public juce::UnitTestRunner
{
    public:
    PluginUnitTestRunner()
    {
        setPassesAreLogged(true);
        setAssertOnFailure(false);
        runAllTests();
    }
};
