#ifndef KAP_DSP_LFO_H_
#define KAP_DSP_LFO_H_

#include "util/Interpolation.h"

#include <juce_core/juce_core.h>

#include <memory>

namespace dsp {

template < class Real >
class Lfo
{
public:
  Lfo( double maxDelayTimeInSeconds ) : mMaxDelayTimeInSeconds{ maxDelayTimeInSeconds } {}

  void setSampleRate( double sampleRate );
  void reset();
  void process( Real rate, Real depth, int numSamples );

  Real const* getBuffer() { return mBuffer.get(); }

private:
  double mMaxDelayTimeInSeconds{ -1. };
  double mSampleRate{ -1. };
  int mDelayIndex{ 0 };
  size_t mBufferSize{ 0 };
  Real mPhase{ 0 };
  std::unique_ptr< Real[] > mBuffer{};
};

template < class Real >
void Lfo< Real >::setSampleRate( double sampleRate )
{
  mSampleRate = sampleRate;
  mBufferSize = static_cast< size_t >( mSampleRate * mMaxDelayTimeInSeconds );
  mBuffer.reset( new Real[ mBufferSize ] );
  juce::zeromem( mBuffer.get(), mBufferSize * sizeof( Real ) );
};

template < class Real >
void Lfo< Real >::reset()
{
  mBufferSize = 0;
  mBuffer.reset();
}

template < class Real >
void Lfo< Real >::process( Real rate, Real depth, int numSamples )
{
  const Real rateMapped = juce::jmap( rate, Real( 0 ), Real( 1 ), Real( .01 ), Real( 10 ) );
  const Real rateOverSample = rateMapped / static_cast< Real >( mSampleRate );
  for ( int sample = 0; sample < numSamples; ++sample ) {
    mPhase = ( mPhase + rateOverSample > 1 ) ? mPhase + rateOverSample - 1 : mPhase + rateOverSample;
    const Real lfoPosition = std::sin( mPhase * juce::MathConstants< Real >::twoPi ) * depth;
    mBuffer[ sample ] = lfoPosition;
  }
}

} // namespace dsp

#endif // KAP_DSP_LFO_H_
