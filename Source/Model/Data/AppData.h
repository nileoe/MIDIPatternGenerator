/*
 ==============================================================================
 
 AppData.h
 Created: 22 Jan 2025 2:58:40pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "../Notes/Scale.h"
#include "../Notes/RootNote.h"
// #include "DebugWindow.h"
#include "../Generation Algorithms/RandomizerGenerator.h"
#include "../Generation Algorithms/ThreeNGenerator.h"
#include "../../Testing/Tester.h"
#include "PatternSettings.h"


class AppData
{
    public:
    static AppData& getInstance();
    
    const juce::Array<Scale>&       getScales()         const;
    const juce::Array<RootNote>&    getRootNotes()      const;
    const juce::Array<GenerationAlgorithm*>&        getGenerationAlgorithms()     const;

    const Scale*                getScaleById (int id)                 const;
    const RootNote*             getRootNoteById (int id)              const;
    const RootNote*             getRootNoteByOffsetFromC (int degree) const;
    const GenerationAlgorithm*  getSelectedGenerator()                const;
    juce::String                getSelectedGeneratorName()            const;
    int getSelectedAlgorithmId() const;

    void addScale (Scale scale);
    
    const juce::Array<int> getPattern(juce::SortedSet<int> heldNotes, int lastPressedKey) const;

    void setSelectedAlgorithmId (int id);
    
    // DELETE THIS
//    void log(juce::String dbgText, bool newLine = true)
//    {
//        jassert(dbox != nullptr);
//        dbox->log(dbgText, newLine);
//    }
//    void setDbox(AlgorithmSettingsBox& box)
//    {
//        this->dbox = box;
//    }
    //

//    AlgorithmSettingsBox* dbox;
    private:
    //
    //
    AppData() noexcept;
    ~AppData();
    
    void addRootNotesData();
    void addScaleData();
    void addGenerationAlgorithms();

//    DebugWindow debugWindow;
    juce::Array<GenerationAlgorithm*> generationAlgorithms;
    juce::Array<Scale>                scales;
    juce::Array<RootNote>             rootNotes;
    
    int selectedAlgorithmId;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppData)
};
