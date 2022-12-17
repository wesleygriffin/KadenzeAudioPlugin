#ifndef DSP_GAIN_H_
#define DSP_GAIN_H_

namespace dsp {

template < typename Real >
class Gain
{
public:
  void process( Real const* inBuffer, int numSamples, Real gainInDecibels, Real smoothingCoefficient, Real* outBuffer );

  float getMeterLevel() const { return mOutputSmoothed; }

private:
  Real mGainSmoothed{ 0 };
  Real mOutputSmoothed{ 0 };
};

extern Gain< float > fGain;
extern Gain< double > dGain;

} // namespace dsp

#endif // DSP_GAIN_H_