#include "pch.h"
#include "ScreenUtils.hpp"

using namespace Rampage;

struct Position
{
	float x;
	float y;

	Position(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

std::unordered_map<int, Position> badge_slots = {
	{0, Position(0.91f, 0.97f)},
	{1, Position(0.91f, 0.918f)}
};

std::unordered_map<int, Position> content_slots =
{
	{0, Position(0.75f, 0.952f)},
	{1, Position(0.75f, 0.90f)}
};

std::unordered_map<int, Position> title_slots =
{
	{0, Position(0.855f, 0.96f)},
	{1, Position(0.855f, 0.91f)}
};

void draw_sprite(float x, float y, bool red)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("timerbars"))
		UI::load_sprites();

	GRAPHICS::DRAW_SPRITE("timerbars", "all_black_bg", x, y, 0.15f, 0.045f, 0, 0, 0, 0, 150, 0, 0);

	if (red)
		GRAPHICS::DRAW_SPRITE("timerbars", "all_red_bg", x, y, 0.15f, 0.045f, 0, 165, 15, 1, 150, 0, 0);
}

void draw_sprite_text(float x, float y, float scale, const char* text, bool right)
{
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	if (right)
	{
		HUD::SET_TEXT_WRAP(0.6f, 0.975f);
		HUD::SET_TEXT_JUSTIFICATION(2);
	}
	HUD::SET_TEXT_SCALE(1.0f, scale);
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
}

void UI::draw_badge(std::string title, std::string content, bool red, int slot)
{
	if (red) {
		title = std::string("~r~").append(title);
		content = std::string("~r~").append(content);
	}

	Position bPos = badge_slots.at(slot);
	Position cPos = content_slots.at(slot);
	Position tPos = title_slots.at(slot);
	draw_sprite(bPos.x, bPos.y, red);
	draw_sprite_text(cPos.x, cPos.y, 0.42f, content.c_str(), true);
	draw_sprite_text(tPos.x, tPos.y, 0.295f, title.c_str(), false);
}

void UI::load_sprites()
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("timerbars", false);

	while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("timerbars"))
		WAIT(1);
}

void UI::free_sprites()
{
	GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED("timerbars");
}

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
