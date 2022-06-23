#include "pch.h"
#include "MainScript.hpp"

using namespace Rampage;

bool sound = true;

void create_blips() {
	for (auto& mission : Globals::mission_data)
		mission.blip = UI::create_blip(mission.location.x, mission.location.y, mission.location.z, eBlipSprite::BlipSpriteRampage, eBlipColor::BlipColorRed, mission.name.c_str());
}

void rampage_blip_watch() {
	for (auto& mission : Globals::mission_data) {
		if (Globals::RampageData::rampage_active)
			continue;

		if (mission.blip == 0 && MISC::GET_GAME_TIMER() - mission.last_played > 300000) {
			mission.blip = UI::create_blip(mission.location.x, mission.location.y, mission.location.z, eBlipSprite::BlipSpriteRampage, eBlipColor::BlipColorRed, mission.name.c_str());
		}
	}
}

void delete_blips() {
	for (auto& mission : Globals::mission_data) {
		if (mission.blip != 0 && HUD::DOES_BLIP_EXIST(mission.blip)) {
			HUD::REMOVE_BLIP(&mission.blip);
			mission.blip = 0;
		}
			
	}
}

void read_config_file() {
	nlohmann::json j;
	std::ifstream i("RampageData\\config.json");
	i >> j;
	i.close();
	Globals::ScriptConfig::rampage_effect_disabled = j.at("disableRampageEffect");
	Globals::ScriptConfig::start_rampage_key = j.at("startRampageKey");
}

void read_rampages_file() {
	nlohmann::json j;
	std::ifstream i("RampageData\\Rampage.json");
	i >> j;
	i.close();
	delete_blips();
	Globals::mission_data = std::vector<Mission::MissionData>();

	for (auto& item : j.items()) {
		nlohmann::json obj = item.value();
		Mission::MissionData mission = Mission::MissionData();
		mission.melee_override = 0;
		mission.pistol_override = 0;
		mission.shotgun_override = 0;
		mission.machinegun_override = 0;
		mission.rifle_override = 0;
		mission.heavy_override = 0;
		mission.sniper_override = 0;
		mission.explosive_override = 0;
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

		if (obj.find("melee_override") != obj.end()) {
			std::string weapon_name = obj.at("melee_override");
			mission.melee_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("pistol_override") != obj.end()) {
			std::string weapon_name = obj.at("pistol_override");
			mission.pistol_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("machinegun_override") != obj.end()) {
			std::string weapon_name = obj.at("machinegun_override");
			mission.machinegun_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("shotgun_override") != obj.end()) {
			std::string weapon_name = obj.at("shotgun_override");
			mission.shotgun_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("rifle_override") != obj.end()) {
			std::string weapon_name = obj.at("rifle_override");
			mission.rifle_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("sniper_override") != obj.end()) {
			std::string weapon_name = obj.at("sniper_override");
			mission.sniper_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("heavy_override") != obj.end()) {
			std::string weapon_name = obj.at("heavy_override");
			mission.heavy_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("explosive_override") != obj.end()) {
			std::string weapon_name = obj.at("explosive_override");
			mission.explosive_override = MISC::GET_HASH_KEY(weapon_name.c_str());
		}

		if (obj.find("vehicle_restriction") != obj.end()) {
			int vehicle_restriction = obj.at("vehicle_restriction");
			
			if (vehicle_restriction != -1 && vehicle_restriction != 0 && vehicle_restriction != 1)
				vehicle_restriction = -1;

			mission.vehicle_restriction = vehicle_restriction;
		}
		else {
			mission.vehicle_restriction = -1;
		}

		Globals::mission_data.push_back(mission);
	}
}

void main() {
	read_config_file();
	read_rampages_file();
	create_blips();

	for (;;) {
		if (!Globals::RampageData::rampage_active) {
			if (MISC::HAS_CHEAT_STRING_JUST_BEEN_ENTERED_(MISC::GET_HASH_KEY("RAMPAGE_READ_DATA"))) {
				read_rampages_file();
			}

			if (MISC::HAS_CHEAT_STRING_JUST_BEEN_ENTERED_(MISC::GET_HASH_KEY("RAMPAGE_READ_CONFIG"))) {
				read_config_file();
			}

			rampage_blip_watch();
			Hash rampage_hash = Utils::is_player_in_start_range();

			if (rampage_hash != 0) {
				UI::show_help_text(std::string("Press ~").append(controlsNames.at(Globals::ScriptConfig::start_rampage_key)).append("~ to start the rampage.").c_str(), sound);

				if (sound)
					sound = false;

				if (PAD::IS_CONTROL_JUST_PRESSED(0, Globals::ScriptConfig::start_rampage_key))
				{
					delete_blips();
					Globals::UIFlags::scaleform_type = ScaleformTypes::RampageStarted;

					if (Globals::UIFlags::scaleform_active)
						Globals::UIFlags::clean = true;
					else
						Globals::UIFlags::scaleform_active = true;

					TASK::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "missrampageintrooutro", "trvram_6_1h_intro", 8, -8, -1, 1, 0, 0, 0, 0);

					if (!Globals::ScriptConfig::rampage_effect_disabled)
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
			else if (!sound)
				sound = true;
		}
		else if (!process_rampage()) {
			for (auto& mission : Globals::mission_data) {
				if (mission.mission_hash != Globals::RampageData::current_mission.mission_hash)
					continue;

				mission.last_played = MISC::GET_GAME_TIMER();
			}
		}
			

		WAIT(0);
	}
}

void Rampage::on_start() {
	std::srand(GetTickCount64());
	main();
}

void Rampage::on_abort() {
	delete_blips();

	if (Globals::RampageData::rampage_active)
		end_rampage(false);
}