#include "TopPanel.h"

#include "ui/LookAndFeel.h"

#include "Processor.h"

namespace ui {

TopPanel::TopPanel( kap::Processor* processor ) : PanelBase{ processor }
{
  setSize( kWidth, kHeight );
  int buttonX = 15;
  int buttonY = 10;

  mInitPresetButton.reset( new juce::TextButton( "INIT" ) );
  mInitPresetButton->setBounds( buttonX, buttonY, kPresetButtonWidth, kPresetButtonHeight );
  mInitPresetButton->onClick = [ & ]() {
    mProcessor->getPresetManager()->createInitPreset();
    updatePresetComboBox();
  };
  addAndMakeVisible( mInitPresetButton.get() );
  buttonX += kPresetButtonWidth;

  mSavePresetButton.reset( new juce::TextButton( "SAVE" ) );
  mSavePresetButton->setBounds( buttonX, buttonY, kPresetButtonWidth, kPresetButtonHeight );
  mSavePresetButton->onClick = [ & ]() { mProcessor->getPresetManager()->savePreset(); };
  addAndMakeVisible( mSavePresetButton.get() );
  buttonX += kPresetButtonWidth;

  mSaveAsPresetButton.reset( new juce::TextButton( "SAVE AS" ) );
  mSaveAsPresetButton->setBounds( buttonX, buttonY, kPresetButtonWidth, kPresetButtonHeight );
  mSaveAsPresetButton->onClick = [ & ]() { displaySaveAsPopup(); };
  addAndMakeVisible( mSaveAsPresetButton.get() );
  buttonX += kPresetButtonWidth;

  int comboBoxX = static_cast< int >( kWidth * .5f - kPresetComboBoxWidth * .5f );

  mPresetComboBox.reset( new juce::ComboBox() );
  mPresetComboBox->setBounds( comboBoxX, buttonY, kPresetComboBoxWidth, kPresetComboBoxHeight );
  mPresetComboBox->onChange = [ & ]() {
    if ( mPresetComboBox->getSelectedItemIndex() >= 0 ) {
      mProcessor->getPresetManager()->loadPresetWithIndex( mPresetComboBox->getSelectedItemIndex() );
    }
  };
  addAndMakeVisible( mPresetComboBox.get() );

  updatePresetComboBox();
}

void TopPanel::paint( juce::Graphics& g )
{
  PanelBase::paint( g );
  g.setColour( LookAndFeel::getInstance()->getTopPanelTextColour( *this ) );
  g.setFont( LookAndFeel::getInstance()->getTopPanelTextFont( *this ) );
  g.drawFittedText(
    "KADENZE AUDIO PLUGIN", kWidth - kLabelWidth, 0, kLabelWidth, getHeight(), juce::Justification::centred, 1 );
}

void TopPanel::updatePresetComboBox()
{
  auto presetManager = mProcessor->getPresetManager();

  const juce::String currentPresetName = presetManager->getCurrentPresetName();
  mPresetComboBox->clear( juce::dontSendNotification );

  const int numPresets = presetManager->getNumberOfPresets();
  for ( int i = 0; i < numPresets; ++i ) {
    mPresetComboBox->addItem( presetManager->getPresetNameForIndex( i ), i + 1 );
  }

  mPresetComboBox->setText( presetManager->getCurrentPresetName() );
}

void TopPanel::displaySaveAsPopup()
{
  auto presetManager = mProcessor->getPresetManager();

  juce::AlertWindow window{ "Save As", "Please enter a name for your preset", juce::AlertWindow::NoIcon };
  window.centreAroundComponent( this, getWidth(), getHeight() );
  window.addTextEditor( "presetName", presetManager->getCurrentPresetName(), "Preset name" );
  window.addButton( "Confirm", 1 );
  window.addButton( "Cancel", 0 );

  if ( window.runModalLoop() ) {
    presetManager->saveAsPreset( window.getTextEditor( "presetName" )->getText() );
    updatePresetComboBox();
  }
}

} // namespace ui