#include "pch.h"
#include "Rampage.hpp"

using namespace Rampage;

CurrentRampageData crd;
int checkpoint = 10000;

void Rampage::start_rampage() {
	AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SCRIPT\\RAMPAGE_01", FALSE, -1);
	AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SCRIPT\\RAMPAGE_02", FALSE, -1);
	PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(PLAYER::PLAYER_ID(), FALSE);
	AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", TRUE);
	AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", TRUE);
	Globals::UIFlags::kill_count = 0;
	Globals::UIFlags::time_left = 0;
	checkpoint = 10000;
	crd = CurrentRampageData();
	crd.enemy_peds = {};
	crd.enemy_vehicles = {};
	Ped ppid = PLAYER::PLAYER_PED_ID();
	WEAPON::SET_CAN_PED_EQUIP_ALL_WEAPONS_(ppid, FALSE);

	switch (Globals::RampageData::current_mission.mission_flags) {
	case 1:
	{
		crd.melee_enabled = true;
		break;
	}
	case 1 << 2:
	{
		crd.melee_enabled = true;
		crd.weak_enemies = true;
		break;
	}
	case 2 << 3 << 4:
	{
		crd.weak_enemies = true;
		crd.sniper_enabled = true;
		crd.headshot_only = true;
		break;
	}
	case 3 << 4:
	{
		crd.headshot_only = true;
		crd.sniper_enabled = true;
		break;
	}
	case 3 << 9:
	{
		crd.headshot_only = true;
		crd.rifle_enabled = true;
		break;
	}
	case 3 << 10:
	{
		crd.headshot_only = true;
		crd.shotgun_enabled = true;
		break;
	}
	case 3 << 11:
	{
		crd.headshot_only = true;
		crd.machinegun_enabled = true;
		break;
	}
	case 3 << 4 << 8:
	{
		crd.headshot_only = true;
		crd.sniper_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 3 << 8 << 9:
	{
		crd.headshot_only = true;
		crd.rifle_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 3 << 8 << 10:
	{
		crd.headshot_only = true;
		crd.shotgun_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 3 << 8 << 11:
	{
		crd.headshot_only = true;
		crd.machinegun_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 4 << 8:
	{
		crd.sniper_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 8 << 9:
	{
		crd.ability_disabled = true;
		crd.rifle_enabled = true;
		break;
	}
	case 8 << 10:
	{
		crd.shotgun_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 8 << 11:
	{
		crd.machinegun_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 4 << 5 << 8:
	{
		crd.sniper_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 5 << 8 << 9:
	{
		crd.rifle_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 5 << 8 << 10:
	{
		crd.shotgun_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 5 << 8 << 11:
	{
		crd.machinegun_enabled = true;
		crd.explosives_enabled = true;
		crd.ability_disabled = true;
		break;
	}
	case 5 << 6:
	{
		crd.explosives_enabled = true;
		crd.heavy_enabled = true;
		break;
	}
	case 5 << 9:
	{
		crd.explosives_enabled = true;
		crd.rifle_enabled = true;
		break;
	}
	case 5 << 10:
	{
		crd.explosives_enabled = true;
		crd.shotgun_enabled = true;
		break;
	}
	}

	if (crd.pistol_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponPistol50, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponPistol50, 2500, TRUE, TRUE);
	}

	if (crd.rifle_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponAdvancedRifle, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponAdvancedRifle, 3000, TRUE, TRUE);
	}

	if (crd.shotgun_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponCombatShotgun, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponCombatShotgun, 1000, TRUE, TRUE);
	}

	if (crd.heavy_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponMinigun, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponMinigun, 2000, TRUE, TRUE);
	}

	if (crd.sniper_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponSniperRifle, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponSniperRifle, 200, TRUE, TRUE);
	}

	if (crd.explosives_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponStickyBomb, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponStickyBomb, 10, TRUE, TRUE);
	}

	if (crd.machinegun_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponMicroSMG, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponMicroSMG, 1500, TRUE, TRUE);
	}

	if (crd.melee_enabled) {
		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, eWeapon::WeaponHammer, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, eWeapon::WeaponHammer, 1, TRUE, TRUE);
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

		Blip blip = HUD::GET_BLIP_FROM_ENTITY(ped);
		HUD::REMOVE_BLIP(&blip);
		Entity killer = PED::GET_PED_SOURCE_OF_DEATH(ped);

		if (killer == ppid) {
			bool headshot = killed_by_headshot(ped);

			if (crd.headshot_only && headshot) {
				crd.kills += 1;
				crd.headshot_count += 1;

				if (crd.kills == Globals::RampageData::current_mission.target)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_ROAR_MASTER", 0, true);
				else
					AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_KILLED_HEAD_SHOT_MASTER", 0, true);
			}
			else if (!crd.headshot_only) {
				crd.kills += 1;

				if (crd.kills == Globals::RampageData::current_mission.target)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_ROAR_MASTER", 0, true);
				else if (headshot) {
					AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_KILLED_HEAD_SHOT_MASTER", 0, true);
					crd.headshot_count += 1;
				}
				else
					AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_KILLED_COUNTER_MASTER", 0, true);
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
		if (PLAYER::IS_PLAYER_DEAD(0)) {
			end_rampage(false);
			return;
		}

		if (crd.ability_disabled) {
			//PLAYER::SPECIAL_ABILITY_DEPLETE_(0, 0);
			PAD::DISABLE_CONTROL_ACTION(2, 171, TRUE);
			PAD::DISABLE_CONTROL_ACTION(2, 28, TRUE);
			PAD::DISABLE_CONTROL_ACTION(2, 29, TRUE);
			PAD::DISABLE_CONTROL_ACTION(2, 93, TRUE);
		}

		PAD::DISABLE_CONTROL_ACTION(2, 19, TRUE);
		PLAYER::SET_PLAYER_WANTED_LEVEL(0, 0, FALSE);
		HUD::HIDE_AREA_AND_VEHICLE_NAME_THIS_FRAME_();
		Globals::UIFlags::kill_count = crd.kills;
		Globals::UIFlags::time_left = Globals::RampageData::current_mission.time - (MISC::GET_GAME_TIMER() - crd.start_time);
		
		if (Globals::UIFlags::time_left <= checkpoint) {
			AUDIO::PLAY_SOUND_FRONTEND(-1, "10_SEC_WARNING", "HUD_MINI_GAME_SOUNDSET", true);
			checkpoint -= 1000;
		}

		process_dead();

		if (crd.enemy_peds.size() < 10 && MISC::GET_GAME_TIMER() - crd.last_p_spawn > 1000) {
			size_t index = Utils::ran_int(Globals::RampageData::current_mission.ped_spawnpoints.size() - 1, (size_t)0);
			Vector3 coords = Globals::RampageData::current_mission.ped_spawnpoints.at(index);
			index = Utils::ran_int(Globals::RampageData::current_mission.ped_models.size() - 1, (size_t)0);
			Hash model = Globals::RampageData::current_mission.ped_models.at(index);
			Ped enemy = PED::CREATE_PED(0, model, coords, 0.0f, FALSE, FALSE);
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(enemy, Globals::RampageData::current_mission.relationship_group);
			PED::SET_PED_ARMOUR(enemy, 0);
			PED::SET_PED_ACCURACY(enemy, 7);
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

void Rampage::end_rampage(bool show_scaleform) {
	for (auto& ped : crd.enemy_peds) {
		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
	}

	for (auto& vehicle : crd.enemy_vehicles) {
		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&vehicle);
	}

	PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(PLAYER::PLAYER_ID(), TRUE);
	AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", FALSE);
	AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", FALSE);
	WEAPON::SET_CAN_PED_EQUIP_ALL_WEAPONS_(PLAYER::PLAYER_PED_ID(), TRUE);
	GRAPHICS::ANIMPOSTFX_STOP("Rampage");
	GRAPHICS::ANIMPOSTFX_PLAY("RampageOut", 0, FALSE);
	AUDIO::TRIGGER_MUSIC_EVENT("RAMPAGE_STOP");
	Globals::RampageData::rampage_active = false;

	if (!show_scaleform) {
		AUDIO::PLAY_SOUND_FRONTEND(-1, "TIMER_STOP", "HUD_MINI_GAME_SOUNDSET", true);
		return;
	}

	bool passed = crd.kills >= Globals::RampageData::current_mission.target;

	if (!passed) {
		AUDIO::PLAY_SOUND_FRONTEND(-1, "TIMER_STOP", "HUD_MINI_GAME_SOUNDSET", true);
		if (Globals::UIFlags::scaleform_active)
			Globals::UIFlags::clean = true;

		Globals::UIFlags::scaleform_type = ScaleformTypes::RampageFailed;
		Globals::UIFlags::scaleform_active = true;
		return;
	}

	AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_PASSED_MASTER", 0, true);
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
