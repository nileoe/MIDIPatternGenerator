/*
  ==============================================================================

    PatternSettings.h
    Created: 8 Feb 2025 11:15:00am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include "../Notes/NoteSet.h"
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
    
    NoteSet&     getNoteSet()        ;
    int          getLength()         const;
    juce::String getLengthUnitName() const; // mention: no get length int, only name (string)
    
//    void setNoteSet             (NoteSet& noteSet); // no noteset setter as
    void setLength              (int length);
    void setLengthUnit          (LengthUnit unit);
    void setGenerationAlgorithm (GenerationAlgorithm* algo);
    
    private:
    PatternSettings() noexcept;
    
    NoteSet noteSet;
    int length;
    LengthUnit lengthUnit;
    GenerationAlgorithm* generationAlgorithm;
};

