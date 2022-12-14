#ifndef KAP_PARAMETERS_H_
#define KAP_PARAMETERS_H_

#include <juce_audio_processors/juce_audio_processors.h>

namespace kap {

class Parameters
{
public:
  struct Parameter
  {
    const juce::ParameterID id;
    const juce::String name;
    const std::size_t idHash;
    operator juce::StringRef() const { return id.getParamID(); }
    operator juce::String() const { return id.getParamID(); }
  };

  static const Parameter kInputGain;
  static const Parameter kOutputGain;
  static const Parameter kType;
  static const Parameter kDryWet;
  static const Parameter kDelayTime;
  static const Parameter kFeedback;
  static const Parameter kModRate;
  static const Parameter kModDepth;
};

inline bool operator==( const Parameters::Parameter& lhs, const Parameters::Parameter& rhs ) noexcept
{
  return lhs.idHash == rhs.idHash;
}

} // namespace kap

#endif // KAP_PARAMETERS_H_
