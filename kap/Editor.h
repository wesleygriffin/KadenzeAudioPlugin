#ifndef KAP_EDITOR_H_
#define KAP_EDITOR_H_

#include "Processor.h"
#include "ui/MainPanel.h"

namespace kap {

class Editor : public juce::AudioProcessorEditor
{
public:
  explicit Editor( Processor& );
  ~Editor() override;

  void paint( juce::Graphics& ) override;
  void resized() override;

private:
  Processor& processorRef;

  std::unique_ptr<ui::MainPanel> mMainPanel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Editor )
};

} // namespace kap

#endif // KAP_EDITOR_H_