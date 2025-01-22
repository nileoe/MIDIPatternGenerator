/*
  ==============================================================================

    Scale.cpp
    Created: 22 Jan 2025 4:24:51pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include "Scale.h"

int Scale::nextId = 1;
Scale::Scale() : id(nextId++), name("Unnamed"), categoryName("None")
{
}

Scale::Scale(const Scale& other) : id(other.id), name(other.name), noteIndices(other.noteIndices), notePattern(other.notePattern), categoryName(other.categoryName)
{
}

Scale::Scale(juce::String name, juce::Array<bool> notePattern, juce::String categoryName) : id(nextId ++), name(name), notePattern(notePattern), categoryName(categoryName)
{
    // scales must follow the 12-note western system.
    jassert (notePattern.size() == 12);
    // set the note indices
    juce::Array<int> noteIndices;
    for (auto i = 0; i < 12; ++i)
    {
        if (notePattern[i])
        {
            noteIndices.add(i);
        }
    }
}

Scale::Scale(juce::String name, juce::Array<int> noteIndices, juce::String categoryName) : id(nextId ++), name(name), noteIndices(noteIndices), categoryName(categoryName)
{
    // notes indices must be sorted in (strictly) ascending order and range from 0 to 11 inclusive
    for (int i = 0; i < noteIndices.size() - 1; ++i)
    {
        jassert(noteIndices[i] < noteIndices[i + 1]);
    }
    jassert (noteIndices.getFirst() >= 0);
    jassert (noteIndices.getLast() <= 11);
  
    juce::Array<bool> notePattern(false, 12);
    for (auto noteIndex : noteIndices)
    {
        notePattern.set(noteIndex, true);
    }
}

int Scale::getId() const
{
    return id;
}

const juce::String& Scale::getName() const
{
    return name;
}

const juce::String& Scale::getCategoryName() const
{
    return categoryName;
}

const juce::Array<int>&  Scale::getNoteIndices() const
{
    return noteIndices;
}

const juce::Array<bool>& Scale::getNotePattern() const
{
    return notePattern;
}

int Scale::getNoteCount() const
{
    return noteIndices.size();
}

bool Scale::isNoteInScale(int noteIndex) const
{
    jassert (noteIndex >= 0 && noteIndex <= 11);
    for (int scaleNote : noteIndices)
    {
        if (scaleNote == noteIndex)
        {
            return true;
        }
    }
    return false;
}

void Scale::printInfo() const
{
    std::cout << "############ PRINTING SCALE INFO ############" << "\n";
    std::cout << "id: " << id << "\n";
    std::cout << "name: " << name << "\n";
    std::cout << "category: " << categoryName << "\n";
    std::cout << "notes: ";
    for (auto n : noteIndices)
    {
        std::cout << n << ", ";
    }
    std::cout << "\nnext (static) scale class id: " << nextId << "\n";
}

RootNote::RootNote() = default;
RootNote::RootNote (juce::String name, int degree) : name(name), degree(degree)
{
    jassert(name.length() <= 5);
    jassert(degree >= 0 && degree <= 11);
}

const juce::String& RootNote::getName() const
{
    return name;
}

int RootNote::getDegree() const
{
    return degree;
}

void RootNote::printInfo() const
{
    std::cout << "############ PRINTING ROOTNOTE INFO ############" << "\n";
    std::cout << "note name: " << name << "\n";
    std::cout << "note degree: " << degree << "\n";
}

