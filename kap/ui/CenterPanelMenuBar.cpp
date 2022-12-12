#include "CenterPanelMenuBar.h"

#include "ui/FxPanel.h"
#include "ui/ParameterComboBox.h"

#include "Parameters.h"
#include "Processor.h"

namespace ui {

CenterPanelMenuBar::CenterPanelMenuBar( kap::Processor* processor ) : PanelBase{ processor }
{
  setSize( kWidth, kHeight );

  mTypeComboBox.reset( new ParameterComboBox( mProcessor->getValueTreeState(), kap::Parameters::kType ) );
  mTypeComboBox->setBounds( getWidth() - ParameterComboBox::kWidth, 0, ParameterComboBox::kWidth, getHeight() );

  mTypeComboBox->addItem( "Delay", static_cast< int >( FxPanel::Style::kDelay ) + 1 );
  mTypeComboBox->addItem( "Chorus", static_cast< int >( FxPanel::Style::kChorus ) + 1 );
  mTypeComboBox->setSelectedItemIndex(
    static_cast< int >( mProcessor->getValueTreeState().getParameter( kap::Parameters::kType )->getValue() ),
    juce::dontSendNotification );
  addAndMakeVisible( mTypeComboBox.get() );
}

CenterPanelMenuBar::~CenterPanelMenuBar() = default;

void CenterPanelMenuBar::addTypeChangedListener( juce::ComboBox::Listener* listener )
{
  mTypeComboBox->addListener( listener );
}

void CenterPanelMenuBar::removeTypeChangedListener( juce::ComboBox::Listener* listener )
{
  mTypeComboBox->removeListener( listener );
}

} // namespace ui