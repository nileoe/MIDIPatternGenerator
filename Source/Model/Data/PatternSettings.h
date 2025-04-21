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
    
    NoteSet&     getNoteSet();
    NoteValue    getNoteValue()           const;
    double       getNoteSpeedRatio()      const;
    bool         doesAllowOffKeyInput()   const;
    bool         isPatternInfinite()      const;
    bool         doesMergeRepeatedNotes() const;
    int          getLengthInUnits()       const;
    int          getLengthInNotes()       const;
    juce::String getLengthUnitName()      const;


    void setGenerationAlgorithm (GenerationAlgorithm* algo);
    void setNoteValue           (NoteValue noteValue);
    void setNoteSpeedRatio      (double ratio);
    void setAllowOffKeyInput    (bool allowOffKeyInput);
    void setInfinitePattern     (bool infinitePattern);
    void setMergeRepeatedNotes  (bool mergeRepeatedNotes);
    void setLength              (int length);
    void setLengthUnit          (LengthUnit unit);
    void setLengthUnit          (juce::String unitName);
    
    private:
    PatternSettings() noexcept;
    
    NoteSet noteSet;
    int length = 10;
    NoteValue noteValue;
    double noteSpeedRatio = 2; // defaulting to eight notes
    bool allowOffKeyInput = false;
    bool patternIsInfinite = false;
    bool mergeRepeatedNotes = true;
    LengthUnit lengthUnit;
    GenerationAlgorithm* generationAlgorithm;
};

