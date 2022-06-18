#include "pch.h"
#include "ScreenUtils.hpp"

using namespace Rampage;

void UI::show_help_text(const char* text, bool beep) {
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, 0);
}

void UI::show_long_help_text(const char* text1, const char* text2, bool beep) {
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("TWOSTRINGS");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text1);
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text2);
	HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, 0);
}

void UI::show_subtitle(const char* text, int time) {
	HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_PRINT(time, true);
}

void UI::show_notification(const char* text) {
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, true);
}

void UI::set_blip_name(Blip blip, const char* name) {
	HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(name);
	HUD::END_TEXT_COMMAND_SET_BLIP_NAME(blip);
}

Blip UI::create_blip(float x, float y, float z, int sprite, eBlipColor color, const char* name) {
	Blip blipHandle = HUD::ADD_BLIP_FOR_COORD(x, y, z);
	HUD::SET_BLIP_SPRITE(blipHandle, sprite);
	HUD::SET_BLIP_COLOUR(blipHandle, color);
	set_blip_name(blipHandle, name);
	HUD::SET_BLIP_AS_SHORT_RANGE(blipHandle, true);
	return blipHandle;
}

void UI::create_blip_for_enemy(Ped ped) {
	Blip blipHandle = HUD::ADD_BLIP_FOR_ENTITY(ped);
	HUD::SET_BLIP_SCALE(blipHandle, 0.7f);
	HUD::SET_BLIP_SPRITE(blipHandle, eBlipSprite::BlipSpriteEnemy);
	HUD::SET_BLIP_COLOUR(blipHandle, eBlipColor::BlipColorRed);
	set_blip_name(blipHandle, "Enemy");
}

void UI::create_blip_for_enemy(Ped ped, int sprite, const char* name) {
	Blip blipHandle = HUD::ADD_BLIP_FOR_ENTITY(ped);
	HUD::SET_BLIP_SPRITE(blipHandle, sprite);
	HUD::SET_BLIP_SCALE(blipHandle, 0.8f);
	HUD::SET_BLIP_COLOUR(blipHandle, eBlipColor::BlipColorRed);
	set_blip_name(blipHandle, name);
}

void UI::create_blip_for_enemy_vehicle(Vehicle vehicle) {
	Blip blipHandle = HUD::ADD_BLIP_FOR_ENTITY(vehicle);
	Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);

	if (VEHICLE::IS_THIS_MODEL_A_CAR(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, eBlipSprite::BlipSpritePersonalVehicleCar);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_BIKE(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, eBlipSprite::BlipSpritePersonalVehicleBike);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_HELI(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, eBlipSprite::BlipSpriteHelicopterAnimated);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_PLANE(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, eBlipSprite::BlipSpritePlane);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_BOAT(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, eBlipSprite::BlipSpriteBoat);
	}

	HUD::SET_BLIP_SCALE(blipHandle, 0.8f);
	HUD::SET_BLIP_COLOUR(blipHandle, eBlipColor::BlipColorRed);
	set_blip_name(blipHandle, "Enemy vehicle");
}

void UI::delete_entity_blip(Entity entity) {
	Blip blip = HUD::GET_BLIP_FROM_ENTITY(entity);
	HUD::REMOVE_BLIP(&blip);
}
