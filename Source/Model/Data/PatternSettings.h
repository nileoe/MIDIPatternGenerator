/*
  ==============================================================================

    PatternSettings.h
    Created: 8 Feb 2025 11:15:00am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "../Notes/NoteSet.h"
#include "../Notes/NoteValue.h"
#include "../GenerationAlgorithm.h"
#include <JuceHeader.h>


class PatternSettings
{
    public:
    enum LengthUnit
    {
        Note,
        Bar,
        Second
    };
    
    static PatternSettings& getInstance();
    
    NoteSet&     getNoteSet()                   ; // todo put const
    int          getLengthInUnits()  const;
    int          getLengthInNotes()  const;
    juce::String getLengthUnitName() const; // mention: no get length int, only name (string)
    NoteValue    getNoteValue()      const;
    
    void setGenerationAlgorithm (GenerationAlgorithm* algo);
    void setNoteValue           (NoteValue noteValue);
    void setLength              (int length);
    void setLengthUnit          (LengthUnit unit);
    void setLengthUnit          (juce::String unitName);
    
    private:
    PatternSettings() noexcept;
    
    NoteSet noteSet;
    int length;
    LengthUnit lengthUnit;
    NoteValue noteValue;
    GenerationAlgorithm* generationAlgorithm;
};

