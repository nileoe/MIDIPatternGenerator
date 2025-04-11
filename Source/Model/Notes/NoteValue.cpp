/*
  ==============================================================================

    NoteValue.cpp
    Created: 11 Apr 2025 1:14:37pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "NoteValue.h"

int NoteValue::nextId = 1;
NoteValue::NoteValue() = default;
NoteValue::NoteValue (juce::String name, double ratioFromBeat) : id(nextId ++), name(name), ratioFromBeat(ratioFromBeat)
{
    jassert(name.length() > 0);
    jassert(ratioFromBeat > 0);
}

const juce::String& NoteValue::getName() const { return name; }
double NoteValue::getRatioFromBeat()     const { return ratioFromBeat; }
int NoteValue::getId()                   const { return id; }
