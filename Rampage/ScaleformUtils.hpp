#pragma once

#include "natives.h"
#include <string>

namespace Rampage {
	namespace UI {
		int request_scaleform(const std::string& scaleform_name);
		void set_scaleform_title_description(int scaleform_handle, const char* scaleform_title, const char* scaleform_description);
		void add_scaleform_time_objective(int scaleform_handle, int slot, const char* title, bool passed, int ms);
		void add_scaleform_int_objective(int scaleform_handle, int slot, const char* title, bool passed, int value);
		void complete_scaleform(int scaleform_handle);
		void free_scaleform(int scaleform_handle);
		void set_scaleform_text(int scaleform, const std::string& title, const std::string& subtitle);
		void set_wasted_scaleform_text(int scaleform, const std::string& title, const std::string& subtitle);
		int request_mid_message_scaleform();
		void set_total(int scaleform_handle, int type, float percentage, const char* title);
	}
}