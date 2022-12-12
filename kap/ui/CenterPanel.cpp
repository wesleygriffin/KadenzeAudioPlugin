#include "CenterPanel.h"

#include "CenterPanelMenuBar.h"
#include "FxPanel.h"

namespace ui {

CenterPanel::CenterPanel( kap::Processor* processor )
: PanelBase{ processor }, mMenuBar{ new CenterPanelMenuBar{ processor } }, mFxPanel{ new FxPanel{ processor } }
{
  setSize( kWidth, kHeight );

  mMenuBar->addTypeChangedListener( mFxPanel.get() );

  mMenuBar->setTopLeftPosition( 0, 0 );
  addAndMakeVisible( mMenuBar.get() );

  mFxPanel->setTopLeftPosition( 0, CenterPanelMenuBar::kHeight );
  addAndMakeVisible( mFxPanel.get() );
}

CenterPanel::~CenterPanel()
{
  mMenuBar->removeTypeChangedListener( mFxPanel.get() );
}

} // namespace ui