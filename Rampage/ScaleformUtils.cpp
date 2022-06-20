#include "pch.h"
#include "ScaleformUtils.hpp"

using namespace Rampage;

int UI::request_scaleform(const std::string& scaleform_name) {
	int handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE(scaleform_name.c_str());

	if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(handle))
		WAIT(1);

	return handle;
}

void UI::set_scaleform_title_description(int scaleform_handle, const char* title, const char* description) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_handle, "SET_MISSION_TITLE");
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(title);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(description);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

void UI::set_total(int scaleform_handle, int type, float percentage, const char* title) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_handle, "SET_TOTAL");
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(type);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(percentage * 100.0f);
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(title);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

void UI::add_scaleform_time_objective(int scaleform_handle, int slot, const char* title, bool passed, int ms) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_handle, "SET_DATA_SLOT");
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(slot);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(passed);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_TIME(ms, 6);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(title);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

void UI::add_scaleform_int_objective(int scaleform_handle, int slot, const char* title, bool passed, int value) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_handle, "SET_DATA_SLOT");
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(slot);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(passed);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2);
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("NUMBER");
	HUD::ADD_TEXT_COMPONENT_INTEGER(value);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(title);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

void UI::complete_scaleform(int scaleform_handle) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_handle, "DRAW_MENU_LIST");
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

void UI::free_scaleform(int scaleform_handle) {
	GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&scaleform_handle);
}

int UI::request_mid_message_scaleform()
{
	int handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_big_message_freemode");

	while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(handle))
		WAIT(1);

	return handle;
}

void UI::set_scaleform_text(int scaleform, const std::string& title, const std::string& subtitle)
{
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SHOW_MISSION_END_MP_MESSAGE");
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(title.c_str());
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(subtitle.c_str());
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(100);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}


void UI::set_wasted_scaleform_text(int scaleform, const std::string& title, const std::string& subtitle)
{
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SHOW_SHARD_WASTED_MP_MESSAGE");
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(title.c_str());
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}