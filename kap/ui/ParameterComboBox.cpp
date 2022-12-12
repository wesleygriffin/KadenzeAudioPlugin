#include "ParameterComboBox.h"

namespace ui {

ParameterComboBox::ParameterComboBox(
  juce::AudioProcessorValueTreeState& state,
  const kap::Parameters::Parameter& parameter )
: juce::ComboBox{ parameter.name }
{
  mAttachment.reset( new juce::AudioProcessorValueTreeState::ComboBoxAttachment{ state, parameter, *this } );
}

} // namespace ui