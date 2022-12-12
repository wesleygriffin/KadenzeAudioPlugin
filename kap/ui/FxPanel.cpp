#include "FxPanel.h"

#include "ui/LookAndFeel.h"
#include "ui/ParameterDial.h"

#include "Processor.h"

namespace ui {

FxPanel::FxPanel( kap::Processor* processor ) : PanelBase{ processor }
{
  setSize( kWidth, kHeight );
  setStyle(
    static_cast< Style >( mProcessor->getValueTreeState().getParameter( kap::Parameters::kType )->getValue() ) );
}

void FxPanel::setStyle( Style style )
{
  mStyle = style;
  mDials.clear();
  mLabels.clear();

  const int x = static_cast< int >( ( getWidth() * .5f ) - ( ParameterDial::kTotalWidth * .5f ) );
  const int horizontalOffset = static_cast< int >( ParameterDial::kTotalWidth * 1.5 );
  const int y = static_cast< int >( ( getHeight() * .55f ) - ( ParameterDial::kTotalHeight * .5f ) );

  switch ( mStyle ) {
  case Style::kDelay:
    addDial( kap::Parameters::Parameter( kap::Parameters::kDelayTime ), x - horizontalOffset, y );
    addDial( kap::Parameters::Parameter( kap::Parameters::kFeedback ), x, y );
    break;
  case Style::kChorus:
    addDial( kap::Parameters::Parameter( kap::Parameters::kModRate ), x - horizontalOffset, y );
    addDial( kap::Parameters::Parameter( kap::Parameters::kModDepth ), x, y );
    break;
  }

  addDial( kap::Parameters::Parameter( kap::Parameters::kDryWet ), x + horizontalOffset, y );
  repaint();
}

void FxPanel::paint( juce::Graphics& g )
{
  PanelBase::paint( g );

  const std::string label = ( mStyle == Style::kDelay ) ? "DELAY" : "CHORUS";
  g.setColour( LookAndFeel::kColor4 );
  g.setFont( LookAndFeel::kFont3 );
  g.drawFittedText( label, 0, 0, getWidth(), 80, juce::Justification::centred, 1 );
}

void FxPanel::comboBoxChanged( juce::ComboBox* comboBoxThatHasChanged )
{
  setStyle( static_cast< Style >( comboBoxThatHasChanged->getSelectedId() - 1 ) );
}

void FxPanel::addDial( const kap::Parameters::Parameter& parameter, int x, int y )
{
  mDials.emplace_back( new ParameterDial( mProcessor->getValueTreeState(), parameter ) );
  mDials.back()->setBounds( x, y, ParameterDial::kTotalWidth, ParameterDial::kDialHeight );
  addAndMakeVisible( mDials.back().get() );

  mLabels.emplace_back( new juce::Label( parameter.name + "Label", parameter.name ) );
  mLabels.back()->setFont( LookAndFeel::kFont1 );
  mLabels.back()->setJustificationType( juce::Justification::centred );
  mLabels.back()->setBounds(
    x,
    y + static_cast< int >( ParameterDial::kDialHeight * .95f ),
    ParameterDial::kTotalWidth,
    ParameterDial::kLabelHeight );
  addAndMakeVisible( mLabels.back().get() );
}

} // namespace ui