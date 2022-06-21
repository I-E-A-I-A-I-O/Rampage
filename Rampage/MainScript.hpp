#pragma once
#include "natives.h"
#include "Globals.hpp"
#include "ScreenUtils.hpp"
#include "Rampage.hpp"
#include "nlohmann/json.hpp"
#include "Utils.hpp"
#include "ScriptEnums.hpp"
#include <fstream>
#include <cstdlib>

namespace Rampage {
	void on_start();
	void on_abort();
};
