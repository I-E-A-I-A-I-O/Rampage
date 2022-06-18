#include "pch.h"
#include "UIScript.hpp"

using namespace Rampage;

int mc_scaleform_handle;
int bm_scaleform_handle;
int wt_scaleform_handle;
int bm_start;
int phase;

void clean() {
	if (mc_scaleform_handle != 0) {
		UI::free_scaleform(mc_scaleform_handle);
		mc_scaleform_handle = 0;
	}

	if (bm_scaleform_handle != 0) {
		UI::free_scaleform(bm_scaleform_handle);
		bm_scaleform_handle = 0;
	}
		

	if (wt_scaleform_handle != 0) {
		UI::free_scaleform(wt_scaleform_handle);
		wt_scaleform_handle = 0;
	}

	phase = 0;
}

void proccess_passed_scaleform() {
	if (phase == 0) {
		bm_scaleform_handle = UI::request_mid_message_scaleform();
		UI::set_scaleform_text(bm_scaleform_handle, "PASSEaD", "PENIS");
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(bm_scaleform_handle, "SET_SHARD_BACKGROUND_HEIGHT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0.27f);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		mc_scaleform_handle = UI::request_scaleform("MISSION_COMPLETE");
		bm_start = MISC::GET_GAME_TIMER();
		phase = 1;
	}

	if (phase == 1) {
		if (MISC::GET_GAME_TIMER() - bm_start < 1250) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(bm_scaleform_handle, 255, 255, 0, 255, 0);
		}
		else {
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(bm_scaleform_handle, "TRANSITION_UP");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0.3f);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			bm_start = MISC::GET_GAME_TIMER();
			phase = 2;
		}
	}

	if (phase == 2) {
		if (MISC::GET_GAME_TIMER() - bm_start < 750) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(bm_scaleform_handle, 255, 255, 0, 255, 0);
		}
		else
		{
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(bm_scaleform_handle, "SET_SHARD_BACKGROUND_HEIGHT");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0.45f);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			UI::set_scaleform_title_description(mc_scaleform_handle, "", "Objectives");
			UI::add_scaleform_time_objective(mc_scaleform_handle, 0, "TIMED OBJECTIVE", true, 5250);
			UI::add_scaleform_time_objective(mc_scaleform_handle, 1, "TIMED OBJECTIVE 2", false, 10000);
			UI::set_total(mc_scaleform_handle, 4, 2, "TOTAL TOTALED");
			UI::complete_scaleform(mc_scaleform_handle);
			phase = 3;
			bm_start = MISC::GET_GAME_TIMER();
		}
	}

	if (phase == 3) {
		if (MISC::GET_GAME_TIMER() - bm_start < 6000) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(bm_scaleform_handle, 255, 255, 0, 255, 0);
			GRAPHICS::DRAW_SCALEFORM_MOVIE(mc_scaleform_handle, 0.5f, 0.59f, 0.2021f, 0.5111f, 53, 195, 206, 1, 0);
		}
		else {
			GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(bm_scaleform_handle, "SHARD_ANIM_OUT");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(5);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2000);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			phase = 4;
			bm_start = MISC::GET_GAME_TIMER();
		}
	}

	if (phase == 4) {
		if (MISC::GET_GAME_TIMER() - bm_start < 2000) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(bm_scaleform_handle, 255, 255, 0, 255, 0);
		}
		else {
			UI::free_scaleform(bm_scaleform_handle);
			UI::free_scaleform(mc_scaleform_handle);
			mc_scaleform_handle = 0;
			bm_scaleform_handle = 0;
			phase = 0;
			Globals::UIFlags::scaleform_active = false;
		}
	}
}

void process_rampage_scaleform() {
	if (phase == 0) {
		wt_scaleform_handle = UI::request_mid_message_scaleform();
		UI::set_wasted_scaleform_text(wt_scaleform_handle, "~r~rampage", "");
		bm_start = MISC::GET_GAME_TIMER();
		phase = 1;
	}

	if (phase == 1) {
		if (MISC::GET_GAME_TIMER() - bm_start < 1500) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(wt_scaleform_handle, 255, 255, 0, 255, 0);
		}
		else {
			GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(wt_scaleform_handle, "SHARD_ANIM_OUT");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(5);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2000);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			phase = 2;
			bm_start = MISC::GET_GAME_TIMER();
		}
	}

	if (phase == 2) {
		if (MISC::GET_GAME_TIMER() - bm_start < 2000) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(wt_scaleform_handle, 255, 255, 0, 255, 0);
		}
		else {
			UI::free_scaleform(wt_scaleform_handle);
			wt_scaleform_handle = 0;
			phase = 0;
			Globals::UIFlags::scaleform_active = false;
		}
	}
}

void ui_main() {
	for (;;) {
		if (Globals::UIFlags::clean) {
			clean();
			Globals::UIFlags::clean = false;
		}

		if (Globals::UIFlags::scaleform_active) {
			switch (Globals::UIFlags::scaleform_type)
			{
			case Rampage::ScaleformTypes::PassedWithObjectives:
				proccess_passed_scaleform();
				break;
			case Rampage::ScaleformTypes::RampageStarted:
				process_rampage_scaleform();
				break;
			default:
				phase = 0;
				Globals::UIFlags::scaleform_active = false;
				break;
			}
		}

		WAIT(0);
	}
}

void UI::on_start() {
	ui_main();
}

void UI::on_abort() {
	clean();
}