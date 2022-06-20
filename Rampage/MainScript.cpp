#include "pch.h"
#include "MainScript.hpp"

using namespace Rampage;

std::vector<Blip> mission_blips = {};

void read_rampages_file() {
	nlohmann::json j;
	std::ifstream i("RampageData\\Rampage.json");
	i >> j;
	i.close();
	Globals::mission_data = std::vector<Mission::MissionData>();

	for (auto& item : j.items()) {
		nlohmann::json obj = item.value();
		Mission::MissionData mission = Mission::MissionData();
		std::string str_key = obj.at("mission_hash");
		mission.mission_hash = MISC::GET_HASH_KEY(str_key.c_str());
		mission.name = obj.at("name");
		std::vector<int> extras = obj.at("extra_objectives");
		std::vector<int> flags = obj.at("mission_flags");
		float location_x = obj.at("location_x");
		float location_y = obj.at("location_y");
		float location_z = obj.at("location_z");
		mission.location = Vector3();
		mission.location.x = location_x;
		mission.location.y = location_y;
		mission.location.z = location_z;
		mission.target = obj.at("target");
		mission.multiplier = obj.at("multiplier");
		mission.time = obj.at("time");
		mission.extra_target_1 = obj.at("extra_target_1");
		mission.extra_target_2 = obj.at("extra_target_2");
		mission.extra_target_3 = obj.at("extra_target_3");
		std::string relationship_group = obj.at("relationship_group");
		mission.relationship_group = MISC::GET_HASH_KEY(relationship_group.c_str());
		std::vector<std::string> ped_models = obj.at("ped_models");
		std::vector<std::string> vehicle_models = obj.at("vehicle_models");

		if (vehicle_models.empty()) {
			mission.vehicle_models = {
				0xD0EB2BE5,
				0xCFCFEB3B,
				0x1F3766E3
			};
		}
		else {
			mission.vehicle_models = {};

			for (const auto& str_key : vehicle_models) {
				mission.vehicle_models.push_back(MISC::GET_HASH_KEY(str_key.c_str()));
			}
		}

		if (ped_models.empty()) {
			mission.ped_models = {
				0xF42EE883,
				0x231AF63F,
				0x23B88069
			};
		}
		else {
			mission.ped_models = {};

			for (const auto& str_key : ped_models) {
				mission.ped_models.push_back(MISC::GET_HASH_KEY(str_key.c_str()));
			}
		}

		if (extras.empty())
			mission.extra_objectives = 0;
		else {
			for (size_t i = 0; i < extras.size(); i++) {
				if (extras.at(i) == 0) {
					mission.extra_objectives = 0;
					break;
				}

				if (i == 0)
					mission.extra_objectives = extras.at(i);
				else
					mission.extra_objectives = mission.extra_objectives << extras.at(i);
			}
		}

		if (flags.empty())
			mission.mission_flags = 0;
		else {
			for (size_t i = 0; i < flags.size(); i++) {
				if (flags.at(i) == 0) {
					mission.mission_flags = 0;
					break;
				}

				if (i == 0)
					mission.mission_flags = flags.at(i);
				else
					mission.mission_flags = mission.mission_flags << flags.at(i);
			}
		}

		mission.ped_spawnpoints = {};
		mission.vehicle_spawnpoints = {};

		for (auto& coords : obj.at("ped_spawnpoints").items()) {
			nlohmann::json coordsObj = coords.value();
			Vector3 vec = Vector3();
			vec.x = coordsObj.at("x");
			vec.y = coordsObj.at("y");
			vec.z = coordsObj.at("z");
			mission.ped_spawnpoints.push_back(vec);
		}

		for (auto& coords : obj.at("vehicle_spawnpoints").items()) {
			nlohmann::json coordsObj = coords.value();
			Vector3 vec = Vector3();
			vec.x = coordsObj.at("x");
			vec.y = coordsObj.at("y");
			vec.z = coordsObj.at("z");
			mission.vehicle_spawnpoints.push_back(vec);
		}

		Globals::mission_data.push_back(mission);
	}
}

void main() {
	read_rampages_file();

	for (const auto& mission : Globals::mission_data)
		mission_blips.push_back(UI::create_blip(mission.location.x, mission.location.y, mission.location.z, eBlipSprite::BlipSpriteRampage, eBlipColor::BlipColorRed, mission.name.c_str()));

	for (;;) {
		if (!Globals::RampageData::rampage_active) {
			Hash rampage_hash = Utils::is_player_in_start_range();

			if (rampage_hash != 0) {
				UI::show_help_text("Press ~INPUT_CONTEXT~ to start the rampage.", 0);

				if (PAD::IS_CONTROL_JUST_PRESSED(0, 51))
				{
					Globals::UIFlags::scaleform_type = ScaleformTypes::RampageStarted;

					if (Globals::UIFlags::scaleform_active)
						Globals::UIFlags::clean = true;
					else
						Globals::UIFlags::scaleform_active = true;

					GRAPHICS::ANIMPOSTFX_PLAY("Rampage", 0, TRUE);
					AUDIO::TRIGGER_MUSIC_EVENT("RAMPAGE_5_START");
					AUDIO::TRIGGER_MUSIC_EVENT("RAMPAGE_5_OS");

					for (auto& rampage : Globals::mission_data) {
						if (rampage.mission_hash == rampage_hash) {
							Globals::RampageData::current_mission = rampage;
							break;
						}
					}

					start_rampage();
					Globals::RampageData::rampage_active = true;
				}
			}
		}
		else
			process_rampage();

		WAIT(0);
	}
}

void Rampage::on_start() {
	std::srand(GetTickCount64());
	main();
}

void Rampage::on_abort() {
	for (auto blip : mission_blips) {
		if (HUD::DOES_BLIP_EXIST(blip))
			HUD::REMOVE_BLIP(&blip);
	}

	mission_blips.clear();

	if (Globals::RampageData::rampage_active)
		end_rampage(false);
}