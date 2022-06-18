#pragma once
#include "ScriptEnums.hpp"
#include "MissionStruct.hpp"

namespace Rampage {
	namespace Globals {
		struct UIFlags {
			static bool scaleform_active;
			static bool clean;
			static ScaleformTypes scaleform_type;
		};

		struct RampageData {
			static bool rampage_active;
			static Mission::MissionData current_mission;
		};

		extern std::vector<Mission::MissionData> mission_data;
	}
}