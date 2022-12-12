#include "MainPanel.h"

#include "ui/CenterPanel.h"
#include "ui/GainPanel.h"
#include "ui/TopPanel.h"

#include "Parameters.h"

namespace ui {

MainPanel::MainPanel( kap::Processor* processor )
: PanelBase{ processor },
  mTopPanel{ new TopPanel( processor ) },
  mInputGainPanel{ new GainPanel{ processor } },
  mOutputGainPanel{ new GainPanel{ processor } },
  mCenterPanel{ new CenterPanel{ processor } }
{
  setSize( kWidth, kHeight );

  addAndMakeVisible( mTopPanel.get() );

  mInputGainPanel->setTopLeftPosition( 0, ui::TopPanel::kHeight );
  mInputGainPanel->setParameter( kap::Parameters::Parameter( kap::Parameters::kInputGain ) );
  addAndMakeVisible( mInputGainPanel.get() );

  mOutputGainPanel->setTopRightPosition( kWidth, ui::TopPanel::kHeight );
  mOutputGainPanel->setParameter( kap::Parameters::Parameter( kap::Parameters::kOutputGain ) );
  addAndMakeVisible( mOutputGainPanel.get() );

  mCenterPanel->setTopLeftPosition( ui::GainPanel::kWidth, ui::TopPanel::kHeight );
  addAndMakeVisible( mCenterPanel.get() );
}

MainPanel::~MainPanel() = default;

} // namespace ui