#include "pch.h"
#include "Rampage.hpp"

using namespace Rampage;

CurrentRampageData crd;
int checkpoint = 10000;
int vehicle_delay = 20000;
int foot_limit = 10;

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
	case 2 << 5:
	{
		crd.explosives_enabled = true;
		crd.weak_enemies = true;
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
	case 8 << 13:
	{
		crd.ability_disabled = true;
		crd.machinegun_enabled = true;
		crd.vehicle_only = true;
		crd.weak_enemies = true;
		break;
	}
	case 13: 
	{
		crd.machinegun_enabled = true;
		crd.vehicle_only = true;
		crd.weak_enemies = true;
		break;
	}
	case 8 << 14:
	{
		crd.heavy_enabled = true;
		crd.ability_disabled = true;
		crd.only_enemy_vehicles = true;
		break;
	}
	case 14:
	{
		crd.only_enemy_vehicles = true;
		crd.heavy_enabled = true;
		break;
	}
	default: 
	{
		crd.shotgun_enabled = true;
		crd.explosives_enabled = true;
		break;
	}
	}

	if (crd.explosives_enabled) {
		Hash weapon = eWeapon::WeaponStickyBomb;

		if (Globals::RampageData::current_mission.explosive_override != 0)
			weapon = Globals::RampageData::current_mission.explosive_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 25, TRUE, TRUE);
	}

	if (crd.heavy_enabled) {
		Hash weapon = eWeapon::WeaponMinigun;

		if (Globals::RampageData::current_mission.heavy_override != 0)
			weapon = Globals::RampageData::current_mission.heavy_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 5000, TRUE, TRUE);
	}

	if (crd.pistol_enabled) {
		Hash weapon = eWeapon::WeaponPistol50;

		if (Globals::RampageData::current_mission.pistol_override != 0)
			weapon = Globals::RampageData::current_mission.pistol_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 1000, TRUE, TRUE);
	}

	if (crd.rifle_enabled) {
		Hash weapon = eWeapon::WeaponAdvancedRifle;

		if (Globals::RampageData::current_mission.rifle_override != 0)
			weapon = Globals::RampageData::current_mission.rifle_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 3000, TRUE, TRUE);
	}

	if (crd.shotgun_enabled) {
		Hash weapon = eWeapon::WeaponCombatShotgun;

		if (Globals::RampageData::current_mission.shotgun_override != 0)
			weapon = Globals::RampageData::current_mission.shotgun_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 300, TRUE, TRUE);
	}

	if (crd.sniper_enabled) {
		Hash weapon = eWeapon::WeaponSniperRifle;

		if (Globals::RampageData::current_mission.sniper_override != 0)
			weapon = Globals::RampageData::current_mission.sniper_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 150, TRUE, TRUE);
	}

	if (crd.machinegun_enabled) {
		Hash weapon = eWeapon::WeaponMicroSMG;

		if (Globals::RampageData::current_mission.machinegun_override != 0)
			weapon = Globals::RampageData::current_mission.machinegun_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 2000, TRUE, TRUE);
	}

	if (crd.melee_enabled) {
		Hash weapon = eWeapon::WeaponHammer;

		if (Globals::RampageData::current_mission.melee_override != 0)
			weapon = Globals::RampageData::current_mission.melee_override;

		WEAPON::SET_CAN_PED_EQUIP_WEAPON_(ppid, weapon, TRUE);
		WEAPON::GIVE_WEAPON_TO_PED(ppid, weapon, 1, TRUE, TRUE);
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
	case 1 << 2 << 3:
		crd.extra_headshots = true;
		crd.extra_vehicles = true;
		crd.extra_kills = true;
		break;
	}

	if (crd.headshot_only)
		UI::show_subtitle(std::string("Headshot ").append(std::to_string(Globals::RampageData::current_mission.target)).append(" ~r~enemies.").c_str(), 30000);
	else if (crd.vehicle_only)
		UI::show_subtitle(std::string("Drive-By ").append(std::to_string(Globals::RampageData::current_mission.target)).append(" ~r~enemies.").c_str(), 30000);
	else
		UI::show_subtitle(std::string("Kill ").append(std::to_string(Globals::RampageData::current_mission.target)).append(" ~r~enemies.").c_str(), 30000);

	vehicle_delay = crd.only_enemy_vehicles ? 6000 : 20000;
	foot_limit = crd.vehicle_only ? 20 : 10;
	crd.last_p_spawn = MISC::GET_GAME_TIMER();
	crd.last_v_spawn = MISC::GET_GAME_TIMER();
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

		if (!crd.vehicle_only || (crd.vehicle_only && PED::IS_PED_IN_ANY_VEHICLE(ppid, FALSE))) {
			Entity killer = PED::GET_PED_SOURCE_OF_DEATH(ped);

			if (killer == ppid || killer == 0) {
				bool headshot = killed_by_headshot(ped);

				if (crd.headshot_only && headshot) {
					crd.kills += 1;
					crd.headshot_count += 1;

					if (crd.kills == Globals::RampageData::current_mission.target)
						AUDIO::TRIGGER_MUSIC_EVENT("RAMPAGE_5_OS");
					else
						AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_KILLED_HEAD_SHOT_MASTER", 0, true);
				}
				else if (!crd.headshot_only) {
					crd.kills += 1;

					if (crd.kills == Globals::RampageData::current_mission.target)
						AUDIO::TRIGGER_MUSIC_EVENT("RAMPAGE_5_OS");
					else if (headshot) {
						AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_KILLED_HEAD_SHOT_MASTER", 0, true);
						crd.headshot_count += 1;
					}
					else
						AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_KILLED_COUNTER_MASTER", 0, true);
				}
			}
		}

		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
		crd.enemy_peds.erase(crd.enemy_peds.begin() + i);
	}

	for (size_t i = 0; i < crd.enemy_vehicles.size(); i++) {
		Vehicle vehicle = crd.enemy_vehicles.at(i);

		if (!ENTITY::IS_ENTITY_DEAD(vehicle, FALSE))
			continue;

		AUDIO::PLAY_SOUND_FRONTEND(-1, "RAMPAGE_ROAR_MASTER", 0, true);
		Blip blip = HUD::GET_BLIP_FROM_ENTITY(vehicle);
		HUD::REMOVE_BLIP(&blip);
		crd.vehicle_kills += 1;
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);
		crd.enemy_vehicles.erase(crd.enemy_vehicles.begin() + i);
	}
}

void set_ped_config(Ped enemy) {
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(enemy, Globals::RampageData::current_mission.relationship_group);
	PED::SET_PED_ARMOUR(enemy, 0);
	PED::SET_PED_ACCURACY(enemy, 6);
	UI::create_blip_for_enemy(enemy);
	PED::SET_PED_COMBAT_MOVEMENT(enemy, 2);
	PED::SET_PED_CONFIG_FLAG(enemy, 281, TRUE);
	int ran_loadout = Utils::ran_int(100, 1);

	if (!crd.melee_enabled) {
		if (ran_loadout <= 50)
			WEAPON::GIVE_LOADOUT_TO_PED_(enemy, MISC::GET_HASH_KEY("LOADOUT_LOST_L2"));
		else
			WEAPON::GIVE_LOADOUT_TO_PED_(enemy, MISC::GET_HASH_KEY("LOADOUT_COP_SHOTGUN"));

		TASK::TASK_COMBAT_PED(enemy, PLAYER::PLAYER_PED_ID(), 0, 16);
	}
	else {
		if (ran_loadout <= 50)
		{
			WEAPON::GIVE_WEAPON_TO_PED(enemy, eWeapon::WeaponBat, 1, TRUE, TRUE);
			TASK::TASK_PUT_PED_DIRECTLY_INTO_MELEE(enemy, PLAYER::PLAYER_PED_ID(), 0, -1, 0, 0);
		}
		else if (ran_loadout <= 75)
		{
			WEAPON::GIVE_WEAPON_TO_PED(enemy, eWeapon::WeaponKnife, 1, TRUE, TRUE);
			TASK::TASK_PUT_PED_DIRECTLY_INTO_MELEE(enemy, PLAYER::PLAYER_PED_ID(), 0, -1, 0, 0);
		}
		else {
			WEAPON::GIVE_WEAPON_TO_PED(enemy, eWeapon::WeaponPistol, 200, TRUE, TRUE);
			TASK::TASK_COMBAT_PED(enemy, PLAYER::PLAYER_PED_ID(), 0, 16);
		}
	}

	if (crd.weak_enemies)
	{
		int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(enemy);
		ENTITY::SET_ENTITY_HEALTH(enemy, max_health - (max_health * 0.35f), 0);
	}
}

void set_ped_config(Ped enemy, bool passenger) {
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(enemy, Globals::RampageData::current_mission.relationship_group);
	PED::SET_PED_ARMOUR(enemy, 0);
	PED::SET_PED_ACCURACY(enemy, 7);
	UI::create_blip_for_enemy(enemy);
	PED::SET_PED_COMBAT_MOVEMENT(enemy, 2);
	PED::SET_PED_CONFIG_FLAG(enemy, 281, TRUE);
	int ran_loadout = Utils::ran_int(100, 1);

	if (!crd.melee_enabled) {
		if (ran_loadout <= 50)
			WEAPON::GIVE_LOADOUT_TO_PED_(enemy, MISC::GET_HASH_KEY("LOADOUT_LOST_L2"));
		else
			WEAPON::GIVE_LOADOUT_TO_PED_(enemy, MISC::GET_HASH_KEY("LOADOUT_COP_SHOTGUN"));

		if (passenger)
			TASK::TASK_VEHICLE_SHOOT_AT_PED(enemy, PLAYER::PLAYER_PED_ID(), 40.0f);
		else
			TASK::TASK_COMBAT_PED(enemy, PLAYER::PLAYER_PED_ID(), 0, 16);
	}
	else {
		if (ran_loadout <= 50)
		{
			WEAPON::GIVE_WEAPON_TO_PED(enemy, eWeapon::WeaponBat, 1, TRUE, TRUE);
			TASK::TASK_PUT_PED_DIRECTLY_INTO_MELEE(enemy, PLAYER::PLAYER_PED_ID(), 0, -1, 0, 0);
		}
		else if (ran_loadout <= 75)
		{
			WEAPON::GIVE_WEAPON_TO_PED(enemy, eWeapon::WeaponKnife, 1, TRUE, TRUE);
			TASK::TASK_PUT_PED_DIRECTLY_INTO_MELEE(enemy, PLAYER::PLAYER_PED_ID(), 0, -1, 0, 0);
		}
		else {
			WEAPON::GIVE_WEAPON_TO_PED(enemy, eWeapon::WeaponPistol, 200, TRUE, TRUE);

			if (passenger)
				TASK::TASK_VEHICLE_SHOOT_AT_PED(enemy, PLAYER::PLAYER_PED_ID(), 40.0f);
			else
				TASK::TASK_COMBAT_PED(enemy, PLAYER::PLAYER_PED_ID(), 0, 16);
		}
	}

	if (crd.weak_enemies)
	{
		int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(enemy);
		ENTITY::SET_ENTITY_HEALTH(enemy, max_health - (max_health * 0.35f), 0);
	}
}

bool Rampage::process_rampage() {
	if (MISC::GET_GAME_TIMER() - crd.start_time < Globals::RampageData::current_mission.time) {
		if (PLAYER::IS_PLAYER_DEAD(0)) {
			end_rampage(false);
			return false;
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

		if (crd.enemy_peds.size() < foot_limit) {
			if (!crd.only_enemy_vehicles) {
				if (MISC::GET_GAME_TIMER() - crd.last_p_spawn > 1500) {
					Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), FALSE);
					size_t index = Utils::ran_int(Globals::RampageData::current_mission.ped_spawnpoints.size() - 1, (size_t)0);
					Vector3 coords = Globals::RampageData::current_mission.ped_spawnpoints.at(index);

					while (Utils::is_in_range(player_coords, coords, 16.0f) && Globals::RampageData::current_mission.ped_spawnpoints.size() > 1)
					{
						index = Utils::ran_int(Globals::RampageData::current_mission.ped_spawnpoints.size() - 1, (size_t)0);
						coords = Globals::RampageData::current_mission.ped_spawnpoints.at(index);
					}

					index = Utils::ran_int(Globals::RampageData::current_mission.ped_models.size() - 1, (size_t)0);
					Hash model = Globals::RampageData::current_mission.ped_models.at(index);
					Ped enemy = PED::CREATE_PED(0, model, coords, 0.0f, FALSE, FALSE);
					set_ped_config(enemy);
					crd.enemy_peds.push_back(enemy);
					crd.last_p_spawn = MISC::GET_GAME_TIMER();
				}
			}
			
			if (!crd.vehicle_only) {
				if (Globals::RampageData::current_mission.vehicle_spawnpoints.size() > 0 && MISC::GET_GAME_TIMER() - crd.last_v_spawn > vehicle_delay) {
					Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), FALSE);
					size_t index = Utils::ran_int(Globals::RampageData::current_mission.vehicle_spawnpoints.size() - 1, (size_t)0);
					Vector3 coords = Globals::RampageData::current_mission.vehicle_spawnpoints.at(index);

					while (Utils::is_in_range(player_coords, coords, 16.0f) && Globals::RampageData::current_mission.vehicle_spawnpoints.size() > 1)
					{
						index = Utils::ran_int(Globals::RampageData::current_mission.vehicle_spawnpoints.size() - 1, (size_t)0);
						coords = Globals::RampageData::current_mission.vehicle_spawnpoints.at(index);
					}

					index = Utils::ran_int(Globals::RampageData::current_mission.vehicle_models.size() - 1, (size_t)0);
					Hash model = Globals::RampageData::current_mission.vehicle_models.at(index);
					Vehicle vehicle = VEHICLE::CREATE_VEHICLE(model, coords, 0.0f, FALSE, FALSE, FALSE);
					int seats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(model);

					for (int i = -1; i < seats; i++) {
						index = Utils::ran_int(Globals::RampageData::current_mission.ped_models.size() - 1, (size_t)0);
						Hash pmodel = Globals::RampageData::current_mission.ped_models.at(index);
						Ped enemy = PED::CREATE_PED_INSIDE_VEHICLE(vehicle, 0, pmodel, i, FALSE, FALSE);
						set_ped_config(enemy, i != -1);
						crd.enemy_peds.push_back(enemy);
					}

					UI::create_blip_for_enemy_vehicle(vehicle);
					crd.enemy_vehicles.push_back(vehicle);
					crd.last_v_spawn = MISC::GET_GAME_TIMER();
				}
			}
		}

		return true;
	}
	else {
		end_rampage(true);
		return false;
	}
}

void Rampage::end_rampage(bool show_scaleform) {
	for (auto& ped : crd.enemy_peds) {
		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
	}

	for (auto& vehicle : crd.enemy_vehicles) {
		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&vehicle);
	}

	for (auto model : Globals::RampageData::current_mission.ped_models) {
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}

	for (auto model : Globals::RampageData::current_mission.vehicle_models) {
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}

	PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(PLAYER::PLAYER_ID(), TRUE);
	AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", FALSE);
	AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", FALSE);
	WEAPON::SET_CAN_PED_EQUIP_ALL_WEAPONS_(PLAYER::PLAYER_PED_ID(), TRUE);

	if (!Globals::ScriptConfig::rampage_effect_disabled) {
		GRAPHICS::ANIMPOSTFX_STOP("Rampage");
		GRAPHICS::ANIMPOSTFX_PLAY("RampageOut", 0, FALSE);
	}
	
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
