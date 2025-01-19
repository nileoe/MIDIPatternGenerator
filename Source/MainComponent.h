#pragma once

#include <JuceHeader.h>

class MainComponent  : public juce::Component
{
    public:
    //==============================================================================
    MainComponent()
    {
        setSize (1200, 600);
        
        // ---------------- GENERATION METHOD BOX ----------------
//        addAndMakeVisible(generationMethodsBox);
//        generationMethodsBox.setText("Generation Method");
//        generationMethodsBox
//            .setColour(juce::GroupComponent::ColourIds::outlineColourId,
//                       juce::Colours::white);
        // melody button
//        addAndMakeVisible(melodyGenerationButton);
//        melodyGenerationButton.setRadioGroupId(GenerationMethods);
//        
//        // algorithm button
//        addAndMakeVisible(algorithmGenerationButton);
//        algorithmGenerationButton.setRadioGroupId(GenerationMethods);

//        addAndMakeVisible(algorithmMenu);

    }
    
    ~MainComponent() override
    {
    }
    
    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        //        g.setFont (juce::FontOptions (16.0f));
        //        g.setColour (juce::Colours::white);
        //        g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
    }
    
    void resized() override
    {
        addAndMakeVisible(generationMethodsBox);
        generationMethodsBox.setBounds (20, 20, 350, 150);
//        generationMethodsBox        .setBounds (20, 20, 350, 150);
//        algorithmGenerationButton   .setBounds (generationMethodsBox.getX() + 10, generationMethodsBox.getY() + 20, generationMethodsBox.getWidth() - 100, 70);
//        melodyGenerationButton      .setBounds (generationMethodsBox.getX() + 10, generationMethodsBox.getY() + 80, generationMethodsBox.getWidth() - 100, 70);
//        algorithmMenu
//            .setBounds (algorithmGenerationButton.getX() + algorithmGenerationButton.getWidth() + 10,
//                        algorithmGenerationButton.getY() + 20,
//                        80,
//                        algorithmGenerationButton.getHeight() - 20);
    }
    
    enum RadioButtonIds
    {
        GenerationMethods = 101
    };

    
    private:
    struct GenerationMethodsBox : public juce::GroupComponent
    {
//        GenerationMethodsBox (int width, int height)
        GenerationMethodsBox ()
        {
//            setSize(width, height);
            addAndMakeVisible(box);
            box.setText("Generation Method");
            box.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
        }
        
        juce::GroupComponent box;
        juce::ToggleButton algorithmButton    {"Generate from Algorithm"};
        juce::ToggleButton melodyButton       {"Generate from Input Melody"};
        juce::ComboBox algorithmMenu;
    };
    
//    GenerationMethodsBox generationMethodsBox {350, 150};
    GenerationMethodsBox generationMethodsBox;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//class MainComponent : public juce::Component
//{
//public:
//    MainComponent()
//    {
//        addAndMakeVisible(comboBox);
//        comboBox.addItem("Option 1", 1);
//        comboBox.addItem("Option 2", 2);
//        comboBox.addItem("Option 3", 3);
//
//        addAndMakeVisible(toggleButton);
//        toggleButton.setButtonText("Enable");
//
//        setSize(400, 200);
//    }
//
//    void resized() override
//    {
//        juce::FlexBox flexBox;
//        flexBox.flexDirection = juce::FlexBox::Direction::row;
//        flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
//        flexBox.alignItems = juce::FlexBox::AlignItems::center;
//
//        flexBox.items.add(juce::FlexItem(comboBox).withFlex(1.0));
//        flexBox.items.add(juce::FlexItem(toggleButton).withMargin(juce::FlexItem::Margin(0, 0, 0, 20)));
//
//        flexBox.performLayout(getLocalBounds().reduced(20));
//    }
//
//private:
//    juce::ComboBox comboBox;
//    juce::ToggleButton toggleButton;
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
//};
