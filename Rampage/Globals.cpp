#include "pch.h"
#include "Globals.hpp"

using namespace Rampage;

bool Globals::UIFlags::scaleform_active;
bool Globals::UIFlags::clean;
ScaleformTypes Globals::UIFlags::scaleform_type;
std::vector<Mission::MissionData> Globals::mission_data;
bool Globals::RampageData::rampage_active;
Mission::MissionData Globals::RampageData::current_mission;
