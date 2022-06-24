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

		struct ScriptConfig {
			static bool rampage_effect_disabled;
			static int start_rampage_key;
			static int detonate_key;
		};

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