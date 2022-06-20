#pragma once
#include "ScriptEnums.hpp"
#include "MissionStruct.hpp"
#include <map>

namespace Rampage {
	namespace Globals {

		typedef struct {
			int value;
			bool passed;
		} ScaleformObjective;

		struct UIFlags {
			static bool scaleform_active;
			static bool clean;
			static ScaleformTypes scaleform_type;
			static std::map<std::string, ScaleformObjective> extraObjectives;
			static int time_left;
			static int kill_count;
		};

		struct RampageData {
			static bool rampage_active;
			static Mission::MissionData current_mission;
		};

		extern std::vector<Mission::MissionData> mission_data;
	}
}