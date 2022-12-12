#include "Editor.h"

namespace kap {

Editor::Editor( Processor& p ) : AudioProcessorEditor{ &p }, processorRef{ p }, mMainPanel{ new ui::MainPanel( &p ) }
{
  setSize( ui::MainPanel::kWidth, ui::MainPanel::kHeight );
  addAndMakeVisible(mMainPanel.get());
}

Editor::~Editor() {}

void Editor::paint( juce::Graphics& g )
{
  g.fillAll( getLookAndFeel().findColour( juce::ResizableWindow::backgroundColourId ) );
}

void Editor::resized() {}

} // namespace kap