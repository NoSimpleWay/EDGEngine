#include "Helper.h"
#include <iostream>

namespace VectorMath {
	
	int rarity_text_to_id(std::string _text)
	{
		for (int i = 0; i < rarity_value->length(); i++)
		{
			if (rarity_value[i] == _text) { return i; }
		}
		return -1;
	}

	int get_id_from_game_color_text(std::string _text)
	{
		for (int i = 0; i < game_color_names->length(); i++)
		{
			if (game_color_names[i] == _text) { return i; }
		}
		return -1;
	}

	bool check_is_condition_symbols(std::string _s)
	{
		if
			(
				(_s == "<=")	||
				(_s == "<")		||
				(_s == "=")		||
				(_s == ">")		||
				(_s == ">=")
			)
		{
			return true;
		}

		return false;
	}

	int get_id_from_array(std::string _a[], std::string _text)
	{
		
		std::cout << "array is " << sizeof(_a[0]) / sizeof(_a) << " length" << std::endl;
		for (int array_i = 0; array_i < sizeof(_a[0])/sizeof(_a); array_i++)
		{
			//std::cout << "element [" << array_i << "] is " << _a[array_i] << " compared with " << _text<<std::endl;

			if (_a[array_i] == _text)
			{
				//std::cout << " math by id:" << array_i << " key:" << _a[array_i] << std::endl;
				return array_i;
			}
		}

		return -1;
	}


}







