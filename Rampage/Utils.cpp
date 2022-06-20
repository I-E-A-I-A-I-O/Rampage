#include "pch.h"
#include "Utils.hpp"

using namespace Rampage;



std::string Utils::format_duration(std::chrono::milliseconds ms) {
	using namespace std::chrono;
	auto secs = duration_cast<seconds>(ms);
	ms -= duration_cast<milliseconds>(secs);
	auto mins = duration_cast<minutes>(secs);
	secs -= duration_cast<seconds>(mins);

	std::stringstream ss;

	if (mins.count() < 10)
		ss << "0";

	ss << mins.count() << ":";

	if (secs.count() < 10)
		ss << "0";

	ss << secs.count();

	return ss.str();
}

size_t Utils::ran_int(size_t max, size_t min)
{
	return min + (std::rand() % (max - min + 1));
}

int Utils::ran_int(int max, int min)
{
	return min + (std::rand() % (max - min + 1));
}

bool is_busy() {
	return Globals::RampageData::rampage_active ||
		PLAYER::GET_PLAYER_WANTED_LEVEL(0) > 0 ||
		MISC::GET_MISSION_FLAG();
}

bool start_in_vehicle(const Mission::MissionData& mission) {
	if (mission.mission_flags == 13 || mission.mission_flags == 8 << 13)
		return PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
	else
		return !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
}

bool Utils::is_in_range(const Vector3& a, const Vector3& b, const float& range)
{
	Vector3 dif = Vector3();
	dif.x = a.x - b.x;
	dif.y = a.y - b.y;
	dif.z = a.z - b.z;
	float length = (dif.x * dif.x) + (dif.y * dif.y) + (dif.z * dif.z);
	return std::sqrt(length) < range;
}

Hash Utils::is_player_in_start_range() {
	if (is_busy()) return 0;

	Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);

	for (const auto& mission : Globals::mission_data) {
		if (mission.last_played > 0)
		{
			if (MISC::GET_GAME_TIMER() - mission.last_played > 300000)
				if (is_in_range(player_coords, mission.location, 10) && start_in_vehicle(mission))
					return mission.mission_hash;
		}
		else if (is_in_range(player_coords, mission.location, 10) && start_in_vehicle(mission))
				return mission.mission_hash;
	}

	return 0;
}
