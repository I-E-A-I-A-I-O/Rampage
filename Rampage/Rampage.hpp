#pragma once

namespace Rampage {
	typedef struct {
		int remaining_time;
		int kills;
		int vehicle_kills;
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
		bool extra_kills;
		bool extra_headshots;
		bool extra_vehicles;
		std::vector<Ped> enemy_peds = {};
		std::vector<Vehicle> enemy_vehicles = {};
	} CurrentRampageData;

	void start_rampage();
	void end_rampage();
}
