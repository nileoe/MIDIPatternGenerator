/*
 ==============================================================================
 
 ScaleAndHarmonyBox.cpp
 Created: 22 Jan 2025 10:40:42am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "ScaleAndHarmonyBox.h"

ScaleAndHarmonyBox::ScaleAndHarmonyBox(int scaleHarmonyRadioId, NoteSet& patternNoteSet) : patternNoteSet(patternNoteSet)
{
    setText ("Scale and Harmony");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    
    addAndMakeVisible(useHarmonyRadioButton);
    addAndMakeVisible(useScaleRadioButton);
    
    addAndMakeVisible(strictModeTickbox);
    
    addAndMakeVisible(useCustomScaleTickbox);
    addAndMakeVisible(rootNoteMenu);
    addAndMakeVisible(scaleMenu);
    addAndMakeVisible(customScaleButton);
    
    useHarmonyRadioButton   .onClick = [this] { updateToggleState(); };
    useScaleRadioButton     .onClick = [this] { updateToggleState(); };
    
    useHarmonyRadioButton   .setRadioGroupId(scaleHarmonyRadioId);
    useScaleRadioButton     .setRadioGroupId(scaleHarmonyRadioId);
    
    useHarmonyRadioButton   .setToggleState (true, juce::NotificationType::sendNotification);
    updateToggleState();
    
    AppData& data = AppData::getInstance();
    const juce::Array<Scale> scales = data.getScales();
    for (Scale s : scales)
    {
        scaleMenu.addItem (s.getName(), s.getId());
        data.log("scale menu: adding scale ", false);
        data.log(s.getName());
        data.log(juce::String(s.getId()));
        data.log();
    }
    
    const juce::Array<RootNote> rootNotes = data.getRootNotes();
    for (RootNote rn : rootNotes)
    {
        rootNoteMenu.addItem (rn.getName(), rn.getId());
        data.log("rootNote menu: adding rootnote ", false);
        data.log(rn.getName());
        data.log(juce::String(rn.getId()));
        data.log();
    }
    
    scaleMenu.onChange    = [this] { updatePatternScale(); };
    rootNoteMenu.onChange = [this] { updatePatternRootNote(); };
    
    scaleMenu       .setSelectedId(scales   .getFirst().getId());
    rootNoteMenu    .setSelectedId(rootNotes.getFirst().getId());
}

void ScaleAndHarmonyBox::updateToggleState()
{
    bool harmonyIsSelected = useHarmonyRadioButton.getToggleState();
    bool scaleIsSelected = !harmonyIsSelected;
    
    strictModeTickbox.setEnabled(harmonyIsSelected);
    
    scaleMenu.setEnabled(scaleIsSelected);
    rootNoteMenu.setEnabled(scaleIsSelected);
    useCustomScaleTickbox.setEnabled(scaleIsSelected);
    customScaleButton.setEnabled(scaleIsSelected);
}

void ScaleAndHarmonyBox::updatePatternRootNote()
{
//    auto& newRootNote = AppData::getInstance().getRootNoteById(rootNoteMenu.getSelectedId());
//    patternNoteSet.setRootNote(newRootNote);
}
void ScaleAndHarmonyBox::updatePatternScale()
{
//    auto* newScale = AppData::getInstance().getScaleById(scaleMenu.getSelectedId());
//    if (newScale == nullptr)
//    {
//        AppData:getInstance().log("nullptr returned from getScaleById with id ", false);
//        AppData:getInstance().log(juce::String(scaleMenu.getSelectedId()));
//    }
//    patternNoteSet.setScale(*newScale);
}

void ScaleAndHarmonyBox::resized()
{
    using FI = juce::FlexItem;
    juce::Rectangle<int> scaleArea = getLocalBounds().reduced (20);
    juce::Rectangle<int> harmonyArea = scaleArea.removeFromTop (scaleArea.getHeight() / 2);
    
    juce::FlexBox harmonyFb;
    harmonyFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    harmonyFb.items.add (FI(useHarmonyRadioButton)  .withMinWidth (500.0f).withMinHeight (20.0f));
    harmonyFb.items .add (FI(strictModeTickbox)     .withMinWidth (200.0f).withMinHeight (20.0f));
    harmonyFb.performLayout(harmonyArea);
    
    juce::FlexBox scaleFb;
    scaleFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    scaleFb.alignItems = juce::FlexBox::AlignItems::center;
    scaleFb.items.add (FI(useScaleRadioButton)      .withMinWidth (130.0f).withMinHeight (30.0f));
    scaleFb.items.add (FI(rootNoteMenu)             .withMinWidth (95.0f) .withMinHeight (30.0f).withMargin (FI::Margin(0, 10, 0, 0)));
    scaleFb.items.add (FI(scaleMenu)                .withMinWidth (250.0f).withMinHeight (30.0f));
    
    juce:: FlexBox customScaleFb;
    customScaleFb.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
    customScaleFb.alignItems = juce::FlexBox::AlignItems::center;
    customScaleFb.items.add (FI(useCustomScaleTickbox)    .withMinWidth (30.0f) .withMinHeight (30.0f));
    customScaleFb.items.add (FI(customScaleButton)        .withMinWidth (150.0f).withMinHeight (30.0f));
    
    scaleFb.items.add (FI(customScaleFb).withFlex(1.0f)   .withMinWidth (200.0f));
    scaleFb.performLayout (scaleArea);
}
