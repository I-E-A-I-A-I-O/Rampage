#include "pch.h"
#include "Globals.hpp"

using namespace Rampage;

bool Globals::UIFlags::scaleform_active;
bool Globals::UIFlags::clean;
int Globals::UIFlags::time_left;
int Globals::UIFlags::kill_count;
std::map<std::string, Globals::ScaleformObjective> Globals::UIFlags::extraObjectives;
ScaleformTypes Globals::UIFlags::scaleform_type;
std::vector<Mission::MissionData> Globals::mission_data;
bool Globals::RampageData::rampage_active;
Mission::MissionData Globals::RampageData::current_mission;
bool Globals::ScriptConfig::rampage_effect_disabled;
int Globals::ScriptConfig::start_rampage_key;
int Globals::ScriptConfig::detonate_key;
