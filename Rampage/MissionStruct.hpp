#pragma once

#include "nlohmann/json.hpp"
#include "types.h"
#include <string>
#include <vector>

using json = nlohmann::json;

namespace Rampage {
	namespace Mission {
		typedef struct {
			Hash mission_hash;
			Hash relationship_group;
			Hash melee_override;
			Hash pistol_override;
			Hash machinegun_override;
			Hash shotgun_override;
			Hash rifle_override;
			Hash sniper_override;
			Hash heavy_override;
			Hash explosive_override;
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
			int last_played;
			Blip blip;
			std::vector<Hash> ped_models;
			std::vector<Hash> vehicle_models;
			std::vector<Vector3> ped_spawnpoints;
			std::vector<Vector3> vehicle_spawnpoints;
		} MissionData;
	}
}