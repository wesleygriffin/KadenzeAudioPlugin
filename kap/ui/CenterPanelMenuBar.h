#ifndef KAP_UI_CENTERPANELMENUBAR_H_
#define KAP_UI_CENTERPANELMENUBAR_H_

#include "ui/CenterPanel.h"
#include "ui/PanelBase.h"

#include <memory>

namespace ui {

class ParameterComboBox;

class CenterPanelMenuBar final : public PanelBase
{
public:
  CenterPanelMenuBar( kap::Processor* processor );
  ~CenterPanelMenuBar();

  void addTypeChangedListener( juce::ComboBox::Listener* listener );
  void removeTypeChangedListener( juce::ComboBox::Listener* listener );

  static constexpr int kWidth = CenterPanel::kWidth;
  static constexpr int kHeight = 35;

private:
  std::unique_ptr< ParameterComboBox > mTypeComboBox;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CenterPanelMenuBar );
};

} // namespace ui

#endif // KAP_UI_CENTERPANELMENUBAR_H_
