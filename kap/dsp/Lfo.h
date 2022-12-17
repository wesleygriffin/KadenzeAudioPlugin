#ifndef DSP_LFO_H_
#define DSP_LFO_H_

#include <memory>

namespace dsp {

template < typename Real >
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

extern Lfo< float > fLfo;
extern Lfo< double > dLfo;

} // namespace dsp

#endif // DSP_LFO_H_
