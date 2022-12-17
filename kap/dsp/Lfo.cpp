#include "Lfo.h"

#include <cmath>
#include <cstring>
#include <numbers>

namespace dsp {

template < typename Real >
void Lfo< Real >::setSampleRate( double sampleRate )
{
  mSampleRate = sampleRate;
  mBufferSize = static_cast< size_t >( mSampleRate * mMaxDelayTimeInSeconds );
  mBuffer.reset( new Real[ mBufferSize ] );
  std::memset( mBuffer.get(), 0, mBufferSize * sizeof( Real ) );
};

template < class Real >
void Lfo< Real >::reset()
{
  mBufferSize = 0;
  mBuffer.reset();
}

template < typename Real >
void Lfo< Real >::process( Real rate, Real depth, int numSamples )
{
  const Real rateOverSample = rate / static_cast< Real >( mSampleRate );
  for ( int sample = 0; sample < numSamples; ++sample ) {
    mPhase = ( mPhase + rateOverSample > 1 ) ? mPhase + rateOverSample - 1 : mPhase + rateOverSample;
    const Real lfoPosition = std::sin( mPhase * std::numbers::pi_v< Real > * Real{ 2 } ) * depth;
    mBuffer[ sample ] = lfoPosition;
  }
}

template class Lfo< float >;
template class Lfo< double >;

} // namespace dsp