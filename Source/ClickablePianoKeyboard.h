/*
  ==============================================================================

    ClickablePianoKeyboard.h
    Created: 21 Jan 2025 2:03:51pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ClickablePianoKeyboard  : public juce::MidiKeyboardComponent
{
    public:
    ClickablePianoKeyboard(juce::MidiKeyboardState& state, int lowestKey, int highestKey) : juce::MidiKeyboardComponent (state,
                                                                                                                         juce::MidiKeyboardComponent::horizontalKeyboard),
    lowestKey(lowestKey),
    highestKey(highestKey)
    {
    }

    ~ClickablePianoKeyboard() override
    {
    }

    void resized() override
    {
        setAvailableRange (lowestKey, highestKey);
        int whiteKeyCount = (highestKey - lowestKey + 1) *  (7.0 / 12.0);
//        std::cout << "highest key:" << highestKey << "\n";
//        std::cout << "lowest key:" << lowestKey << "\n";
//        std::cout << "white key count: " << whiteKeyCount << "\n";   // 12
        float whiteKeyWidth = getWidth() / whiteKeyCount;
//        std::cout << "\n\n";
//        std::cout << "total key count: " << highestKey - lowestKey + 1 << "\n";   // 12
//        std::cout << "white key count: " << whiteKeyCount << "\n";   // 12
//        std::cout << "piano width: " << getWidth() << "\n";                 // 770
//        std::cout << "white key Width: " << whiteKeyWidth << "\n";                      // 64 (note: is 770 (width) divided by 12 (key count))
//        std::cout << "total keyboard width: " << getTotalKeyboardWidth() << "\n"; // 448
        setKeyWidth (whiteKeyWidth);
    }

private:
    int lowestKey; // set to 24 in my example
    int highestKey; // set to 35 in my example
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClickablePianoKeyboard)
};
