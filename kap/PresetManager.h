#ifndef KAP_PRESETMANAGER_H_
#define KAP_PRESETMANAGER_H_

#include <juce_audio_processors/juce_audio_processors.h>

namespace kap {

class PresetManager
{
public:
  PresetManager( juce::AudioProcessor* processor, juce::String fileExtension );

  std::unique_ptr< juce::XmlElement > getXmlForCurrentPreset();
  void loadPresetFromXml( juce::XmlElement* element );

  int getNumberOfPresets();
  juce::String getPresetNameForIndex( int presetIndex );

  void createInitPreset();
  void savePreset();
  void saveAsPreset( juce::String presetName );
  void loadPresetWithIndex( int presetIndex );

  bool getIsCurrentPresetSaved() const { return mCurrentPresetIsSaved; }
  juce::String getCurrentPresetName() const { return mCurrentPresetName; }

private:
  juce::AudioProcessor* mProcessor{ nullptr };
  juce::String mFileExtension{};

  juce::File mPresetDirectory{};
  juce::File mCurrentlyLoadedPreset{};
  std::vector< juce::File > mLocalPresets{};

  bool mCurrentPresetIsSaved{ false };
  juce::String mCurrentPresetName{ "Untitled" };
  juce::XmlElement* mCurrentPreset{ nullptr };

  void updateLocalPresets();
};

} // namespace kap

#endif // KAP_PRESETMANAGER_H_
