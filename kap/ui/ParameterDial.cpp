#include "ParameterDial.h"

namespace ui {

ParameterDial::ParameterDial( juce::AudioProcessorValueTreeState& state, const kap::Parameters::Parameter& parameter )
: juce::Slider{ parameter.name }
{
  setSliderStyle( juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag );
  setTextBoxStyle( juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0 );
  setRange( 0, 1, .001 );
  mAttachment.reset( new juce::AudioProcessorValueTreeState::SliderAttachment{ state, parameter, *this } );
}

} // namespace ui