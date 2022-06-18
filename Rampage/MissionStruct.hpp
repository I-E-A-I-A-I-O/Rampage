#pragma once

#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "ScriptEnums.hpp"
#include "types.h"

using json = nlohmann::json;

namespace Rampage {
	namespace Mission {
		typedef struct {
			Hash mission_hash;
			Hash relationship_group;
			Vector3 location;
			std::string name;
			int extra_objectives;
			int mission_flags;
			int time;
			float multiplier;
			int target;
			int extra_target_1;
			int extra_target_2;
			int extra_target_3;
			std::vector<Hash> ped_models;
			std::vector<Hash> vehicle_models;
			std::vector<Vector3> ped_spawnpoints;
			std::vector<Vector3> vehicle_spawnpoints;
		} MissionData;
	}
}