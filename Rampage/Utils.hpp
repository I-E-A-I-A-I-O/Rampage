#pragma once

#include "natives.h"
#include "Globals.hpp"
#include "MissionStruct.hpp"
#include <chrono>

namespace Rampage {
	namespace Utils {
		std::string format_duration(std::chrono::milliseconds ms);
		Hash is_player_in_start_range();
		size_t ran_int(size_t max, size_t min);
		int ran_int(int max, int min);
		bool is_in_range(const Vector3& a, const Vector3& b, const float& range);
	}
}
