#include "Editor.h"

#include "ui_assets.h"

namespace kap {

Editor::Editor( Processor& p )
: AudioProcessorEditor{ &p },
  processorRef{ p },
  mLookAndFeel{ new ui::LookAndFeel },
  mMainPanel{ new ui::MainPanel( &p ) },
  mBackgroundImage{ juce::ImageCache::getFromMemory( ui::kadenze_bg_png, ui::kadenze_bg_pngSize ) }
{
  setSize( ui::MainPanel::kWidth, ui::MainPanel::kHeight );
  setLookAndFeel( mLookAndFeel.get() );
  ui::LookAndFeel::setDefaultLookAndFeel( mLookAndFeel.get() );
  addAndMakeVisible( mMainPanel.get() );
}

Editor::~Editor() {}

void Editor::paint( juce::Graphics& g )
{
  g.drawImage( mBackgroundImage, getLocalBounds().toFloat() );
}

void Editor::resized() {}

} // namespace kap