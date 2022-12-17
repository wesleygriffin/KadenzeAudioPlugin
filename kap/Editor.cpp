#include "Editor.h"

#include "ui_assets.h"

#include "ui/LookAndFeel.h"

namespace kap {

Editor::Editor( Processor& p )
: AudioProcessorEditor{ &p },
  processorRef{ p },
  mMainPanel{ new ui::MainPanel( &p ) },
  mBackgroundImage{ juce::ImageCache::getFromMemory( ui::kadenze_bg_png, ui::kadenze_bg_pngSize ) }
{
  setSize( ui::MainPanel::kWidth, ui::MainPanel::kHeight );
  setLookAndFeel( ui::LookAndFeel::getInstance() );
  ui::LookAndFeel::setDefaultLookAndFeel( ui::LookAndFeel::getInstance() );
  addAndMakeVisible( mMainPanel.get() );
}

Editor::~Editor()
{
  setLookAndFeel( nullptr );
  ui::LookAndFeel::setDefaultLookAndFeel( nullptr );
}

void Editor::paint( juce::Graphics& g )
{
  g.drawImage( mBackgroundImage, getLocalBounds().toFloat() );
}

void Editor::resized() {}

} // namespace kap