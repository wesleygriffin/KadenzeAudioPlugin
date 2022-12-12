#include "GainPanel.h"

#include "Processor.h"

namespace ui {

GainPanel::GainPanel( kap::Processor* processor ) : PanelBase{ processor }
{
  setSize( kWidth, kHeight );
}

GainPanel::~GainPanel() = default;

void GainPanel::setParameter( const kap::Parameters::Parameter& parameter )
{
  mDial.reset( new ParameterDial{ mProcessor->getValueTreeState(), parameter } );
  mDial->setBounds(
    static_cast< int >( ( getWidth() * .5f ) - ( ParameterDial::kTotalWidth * .5f ) ),
    static_cast< int >( ( getHeight() * .5f ) - ( ParameterDial::kDialHeight * .5f ) ),
    ParameterDial::kTotalWidth,
    ParameterDial::kDialHeight );
  addAndMakeVisible( mDial.get() );

  mLabel.reset( new juce::Label( parameter.name + "Label", parameter.name ) );
  mLabel->setJustificationType( juce::Justification::centred );
  mLabel->setColour( juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke );
  mLabel->setBounds(
    static_cast< int >( ( getWidth() * .5f ) - ( ParameterDial::kTotalWidth * .5f ) ),
    static_cast< int >( ( getHeight() * .5f ) + ( ParameterDial::kDialHeight * .5f ) ),
    ParameterDial::kTotalWidth,
    ParameterDial::kLabelHeight );
  addAndMakeVisible( mLabel.get() );
}

} // namespace ui