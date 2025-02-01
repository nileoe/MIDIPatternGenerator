/*
  ==============================================================================

    DebugEditor.cpp
    Created: 1 Feb 2025 4:40:13pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DebugEditor.h"

//==============================================================================
DebugEditor::DebugEditor()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DebugEditor::~DebugEditor()
{
}

void DebugEditor::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("DebugEditor", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DebugEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
