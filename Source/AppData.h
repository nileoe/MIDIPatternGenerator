/*
 ==============================================================================
 
 AppData.h
 Created: 22 Jan 2025 2:58:40pm
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include "Scale.h"
#include "DebugWindow.h"


class AppData
{
    public:
    static AppData& getInstance();
    
    const juce::StringArray&        getAlgorithms()     const;
    const juce::Array<Scale>&       getScales()         const;
    const juce::Array<RootNote>&    getRootNotes()      const;
    
    const Scale* getScaleById           (int id)        const;
    const RootNote* getRootNoteByOffsetFromC (int degree)    const;
    
    void addScale (Scale scale);
    //
    void dbg(juce::String);
    
//    const DebugWindow& getDebugWindow() const
//    {
//        return debugWindow;
//    }
    DebugWindow& getDebugWindow()
    {
        return debugWindow;
    }


    private:
    
    DebugWindow debugWindow;
    juce::StringArray           algorithms;
    juce::Array<Scale>          scales;
    juce::Array<RootNote>       rootNotes;
    
    AppData() noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppData)
};
