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
  VuMeter( kap::Processor* processor );

  void paint( juce::Graphics& g ) override;

  void timerCallback() override;

  void setGainCallback( std::function< float( int channel ) > callback );

private:
  kap::Processor* mProcessor;
  std::function< float( int ) > mGainCallback;
  std::array< float, 2 > mLevels;

  int numChannels() const { return static_cast< int >( mLevels.size() ); }
};

} // namespace components

#endif // KAP_COMPONENTS_VUMETER_H_