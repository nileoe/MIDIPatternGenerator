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
    Tester t;
    heldNotes.clear();
    currentNote = 0;
    patternNoteIndex = 0;
    lastNoteValue = -1;
    time = 0;
    rate = static_cast<float> (sampleRate);
    // NEW
    lastPressedKey = -1;
}


void ArpAlgoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    jassert (buffer.getNumChannels() == 0);
    const int numSamples = buffer.getNumSamples();
    auto noteDuration = static_cast<int> (std::ceil (rate / 6)); // 6 notes/seconds for now
    int bufferLastPressedKey = -1;

    // CAPTURING PRESSED NOTES (INPUT)
    for (const juce::MidiMessageMetadata metadata : midiMessages)
    {
        const juce::MidiMessage message = metadata.getMessage();
        if      (message.isNoteOn())
        {
            heldNotes.add(message.getNoteNumber());
            bufferLastPressedKey = message.getNoteNumber(); // recording last pressed key
        }
        else if (message.isNoteOff()) heldNotes.removeValue(message.getNoteNumber());
    }
    
    if (differentNewKeyIsPressed(bufferLastPressedKey, midiMessages.getNumEvents()))
    {
        
        DBG ("new key pressed: " << juce::MidiMessage::getMidiNoteName(bufferLastPressedKey, true, true, 0) << ". CREATING NEW PATTERN");
        lastPressedKey = bufferLastPressedKey;
        pattern = AppData::getInstance().getPattern(heldNotes, lastPressedKey);
        currentNote = 0; // reset the index of the pattern note to play.
    }
    midiMessages.clear();
    if (!shouldPatternBeOutputed())
    {
        if (shouldSendCleanupNoteOffMessage())
        {
            DBG ("Sending manual note off message to " << juce::MidiMessage::getMidiNoteName(currentNote, true, true, 0) << " (offset: (manual=0)");
            DBG ("also resetting currentNote to 0");
            currentNote = 0;
            midiMessages.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue), 0);
            lastNoteValue = -1;
        }
        return;
    }
    
    if ((time + numSamples) >= noteDuration)
    {
        auto offset = juce::jmax (0, juce::jmin ((int) (noteDuration - time), numSamples - 1));
        if (lastNoteValue > 0)
        {
            DBG ("Sending note OFF with lastNoteValue of " << juce::MidiMessage::getMidiNoteName (lastNoteValue, true, true, 0) << " (offset: " << offset << ")");
            midiMessages.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue), offset);
            lastNoteValue = -1;
        }
        if (pattern.isEmpty())
        {
            DBG ("Error: Pattern should NOT be empty at this point");
            jassertfalse;
        }
        //        currentNote = (currentNote + 1) % pattern.size();
        lastNoteValue = pattern[currentNote];
        DBG ("Sending note ON with lastNoteValue of " << juce::MidiMessage::getMidiNoteName (lastNoteValue, true, true, 0) << " (offset: " << offset << ")");
        midiMessages.addEvent (juce::MidiMessage::noteOn (1, lastNoteValue, (juce::uint8) 127), offset);
        currentNote ++;
    }
    time = (time + numSamples) % noteDuration;
    if (patternIsExhausted())
    {
        DBG ("pattern exhausted.");
        if (isWritingPatternModeOn)
        {
            isWritingPatternModeOn = false;
            pattern = juce::Array<int>();
            DBG ("Setting writing mode OFF. Setting pattern to empty pattern of initial size " << pattern.size() << ".");
            DBG ("Sending change message to button...");
            // TODO send midi stop message
        }
    }
}


bool ArpAlgoAudioProcessor::differentNewKeyIsPressed(int bufferLastPressedKey, int midiBufferSize) const
{
    // a different key cannot be pressed if there is no new notes (buffer size == 0), the new key is different from
    // the previous value and not still initialised to -1 (initial value).
    return midiBufferSize != 0 && lastPressedKey != bufferLastPressedKey && bufferLastPressedKey != -1;
}

bool ArpAlgoAudioProcessor::shouldPatternBeOutputed() const
{
    // Do NOT output notes (no pattern to output) if the pattern's end is reached
    if (patternIsExhausted())
    {
        return false;
    }
    // DO output pattern if writing pattern mode is on, and a pattern has been created
    if (isWritingPatternModeOn && !pattern.isEmpty())
    {
        return true;
    }
    // DO output pattern if not in writing mode, but keys are currently pressed held.
    if (!isWritingPatternModeOn && !heldNotes.isEmpty())
    {
        if (pattern.isEmpty())
        {
            DBG ("Pattern should NOT be empty");
            jassertfalse;
        }
        return true;
    }
    // Default case: no notes to output.
    return false;
}

bool ArpAlgoAudioProcessor::patternIsExhausted() const
{
//    DBG ("PE: current note = " << currentNote << "\t(pattern size is " << pattern.size() << ")");
//    if(currentNote >= pattern.size())
//        DBG("EXEXEX");
    return currentNote != -1 && currentNote >= pattern.size();
}

bool ArpAlgoAudioProcessor::shouldSendCleanupNoteOffMessage() const
{
    return heldNotes.isEmpty() && lastNoteValue != -1 && (!isWritingPatternModeOn || (isWritingPatternModeOn && patternIsExhausted()));
}

void ArpAlgoAudioProcessor::togglePatternWritingMode()
{
    isWritingPatternModeOn = !isWritingPatternModeOn;
    DBG ("switching writingPatternMode to " << (isWritingPatternModeOn ? "TRUE" : "FALSE"));
}

bool ArpAlgoAudioProcessor::getPatternWritingMode() const
{
    return isWritingPatternModeOn;
}

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
