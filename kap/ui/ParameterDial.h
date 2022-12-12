#ifndef KAP_UI_PARAMTERDIAL_H_
#define KAP_UI_PARAMTERDIAL_H_

#include "Parameters.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <memory>

namespace ui {

class ParameterDial final : public juce::Slider
{
public:
  ParameterDial( juce::AudioProcessorValueTreeState& state, const kap::Parameters::Parameter& parameter );

  static constexpr int kDialWidth = 64;
  static constexpr int kDialHeight = 64;
  static constexpr int kLabelWidth = 96;
  static constexpr int kLabelHeight = 32;
  static constexpr int kTotalWidth = kLabelWidth;
  static constexpr int kTotalHeight = kDialHeight + kLabelHeight;

private:
  std::unique_ptr< juce::AudioProcessorValueTreeState::SliderAttachment > mAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ParameterDial );
};

} // namespace ui

#endif // KAP_UI_PARAMTERDIAL_H_
