#include "Gain.h"

#include <cmath>

namespace dsp {

template < typename Real >
void Gain< Real >::process(
  Real const* inBuffer,
  int numSamples,
  Real gainInDecibels,
  Real smoothingCoefficient,
  Real* outBuffer )
{
  mGainSmoothed = mGainSmoothed - smoothingCoefficient * ( mGainSmoothed - gainInDecibels );

  for ( int sample = 0; sample < numSamples; ++sample ) {
    outBuffer[ sample ] = inBuffer[ sample ] * mGainSmoothed;
  }

  Real absOutput = std::abs( outBuffer[ 0 ] );
  mOutputSmoothed = smoothingCoefficient * ( mOutputSmoothed - absOutput ) + absOutput;
}

template class Gain< float >;
template class Gain< double >;

} // namespace dsp