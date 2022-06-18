#pragma once

#include "natives.h"
#include "enums.h"

namespace Rampage {
	namespace UI {
		void show_subtitle(const char* text, int time);
		void show_help_text(const char* text, bool beep);
		void show_long_help_text(const char* text1, const char* text2, bool beep);
		void show_notification(const char* text);
		void set_blip_name(Blip blip, const char* name);
		Blip create_blip(float x, float y, float z, int sprite, eBlipColor color, const char* name);
		void create_blip_for_enemy(Ped ped);
		void create_blip_for_enemy(Ped ped, int sprite, const char* name);
		void create_blip_for_enemy_vehicle(Vehicle vehicle);
		void delete_entity_blip(Entity entity);
	}
}