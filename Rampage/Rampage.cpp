#include "pch.h"
#include "Rampage.hpp"
#include "Globals.hpp"

using namespace Rampage;

CurrentRampageData crd;

void Rampage::start_rampage() {
	crd = CurrentRampageData();
	crd.remaining_time = Globals::RampageData::current_mission.time;
}
