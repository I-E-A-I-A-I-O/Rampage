#include "pch.h"
#include "Rampage.hpp"

using namespace Rampage;

CurrentRampageData crd;

void Rampage::start_rampage() {
	crd = CurrentRampageData();
	crd.enemy_peds = {};
	crd.enemy_vehicles = {};
	Ped ppid = PLAYER::PLAYER_PED_ID();
	WEAPON::SET_CAN_PED_EQUIP_ALL_WEAPONS_(ppid, FALSE);

	switch (Globals::RampageData::current_mission.mission_flags) {
	case 1:
		crd.melee_enabled = true;
		break;
	case 1 << 2:
		crd.melee_enabled = true;
		crd.weak_enemies = true;
		break;
	case 2 << 3 << 4:
		crd.weak_enemies = true;
		crd.sniper_enabled = true;
		crd.headshot_only = true;
		break;
	case 3 << 4:
		crd.headshot_only = true;
		crd.sniper_enabled = true;
		break;
	case 3 << 9:
		crd.headshot_only = true;
		crd.rifle_enabled = true;
		break;
	case 3 << 10:
		crd.headshot_only = true;
		crd.shotgun_enabled = true;
		break;
	case 3 << 11:
		crd.headshot_only = true;
		crd.machinegun_enabled = true;
		break;
	case 3 << 4 << 8:
		crd.headshot_only = true;
		crd.sniper_enabled = true;
		crd.ability_disabled = true;
		break;
	case 3 << 9 << 8:
		crd.headshot_only = true;
		crd.rifle_enabled = true;
		crd.ability_disabled = true;
		break;
	case 3 << 10 << 8:
		crd.headshot_only = true;
		crd.shotgun_enabled = true;
		crd.ability_disabled = true;
		break;
	case 3 << 11 << 8:
		crd.headshot_only = true;
		crd.shotgun_enabled = true;
		crd.ability_disabled = true;
		break;
	case 4 << 8:
		crd.sniper_enabled = true;
		crd.ability_disabled = true;
		break;
	case 8 << 9:
		crd.ability_disabled = true;
		crd.rifle_enabled = true;
		break;
	case 8 << 10:
		crd.shotgun_enabled = true;
		crd.ability_disabled = true;
		break;
	case 8 << 11:
		crd.machinegun_enabled = true;
		crd.ability_disabled = true;
		break;
	case 4 << 5 << 8:
		crd.sniper_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	case 5 << 8 << 9:
		crd.rifle_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	case 5 << 8 << 10:
		crd.shotgun_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	case 5 << 8 << 11:
		crd.machinegun_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	case 5 << 6:
		crd.explosives_enabled = true;
		crd.heavy_enabled = true;
		break;
	case 5 << 9:
		crd.explosives_enabled = true;
		crd.rifle_enabled = true;
		break;
	case 5 << 10:
		crd.explosives_enabled = true;
		crd.shotgun_enabled = true;
		break;
	}

	if (crd.pistol_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponPistol50, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponPistol50, 2500, FALSE, TRUE);
	}

	if (crd.rifle_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponAssaultRifle, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponAssaultRifle, 3000, FALSE, TRUE);
	}

	if (crd.shotgun_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponPumpShotgun, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponPumpShotgun, 1000, FALSE, TRUE);
	}

	if (crd.heavy_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponMinigun, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponMinigun, 2000, FALSE, TRUE);
	}

	if (crd.sniper_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponHeavySniper, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponHeavySniper, 200, FALSE, TRUE);
	}

	if (crd.explosives_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponStickyBomb, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponStickyBomb, 10, FALSE, TRUE);
	}

	if (crd.machinegun_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponMicroSMG, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponMicroSMG, 1500, FALSE, TRUE);
	}

	if (crd.melee_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponHammer, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponHammer, 1, FALSE, TRUE);
	}

	crd.start_time = MISC::GET_GAME_TIMER();

	for (auto model : Globals::RampageData::current_mission.ped_models) {
		STREAMING::REQUEST_MODEL(model);

		while (!STREAMING::HAS_MODEL_LOADED(model))
			WAIT(0);
	}

	for (auto model : Globals::RampageData::current_mission.vehicle_models) {
		STREAMING::REQUEST_MODEL(model);

		while (!STREAMING::HAS_MODEL_LOADED(model))
			WAIT(0);
	}

	switch (Globals::RampageData::current_mission.extra_objectives) {
	case 1:
		crd.extra_kills = true;
		break;
	case 2:
		crd.extra_headshots = true;
		break;
	case 3:
		crd.extra_vehicles = true;
		break;
	case 1 << 2:
		crd.extra_kills = true;
		crd.extra_headshots = true;
		break;
	case 1 << 3:
		crd.extra_kills = true;
		crd.extra_vehicles = true;
		break;
	case 2 << 3:
		crd.extra_headshots = true;
		crd.extra_vehicles = true;
		break;
	}

	if (crd.headshot_only)
		UI::show_subtitle(std::string("Headshot ").append(std::to_string(Globals::RampageData::current_mission.target)).append(" ~r~enemies.").c_str(), 30000);
	else
		UI::show_subtitle(std::string("Kill ").append(std::to_string(Globals::RampageData::current_mission.target)).append(" ~r~enemies.").c_str(), 30000);
}

bool killed_by_headshot(Ped ped) {
	int lastDamagedBone;
	PED::GET_PED_LAST_DAMAGE_BONE(ped, &lastDamagedBone);
	return lastDamagedBone == eBone::SKEL_Head;
}

void process_dead() {
	Ped ppid = PLAYER::PLAYER_PED_ID();

	for (size_t i = 0; i < crd.enemy_peds.size(); i++) {
		Ped ped = crd.enemy_peds.at(i);

		if (!ENTITY::IS_ENTITY_DEAD(ped, FALSE))
			continue;

		Entity killer = PED::GET_PED_SOURCE_OF_DEATH(ped);

		if (killer == ppid) {
			bool headshot = killed_by_headshot(ped);

			if (crd.headshot_only && headshot) {
				crd.kills += 1;
				crd.headshot_count += 1;
			}
			else if (!crd.headshot_only) {
				crd.kills += 1;

				if (headshot)
					crd.headshot_count += 1;
			}
		}

		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
		crd.enemy_peds.erase(crd.enemy_peds.begin() + i);
	}

	for (size_t i = 0; i < crd.enemy_vehicles.size(); i++) {
		Vehicle vehicle = crd.enemy_vehicles.at(i);

		if (!ENTITY::IS_ENTITY_DEAD(vehicle, FALSE))
			continue;

		crd.vehicle_kills += 1;
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);
		crd.enemy_vehicles.erase(crd.enemy_vehicles.begin() + i);
	}
}

void Rampage::process_rampage() {
	if (MISC::GET_GAME_TIMER() - crd.start_time < Globals::RampageData::current_mission.time) {
		UI::show_subtitle(std::string("time: ").append(std::to_string(MISC::GET_GAME_TIMER() - crd.start_time)).c_str(), 1000);
		process_dead();

		if (crd.enemy_peds.size() < 10 && MISC::GET_GAME_TIMER() - crd.last_p_spawn > 1000) {
			size_t index = Utils::ran_int(Globals::RampageData::current_mission.ped_spawnpoints.size() - 1, (size_t)0);
			Vector3 coords = Globals::RampageData::current_mission.ped_spawnpoints.at(index);
			size_t index = Utils::ran_int(Globals::RampageData::current_mission.ped_models.size() - 1, (size_t)0);
			Hash model = Globals::RampageData::current_mission.ped_models.at(index);
			Ped enemy = PED::CREATE_PED(0, model, coords, 0.0f, FALSE, FALSE);
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(enemy, Globals::RampageData::current_mission.relationship_group);
			PED::SET_PED_ARMOUR(enemy, 0);
			PED::SET_PED_ACCURACY(enemy, 10);
			int ran_loadout = Utils::ran_int(100, 1);

			if (ran_loadout <= 50)
				WEAPON::GIVE_LOADOUT_TO_PED_(enemy, MISC::GET_HASH_KEY("LOADOUT_LOST_L2"));
			else
				WEAPON::GIVE_LOADOUT_TO_PED_(enemy, MISC::GET_HASH_KEY("LOADOUT_COP_SHOTGUN"));

			PED::SET_PED_CONFIG_FLAG(enemy, 281, TRUE);
			TASK::TASK_COMBAT_PED(enemy, PLAYER::PLAYER_PED_ID(), 0, 16);
			UI::create_blip_for_enemy(enemy);
			PED::SET_PED_COMBAT_MOVEMENT(enemy, 2);

			if (crd.weak_enemies)
			{
				int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(enemy);
				ENTITY::SET_ENTITY_HEALTH(enemy, max_health - (max_health * 0.8f), 0);
			}

			crd.enemy_peds.push_back(enemy);
			crd.last_p_spawn = MISC::GET_GAME_TIMER();
		}
	}
	else
		end_rampage(true);
}

void Rampage::end_rampage(bool showScaleform) {
	WEAPON::SET_CAN_PED_EQUIP_ALL_WEAPONS_(PLAYER::PLAYER_PED_ID(), TRUE);
	GRAPHICS::ANIMPOSTFX_STOP("Rampage");
	GRAPHICS::ANIMPOSTFX_PLAY("RampageOut", 0, FALSE);
	AUDIO::TRIGGER_MUSIC_EVENT("RAMPAGE_STOP");
	Globals::RampageData::rampage_active = false;

	if (!showScaleform)
		return;

	bool passed = crd.kills >= Globals::RampageData::current_mission.target;

	if (!passed) {
		Globals::UIFlags::scaleform_type = ScaleformTypes::RampageFailed;
		Globals::UIFlags::scaleform_active = true;
		return;
	}

	std::map<std::string, Globals::ScaleformObjective> extras = {};

	if (crd.extra_kills) {
		std::string title = std::string("Kill ").append(std::to_string(Globals::RampageData::current_mission.extra_target_1).append(" enemies").c_str());
		Globals::ScaleformObjective objective = Globals::ScaleformObjective();
		objective.value = crd.kills;
		objective.passed = crd.kills >= Globals::RampageData::current_mission.extra_target_1;
		extras.insert(std::make_pair(title, objective));
	}

	if (crd.extra_headshots) {
		std::string title = std::string("Get ").append(std::to_string(Globals::RampageData::current_mission.extra_target_2).append(" headshots").c_str());
		Globals::ScaleformObjective objective = Globals::ScaleformObjective();
		objective.value = crd.headshot_count;
		objective.passed = crd.headshot_count >= Globals::RampageData::current_mission.extra_target_2;
		extras.insert(std::make_pair(title, objective));
	}

	if (crd.extra_vehicles) {
		std::string title = std::string("Destroy ").append(std::to_string(Globals::RampageData::current_mission.extra_target_3).append(" vehicles").c_str());
		Globals::ScaleformObjective objective = Globals::ScaleformObjective();
		objective.value = crd.vehicle_kills;
		objective.passed = crd.vehicle_kills >= Globals::RampageData::current_mission.extra_target_3;
		extras.insert(std::make_pair(title, objective));
	}

	Globals::UIFlags::extraObjectives = extras;
	Globals::UIFlags::scaleform_type = ScaleformTypes::PassedWithObjectives;
	Globals::UIFlags::scaleform_active = true;
}
