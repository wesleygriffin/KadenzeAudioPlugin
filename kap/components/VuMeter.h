#ifndef KAP_COMPONENTS_VUMETER_H_
#define KAP_COMPONENTS_VUMETER_H_

#include <juce_gui_basics/juce_gui_basics.h>

#include <functional>
#include <vector>

namespace kap {
class Processor;
} // namespace kap

namespace components {

class VuMeter : public juce::Component, public juce::Timer
{
public:
  VuMeter( float smoothingCoefficient );

  void paint( juce::Graphics& g ) override;

  void timerCallback() override;

  void setGainCallback( std::function< float( int channel ) > callback );

  enum ColourIds
  {
    meterUnfilledColourId = 0x1b00, /**< The colour for the unfilled part of the meter. */
    meterFilledColourId = 0x1a00 /**< The colour for the filled part of the meter. */
  };

private:
  const float mSmoothingCoefficient;
  std::function< float( int ) > mGainCallback;
  std::array< float, 2 > mLevels;

  int numChannels() const { return static_cast< int >( mLevels.size() ); }
};

} // namespace components

#endif // KAP_COMPONENTS_VUMETER_H_