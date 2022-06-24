#pragma once

#include "natives.h"
#include "enums.h"
#include "Globals.hpp"
#include "ScreenUtils.hpp"
#include "Utils.hpp"
#include <vector>

namespace Rampage {
	typedef struct {
		int start_time;
		int kills;
		int vehicle_kills;
		int headshot_count;
		int last_v_spawn;
		int last_p_spawn;
		bool melee_enabled;
		bool pistol_enabled;
		bool rifle_enabled;
		bool shotgun_enabled;
		bool machinegun_enabled;
		bool sniper_enabled;
		bool heavy_enabled;
		bool explosives_enabled;
		bool vehicle_only;
		bool weak_enemies;
		bool rc_only;
		bool headshot_only;
		bool ability_disabled;
		bool extra_kills;
		bool extra_headshots;
		bool extra_vehicles;
		bool only_enemy_vehicles;
		std::vector<Ped> enemy_peds;
		std::vector<Vehicle> enemy_vehicles;
	} CurrentRampageData;

	typedef struct {
		Ped player_clone;
		Vehicle rc_bandito;
		bool exploded;
		int phase;
		int start_time;
	} BanditoData;

	void start_rampage();
	bool process_rampage();
	void end_rampage(bool show_scaleform);
}
