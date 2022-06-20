#pragma once

#include "natives.h"
#include "Globals.hpp"
#include "MissionStruct.hpp"

namespace Rampage {
	namespace Utils {
		Hash is_player_in_start_range();
		size_t ran_int(size_t max, size_t min);
		int ran_int(int max, int min);
	}
}
