/*
 ==============================================================================
 
 PatternSettings.cpp
 Created: 8 Feb 2025 11:15:00am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "PatternSettings.h"

PatternSettings::PatternSettings() noexcept {}

PatternSettings& PatternSettings::getInstance()
{
    static PatternSettings instance;
    return instance;
}

NoteSet&     PatternSettings::getNoteSet()       { return noteSet; }
int          PatternSettings::getLength()         const { return length; }
juce::String PatternSettings::getLengthUnitName() const
{
    switch (lengthUnit) {
        case PatternSettings::Note:
            return "Note";
        case PatternSettings::Bar:
            return "Bar";
        case PatternSettings::Second:
            return "Second";
        default:
            DBG ("Invalid length unit enum in PatternSettings");
            jassertfalse;
            return "";
    }

}

//void PatternSettings::setNoteSet             (NoteSet& noteSet)          { this->noteSet = noteSet; }
void PatternSettings::setLength              (int length)                { this->length = length; }
void PatternSettings::setLengthUnit          (LengthUnit unit)           { this->lengthUnit = unit; }
void PatternSettings::setGenerationAlgorithm (GenerationAlgorithm* algo) { this->generationAlgorithm = algo; }
