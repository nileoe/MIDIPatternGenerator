#include "PluginProcessor.h"
#include "./Components/Editors/PluginEditor.h"

//==============================================================================
ArpAlgoAudioProcessor::ArpAlgoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
}

ArpAlgoAudioProcessor::~ArpAlgoAudioProcessor()
{
}

void ArpAlgoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
//    Tester t;
    pressedKeys.clear();
    currentNote = -1;
    patternNoteIndex = 0;
    lastNoteValue = -1;
    lastPressedKey = -1;
    time = 0;
    rate = static_cast<float> (sampleRate);
    debugText = "";
}


// ################################################################################################
void ArpAlgoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    jassert (buffer.getNumChannels() == 0);
    const int numSamples = buffer.getNumSamples();
    
    const auto& dataInstance = AppData::getInstance();
    const double bpm = getHostBpmOrDefault();
    const double speedRatio = dataInstance.getNoteSpeedRatio();
    const auto noteDuration = static_cast<int> (std::ceil ((rate * 60.0 / bpm) * speedRatio));

    recordPressedKeys(midiMessages);
    //
    if (!pressedKeys.isEmpty())
    {
//        DBG (pressedKeys.size() << "currently keys pressed");
//        DBG ("buffer last pressed key: " << bufferLastPressedKey);
//        DBG ("Last pressed key recorded: " << lastPressedKey << "\n"); // WORKS FINE
    }
     //
    midiMessages.clear();
//    if (pressedKeys.isEmpty() || patternIsExhausted())
    if (pressedKeys.isEmpty())
    {
        // allow for new pattern to be created even if pressed key is the same as before (forget about last pressed key)
//        lastPressedKey = -1; // doesnt work
        patternBaseNote = -1; // doesnt work
    }
    if (pressedKeys.isEmpty() || patternIsExhausted())
    {
        // No keys are currently pressed, or the pattern has finished playing: will reset pattern, set current note to -1 and return early.
        // May send a noteOff message to clean up last note before.
        if (shouldSendCleanupNoteOffMessage())
        {
            DBG ("Sending clean-up note off message to " << juce::MidiMessage::getMidiNoteName(currentNote, true, true, 0) << " (offset: (manual=0)");
            midiMessages.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue), 0);
            lastNoteValue = -1;
        }
        currentNote = -1;
        pattern = juce::Array<int>();
        return;
    }
    
    
    if (patternBaseNote == lastPressedKey && currentNote == -1)
    {
        return;
    }
    jassert (!pressedKeys.isEmpty());
    
    // CREATE NEW PATTERN if empty or a new key was pressed.
    if (pattern.isEmpty() || differentNewKeyIsPressed(midiMessages.getNumEvents()))
    {
        if (pressedKeys.isEmpty())
            DBG ("no notes held");
        if (differentNewKeyIsPressed(midiMessages.getNumEvents()))
            DBG ("different key was pressed: lastPressedKey = " << lastPressedKey << ", pattern base = " << lastPressedKey);
//        lastPressedKey = bufferLastPressedKey;
        currentNote = 0;
//        jassert (patternBaseKey != -1);
        patternBaseNote = lastPressedKey;
        pattern = dataInstance.getPattern(pressedKeys, patternBaseNote);
        DBG ("CREATING NEW PATTERN: base note = " << patternBaseNote << ", lastPressedKey = " << lastPressedKey);
    }

    if ((time + numSamples) >= noteDuration)
    {
        auto offset = juce::jmax (0, juce::jmin ((int) (noteDuration - time), numSamples - 1));
        if (lastNoteValue > 0)
        {
            midiMessages.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue), offset);
            lastNoteValue = -1;
        }
        jassert (!pattern.isEmpty());
        
        lastNoteValue = pattern[currentNote];
        if (lastNoteValue == -1)
        {
            DBG ("lastNoteValue == -1 nooo");
            jassertfalse;
        }
        midiMessages.addEvent (juce::MidiMessage::noteOn (1, lastNoteValue, (juce::uint8) 127), offset);
        currentNote ++;
    }
    time = (time + numSamples) % noteDuration;
}
// ################################################################################################

//void ArpAlgoAudioProcessor::recordPressedKeys(juce::MidiBuffer& midiMessages, int& bufferLastPressedKey)
void ArpAlgoAudioProcessor::recordPressedKeys(juce::MidiBuffer& midiMessages)
{
    for (const juce::MidiMessageMetadata metadata : midiMessages)
    {
        const juce::MidiMessage message = metadata.getMessage();
        if (message.isNoteOnOrOff()) // TODO could do a "continue" to return early
        {
            int noteNumber = message.getNoteNumber();
            if (message.isNoteOn())
            {
                pressedKeys.add (noteNumber);
                lastPressedKey = noteNumber; // recording last pressed key to use for starting point in most algorithms
                //            bufferLastPressedKey = newNoteNumber;
                DBG ("UPDATING lastPressedKey to: " << lastPressedKey);
                //            DBG ("UPDATING bufferLastPressedKey to: " << bufferLastPressedKey);
            }
            else if (message.isNoteOff())
            {
                //            DBG ("laspressedKey : note off found" << lastPressedKey);
                pressedKeys.removeValue(noteNumber);
            }
        }
    }
}

double ArpAlgoAudioProcessor::getHostBpmOrDefault()
{
    const double BPM_DEFAULT = 120;
    const juce::AudioPlayHead* playHead = getPlayHead();
    if (playHead != nullptr)
    {
//        debugText = "playhead is valid\n";
//        DBG ("playhead is valid");
        juce::Optional<juce::AudioPlayHead::PositionInfo> position = playHead->getPosition();
        if (position.hasValue())
        {
//            debugText += "position has a value, trying to access it\n";
//            DBG ("position has a value, trying to access it\n");
            juce::Optional<double> foundBPM = position->getBpm();
            if (foundBPM.hasValue())
            {
//                debugText += "BPM has a value of ";
//                debugText += juce::String(*foundBPM);
//                debugText += "\n";
//                DBG ("BPM has a value of " << *foundBPM);
                return *foundBPM;
            }
            else
            {
//                debugText += "no value found for BPM\n";
//                DBG ("no value found for BPM (will defatult to 120");
            }
            
        }
        else
        {
//            debugText += "position has no value.\n";
//            DBG ("position has no value.");
        }
    }
    else
    {
//        debugText = "playhead is nullptr";
//        DBG ("playhead is nullptr");
    }
    return BPM_DEFAULT;
}

//bool ArpAlgoAudioProcessor::differentNewKeyIsPressed(int bufferLastPressedKey, int midiBufferSize) const
bool ArpAlgoAudioProcessor::differentNewKeyIsPressed(int midiBufferSize) const
{
    // DBG ("diffent key? pattern base key:" << patternBaseKey << ", buffer last pressed key: " << bufferLastPressedKey);
    // a different key cannot be pressed if there is no new notes (buffer size == 0).
    // It is new if the new key is different from the previous recorded value and not
    // still initialised to -1 (default value).
//    if (midiBufferSize == 0)
//    {
//        DBG ("differentNewKeyIsPressed returning false, buffersize = 0");
//        return false;
//    }
//    else if (lastPressedKey != patternBaseNote)
        if (lastPressedKey != patternBaseNote)
    {
        DBG ("NEW DIFFERRENT KEY FOUND: lastPressedKey is " << lastPressedKey << ", patternBaseNote is " << patternBaseNote);
        return true;
    }
//    else if (bufferLastPressedKey == -1)
//    {
//        DBG ("buffer last pressed key is -1");
////        newKeyFound = false;
//    }

//    if (midiBufferSize != 0 && patternBaseKey != bufferLastPressedKey && bufferLastPressedKey != -1)
//      if (midiBufferSize != 0 && lastPressedKey != bufferLastPressedKey)
//    {
//        DBG ("\t\t NEW KEY FOUND");
//        return true;
//    }
    return false;
}

//bool ArpAlgoAudioProcessor::shouldOutputNotes() const
//{
//    return !patternIsExhausted() && !heldNotes.isEmpty();
//}
    // Do NOT output notes (no pattern to output) if the pattern's end is reached
//    if (patternIsExhausted())
//    {
//        return false;
//    }
//    if (heldNotes.isEmpty())
//    {
//        return false;
//    }
//    return true;
//    // DO output pattern if writing pattern mode is on, and a pattern has been created
//    if (isWritingPatternModeOn && !pattern.isEmpty())
//    {
//        return true;
//    }
//    // DO output pattern if not in writing mode, but keys are currently pressed held.
//    if (!isWritingPatternModeOn && !heldNotes.isEmpty())
//    {
//        if (pattern.isEmpty())
//        {
//            DBG ("Pattern should NOT be empty");
//            jassertfalse;
//        }
//        return true;
//    }
//    // Default case: no notes to output.
//    return false;
//}

bool ArpAlgoAudioProcessor::patternIsExhausted() const
{
    bool isExhausted = currentNote != -1 && currentNote >= pattern.size();
    if (isExhausted)
    {
        DBG ("PATTERN IS EXHAUSTED");
        DBG ("current note is " << currentNote);
        DBG ("pattern size is " << pattern.size());
    }
    return isExhausted;
}

bool ArpAlgoAudioProcessor::shouldSendCleanupNoteOffMessage() const
{
    return pressedKeys.isEmpty() && lastNoteValue != -1;
    //    return heldNotes.isEmpty() && lastNoteValue != -1 && (!isWritingPatternModeOn || (isWritingPatternModeOn && patternIsExhausted()));
}

//void ArpAlgoAudioProcessor::setIsNewAlgorithmUsed(bool newIsUsed)
//{
//    isNewAlgorithmUsed = newIsUsed;
//}

// DEFAULT PLUGIN FUNCTIONS
void ArpAlgoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ArpAlgoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

const juce::String ArpAlgoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ArpAlgoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ArpAlgoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ArpAlgoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ArpAlgoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ArpAlgoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ArpAlgoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ArpAlgoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ArpAlgoAudioProcessor::getProgramName (int index)
{
    return {};
}

void ArpAlgoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

bool ArpAlgoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ArpAlgoAudioProcessor::createEditor()
{
    return new ArpAlgoAudioProcessorEditor (*this);
}

//==============================================================================
void ArpAlgoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ArpAlgoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ArpAlgoAudioProcessor();
}
