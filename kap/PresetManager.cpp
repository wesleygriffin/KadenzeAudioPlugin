#include "PresetManager.h"

namespace kap {

PresetManager::PresetManager( juce::AudioProcessor* processor, juce::String fileExtension )
: mProcessor{ processor },
  mFileExtension{ std::move( fileExtension ) },
  mPresetDirectory{
    juce::File::getSpecialLocation( juce::File::userDocumentsDirectory ).getFullPathName()
    + juce::File::getSeparatorString() + mProcessor->getName() }
{
  if ( !mPresetDirectory.exists() ) {
    mPresetDirectory.createDirectory();
  }

  updateLocalPresets();
}

std::unique_ptr< juce::XmlElement > PresetManager::getXmlForCurrentPreset()
{
  std::unique_ptr< juce::XmlElement > root( new juce::XmlElement( "Preset" ) );
  root->setAttribute( juce::Identifier( "Name" ), mCurrentPresetName );
  auto& parameters = mProcessor->getParameters();
  for ( int i = 0; i < parameters.size(); ++i ) {
    auto parameter = reinterpret_cast< juce::AudioProcessorParameterWithID* >( parameters.getUnchecked( i ) );
    root->setAttribute( parameter->paramID, parameter->getValue() );
  }
  return root;
}

void PresetManager::loadPresetFromXml( juce::XmlElement* element )
{
  if ( !element->hasAttribute( "Name" ) ) {
    return;
  }

  mCurrentPreset = element;
  auto& parameters = mProcessor->getParameters();

  for ( int i = 0; i < mCurrentPreset->getNumAttributes(); ++i ) {
    const juce::String paramId = mCurrentPreset->getAttributeName( i );
    const float value = static_cast< float >( mCurrentPreset->getDoubleAttribute( paramId ) );
    for ( int j = 0; j < parameters.size(); ++j ) {
      auto parameter = reinterpret_cast< juce::AudioProcessorParameterWithID* >( parameters.getUnchecked( j ) );
      if ( parameter->paramID == paramId ) {
        parameter->setValueNotifyingHost( value );
      }
    }
  }
}

int PresetManager::getNumberOfPresets()
{
  return static_cast< int >( mLocalPresets.size() );
}

juce::String PresetManager::getPresetNameForIndex( int presetIndex )
{
  return mLocalPresets[ presetIndex ].getFileNameWithoutExtension();
}

void PresetManager::createInitPreset()
{
  auto& parameters = mProcessor->getParameters();
  for ( int i = 0; i < parameters.size(); ++i ) {
    auto parameter = reinterpret_cast< juce::AudioProcessorParameterWithID* >( parameters.getUnchecked( i ) );
    parameter->setValueNotifyingHost( parameter->getDefaultValue() );
  }

  mCurrentPresetIsSaved = false;
  mCurrentPresetName = "Untitled";
}

void PresetManager::savePreset()
{
  juce::MemoryBlock destData;
  mProcessor->getStateInformation( destData );
  mCurrentlyLoadedPreset.deleteFile();
  mCurrentlyLoadedPreset.appendData( destData.getData(), destData.getSize() );
  mCurrentPresetIsSaved = true;
}

void PresetManager::saveAsPreset( juce::String presetName )
{
  juce::File presetFile(
    mPresetDirectory.getFullPathName() + juce::File::getSeparatorString() + presetName + mFileExtension );
  if ( !presetFile.exists() ) {
    presetFile.create();
  } else {
    presetFile.deleteFile();
  }

  juce::MemoryBlock destData;
  mProcessor->getStateInformation( destData );
  presetFile.appendData( destData.getData(), destData.getSize() );
  mCurrentPresetIsSaved = true;
  mCurrentPresetName = presetName;
  updateLocalPresets();
}

void PresetManager::loadPresetWithIndex( int presetIndex )
{
  mCurrentlyLoadedPreset = mLocalPresets[ presetIndex ];
  juce::MemoryBlock presetData;
  if ( mCurrentlyLoadedPreset.loadFileAsData( presetData ) ) {
    mCurrentPresetIsSaved = true;
    mCurrentPresetName = getPresetNameForIndex( presetIndex );
    mProcessor->setStateInformation( presetData.getData(), static_cast< int >( presetData.getSize() ) );
  }
}

void PresetManager::updateLocalPresets()
{
  mLocalPresets.clear();
  for ( auto&& entry : juce::RangedDirectoryIterator( mPresetDirectory, true, "*" + mFileExtension ) ) {
    mLocalPresets.push_back( entry.getFile() );
  }
}

} // namespace kap