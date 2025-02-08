/*
  ==============================================================================

    RootNote.cpp
    Created: 2 Feb 2025 8:46:20pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "RootNote.h"

int RootNote::nextId = 1;
RootNote::RootNote() = default;
RootNote::RootNote (juce::String name, int offsetFromC) : id(nextId ++), name(name), offsetFromC(offsetFromC)
{
    jassert(name.length() <= 5);
    jassert(offsetFromC >= 0 && offsetFromC <= 11);
}

const   juce::String&   RootNote::getName()     const { return name; }
int                     RootNote::getOffsetFromC()   const { return offsetFromC; }
int                     RootNote::getId()       const { return id; }

void RootNote::printInfo() const
{
    std::cout << "############ PRINTING ROOTNOTE INFO ############" << "\n";
    std::cout << "note name: " << name << "\n";
    std::cout << "note offset from c: " << offsetFromC << "\n";
}
