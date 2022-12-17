#include "Processor.h"
#include "Editor.h"
#include "Parameters.h"
#include "Smoothing.h"

namespace kap {

namespace {

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
  juce::AudioProcessorValueTreeState::ParameterLayout layout;

  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kInputGain.id, Parameters::kInputGain.name, 0.f, 1.f, .5f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kOutputGain.id, Parameters::kOutputGain.name, 0.f, 1.f, .5f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kType.id, Parameters::kType.name, 0.f, 1.f, 0.f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kDryWet.id, Parameters::kDryWet.name, 0.f, 1.f, .5f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kDelayTime.id, Parameters::kDelayTime.name, 0.f, 1.f, .5f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kFeedback.id, Parameters::kFeedback.name, 0.f, 1.f, .5f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kModRate.id, Parameters::kModRate.name, 0.f, 1.f, .5f ) ) );
  layout.add( std::unique_ptr< juce::RangedAudioParameter >(
    new juce::AudioParameterFloat( Parameters::kModDepth.id, Parameters::kModDepth.name, 0.f, 1.f, .5f ) ) );

  return layout;
}

} // namespace

Processor::Processor() : AudioProcessor
{
  BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
    .withInput( "Input", juce::AudioChannelSet::stereo(), true )
#endif
    .withOutput( "Output", juce::AudioChannelSet::stereo(), true )
#endif
}
, mValueTreeState{ *this, nullptr, juce::Identifier( "Preset" ), createParameterLayout() },
  mPresetManager{ new PresetManager{ this, ".kap" } }
{
  juce::Logger::setCurrentLogger(
    juce::FileLogger::createDefaultAppLogger( "Fraktured Labs", "KadenzeAudioPlugin.txt", "Processor Starting" ) );
  mInputGainParam = mValueTreeState.getRawParameterValue( Parameters::kInputGain );
  mOutputGainParam = mValueTreeState.getRawParameterValue( Parameters::kOutputGain );
  mTypeParam = mValueTreeState.getRawParameterValue( Parameters::kType );
  mDryWetParam = mValueTreeState.getRawParameterValue( Parameters::kDryWet );
  mDelayTimeParam = mValueTreeState.getRawParameterValue( Parameters::kDelayTime );
  mFeedbackParam = mValueTreeState.getRawParameterValue( Parameters::kFeedback );
  mModRateParam = mValueTreeState.getRawParameterValue( Parameters::kModRate );
  mModDepthParam = mValueTreeState.getRawParameterValue( Parameters::kModDepth );

  const int numChannels = getTotalNumInputChannels();
  for ( int i = 0; i < numChannels; ++i ) {
    mInputGain.emplace_back( new dsp::Gain< float > );
    mOutputGain.emplace_back( new dsp::Gain< float > );
    mDelay.emplace_back( new dsp::Delay< float >( kMaxDelayTimeInSeconds ) );
    mLfo.emplace_back( new dsp::Lfo< float >( kMaxDelayTimeInSeconds ) );
  }
}

Processor::~Processor() {}

const juce::String Processor::getName() const
{
  return JucePlugin_Name;
}

bool Processor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool Processor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool Processor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double Processor::getTailLengthSeconds() const
{
  return 0.0;
}

int Processor::getNumPrograms()
{
  return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Processor::getCurrentProgram()
{
  return 0;
}

void Processor::setCurrentProgram( int index )
{
  juce::ignoreUnused( index );
}

const juce::String Processor::getProgramName( int index )
{
  juce::ignoreUnused( index );
  return {};
}

void Processor::changeProgramName( int index, const juce::String& newName )
{
  juce::ignoreUnused( index, newName );
}

void Processor::prepareToPlay( double sampleRate, int samplesPerBlock )
{
  juce::ignoreUnused( samplesPerBlock );
  const int numChannels = getTotalNumInputChannels();
  for ( int i = 0; i < numChannels; ++i ) {
    mDelay[ i ]->setSampleRate( sampleRate );
    mLfo[ i ]->setSampleRate( sampleRate );
  }
}

void Processor::releaseResources()
{
  const int numChannels = getTotalNumInputChannels();
  for ( int i = 0; i < numChannels; ++i ) {
    mDelay[ i ]->reset();
    mLfo[ i ]->reset();
  }
}

bool Processor::isBusesLayoutSupported( const BusesLayout& layouts ) const
{
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused( layouts );
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (
    layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
    && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo() )
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if ( layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet() ) return false;
#endif

  return true;
#endif
}

void Processor::processBlock( juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midiMessages )
{
  juce::ignoreUnused( midiMessages );

  juce::ScopedNoDenormals noDenormals;
  const int totalNumInputChannels = getTotalNumInputChannels();
  const int totalNumOutputChannels = getTotalNumOutputChannels();
  const int numSamples = buffer.getNumSamples();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for ( int i = totalNumInputChannels; i < totalNumOutputChannels; ++i ) {
    buffer.clear( i, 0, buffer.getNumSamples() );
  }

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.
  for ( int channel = 0; channel < totalNumInputChannels; ++channel ) {
    auto* channelData = buffer.getWritePointer( channel );

    const float inputGainMapped =
      juce::Decibels::decibelsToGain( juce::jmap< float >( *mInputGainParam, -24.f, 24.f ), -24.f );

    mInputGain[ channel ]->process(
      channelData, numSamples, inputGainMapped, kParameterSmoothingCoeff_Fine< float >, channelData );

    const float rate = ( channel == 0 ) ? 0.f : static_cast< float >( *mModRateParam );
    const float rateMapped = juce::jmap< float >( rate, .01f, 10.f );
    mLfo[ channel ]->process( rate, *mModDepthParam, numSamples );

    const float feedbackMapped = ( *mTypeParam < 1.f ) ? juce::jmap< float >( *mFeedbackParam, 0.f, 1.2f ) : 0.f;
    const float delayTime = ( *mTypeParam < 1.f ) ? static_cast< float >( *mDelayTimeParam ) : .003f;
    mDelay[ channel ]->process(
      channelData,
      numSamples,
      *mDelayTimeParam,
      *mFeedbackParam,
      kParameterSmoothingCoeff_Fine< float >,
      *mDryWetParam,
      ( *mTypeParam < 1.f ) ? nullptr : mLfo[ channel ]->getBuffer(),
      channelData );

    const float outputGainMapped =
      juce::Decibels::decibelsToGain( juce::jmap< float >( *mOutputGainParam, -24.f, 24.f ), -24.f );
    mOutputGain[ channel ]->process(
      channelData, numSamples, outputGainMapped, kParameterSmoothingCoeff_Fine< float >, channelData );
  }
}

bool Processor::hasEditor() const
{
  return true;
}

juce::AudioProcessorEditor* Processor::createEditor()
{
  return new Editor( *this );
}

void Processor::getStateInformation( juce::MemoryBlock& destData )
{
  juce::XmlElement root( "State" );
  std::unique_ptr< juce::XmlElement > preset( mPresetManager->getXmlForCurrentPreset() );
  root.prependChildElement( preset.release() ); // hmm.... not happy about that
  copyXmlToBinary( root, destData );
}

void Processor::setStateInformation( const void* data, int sizeInBytes )
{
  std::unique_ptr< juce::XmlElement > root( getXmlFromBinary( data, sizeInBytes ) );
  if ( root && root->hasTagName( "State" ) ) {
    for ( auto* child : root->getChildIterator() ) {
      if ( child->hasTagName( "Preset" ) ) {
        mPresetManager->loadPresetFromXml( child );
      }
    }
  }
}

} // namespace kap

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new kap::Processor();
}