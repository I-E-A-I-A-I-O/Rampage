#include "pch.h"
#include "Globals.hpp"

using namespace Rampage;

bool Globals::UIFlags::scaleform_active;
bool Globals::UIFlags::clean;
std::map<std::string, Globals::ScaleformObjective> Globals::UIFlags::extraObjectives;
ScaleformTypes Globals::UIFlags::scaleform_type;
std::vector<Mission::MissionData> Globals::mission_data;
bool Globals::RampageData::rampage_active;
Mission::MissionData Globals::RampageData::current_mission;
