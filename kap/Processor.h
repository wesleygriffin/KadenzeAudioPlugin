#ifndef KAP_PROCESSOR_H_
#define KAP_PROCESSOR_H_

#include "managers/PresetManager.h"

#include "dsp/Delay.h"
#include "dsp/Gain.h"
#include "dsp/Lfo.h"

#include <juce_audio_processors/juce_audio_processors.h>

#include <atomic>
#include <memory>
#include <vector>

namespace kap {

class Processor : public juce::AudioProcessor
{
public:
  Processor();
  ~Processor() override;

  void prepareToPlay( double sampleRate, int samplesPerBlock ) override;
  void releaseResources() override;

  bool isBusesLayoutSupported( const BusesLayout& layouts ) const override;

  void processBlock( juce::AudioBuffer< float >&, juce::MidiBuffer& ) override;
  using AudioProcessor::processBlock;

  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram( int index ) override;
  const juce::String getProgramName( int index ) override;
  void changeProgramName( int index, const juce::String& newName ) override;

  void getStateInformation( juce::MemoryBlock& destData ) override;
  void setStateInformation( const void* data, int sizeInBytes ) override;

  const juce::AudioProcessorValueTreeState& getValueTreeState() const noexcept { return mValueTreeState; }
  juce::AudioProcessorValueTreeState& getValueTreeState() noexcept { return mValueTreeState; }

  PresetManager* getPresetManager() { return mPresetManager.get(); }

  float getInputMeterLevel( int channel ) { return mInputGain[ channel ]->getMeterLevel(); }
  float getOutputMeterLevel( int channel ) { return mOutputGain[ channel ]->getMeterLevel(); }

private:
  static constexpr float kMaxDelayTimeInSeconds = 2.f;

  juce::AudioProcessorValueTreeState mValueTreeState;
  std::unique_ptr< PresetManager > mPresetManager;

  std::atomic< float >* mInputGainParam;
  std::atomic< float >* mOutputGainParam;
  std::atomic< float >* mTypeParam;
  std::atomic< float >* mDryWetParam;
  std::atomic< float >* mDelayTimeParam;
  std::atomic< float >* mFeedbackParam;
  std::atomic< float >* mModRateParam;
  std::atomic< float >* mModDepthParam;

  std::vector< std::unique_ptr< dsp::Gain< float > > > mInputGain;
  std::vector< std::unique_ptr< dsp::Gain< float > > > mOutputGain;
  std::vector< std::unique_ptr< dsp::Delay< float > > > mDelay;
  std::vector< std::unique_ptr< dsp::Lfo< float > > > mLfo;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Processor )
};

} // namespace kap

#endif // KAP_PROCESSOR_H_