#include "Parameters.h"

namespace kap {

Parameters::Parameter const Parameters::kInputGain{ "InputGain", "Input Gain" };
Parameters::Parameter const Parameters::kOutputGain{ "OutputGain", "Output Gain" };
Parameters::Parameter const Parameters::kType{ "DelayType", "Type" };
Parameters::Parameter const Parameters::kDryWet{ "DelayWetDry", "Dry Wet" };
Parameters::Parameter const Parameters::kDelayTime{ "DelayTime", "Delay Time" };
Parameters::Parameter const Parameters::kFeedback{ "DelayFeedback", "Feedback" };
Parameters::Parameter const Parameters::kModRate{ "ModulationRate", "Mod Rate" };
Parameters::Parameter const Parameters::kModDepth{ "ModulationDepth", "Mod Depth" };

} // namespace kap