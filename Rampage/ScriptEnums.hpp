#pragma once

namespace Rampage {
	enum class ScaleformTypes
	{
		PassedWithObjectives,
		RampageStarted
	};

	enum class ExtraObjectives {
		NONE,
		KILL_AMMOUNT = 1,
		HEADSHOT_AMMOUNT,
		VEHICLE_AMMOUNT
	};

	enum class MissionFlags {
		DEFAULT,
		MELEE_ONLY,
		WEAK_ENEMIES,
		HEADSHOT_ONLY,
		SNIPER_ONLY,
		EXPLOSIVE_ONLY,
		HEAVY_ONLY,
		PISTOL_ONLY,
		NO_SPECIAL_ABILITY,
		RIFLE_ONLY,
		SHOTGUN_ONLY,
		MACHINEGUN_ONLY,
		RC,
		DRIVE_BY
	};
}
