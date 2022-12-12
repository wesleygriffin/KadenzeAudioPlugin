#ifndef KAP_UI_PARAMTERCOMBOBOX_H_
#define KAP_UI_PARAMTERCOMBOBOX_H_

#include "Parameters.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <memory>

namespace ui {

class ParameterComboBox final : public juce::ComboBox
{
public:
  ParameterComboBox( juce::AudioProcessorValueTreeState& state, const kap::Parameters::Parameter& parameter );

  static constexpr int kWidth = 85;

private:
  std::unique_ptr< juce::AudioProcessorValueTreeState::ComboBoxAttachment > mAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ParameterComboBox );
};

} // namespace ui

#endif // KAP_UI_PARAMTERCOMBOBOX_H_
