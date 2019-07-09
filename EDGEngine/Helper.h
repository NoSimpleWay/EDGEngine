#pragma once
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EGabarite.h"



	static float correction_x;
	static float correction_y;

	static float correction_x_offset;
	static float correction_y_offset;



	static std::string rarity_value[4] = { "Normal", "Magic", "Rare", "Unique" };

	static std::string game_color_names[6] = { "Red", "Green", "Blue", "Brown", "White", "Yellow" };

	static std::string condition_names[6] = { "<=", "<", "=", ">", ">=","<>" };

	static bool global_button_block = false;



	

	
	static EGabarite* gabarite_white_pixel;



	namespace Helper {
		

		int get_id_from_array(std::string _a[], std::string _text);
		bool check_is_condition_symbols(std::string _s);

		int rarity_text_to_id(std::string _text);
		int get_id_from_game_color_text(std::string _text);
	}

