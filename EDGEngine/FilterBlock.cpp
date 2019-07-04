#include "Enums.h"
#include "Batcher.h"
#include "EFont.h"
#include "Helper.h"
#include <vector>
class FilterBlock
{
public:
	float x=0;
	float y=0;
	float size_x=300;
	float size_y=100;

	int socket_count = 0;		bool is_socket_active = false;			std::string socket_condition = "=";
	int links_count=0;			bool is_links_active = false;			std::string links_condition = "=";

	int item_level=0;			bool is_item_level_active = false;		std::string item_level_condition = "=";
	int required_level=0;		bool is_required_level_active = false;	std::string required_level_condition = "=";

	int item_width = 0;			bool is_item_width_active = false;		std::string item_width_condition = "=";
	int item_height = 0;		bool is_item_height_active = false;		std::string item_height_condition = "=";

	int item_quality = 0;		bool is_item_qualityt_active = false;	std::string item_quality_condition = "=";
	int item_stack_size = 0;	bool is_stack_size_active = false;		std::string item_stack_size_condition = "=";
	int gem_level = 0;			bool is_gem_level_active = false;		std::string gem_level_condition = "=";

	int map_tier = 0;			bool is_map_tier_active = false;		std::string map_tier_condition = "=";


	bool is_socket_group_active = false;
	int red_sockets=0;
	int green_sockets=0;
	int blue_sockets=0;
	int white_sockets=0;
	bool is_prophecy_active = false;
	
	std::string	item_rarity = "Rare";				bool is_item_rarity_active = false;	 std::string rarity_condition = "=";

	bool		is_corrupted		= false;		bool is_corrupted_active = false;

	//Enums::YNE		is_corrupted		= Enums::YNE::EITHER;		bool is_corrupted_active = false;
	bool		is_shaper_item		= false;		bool is_shaper_item_active = false;
	bool		is_elder_item		= false;		bool is_elder_item_active = false;
	bool		is_fractured_item	= false;		bool is_fractured_item_active = false;
	bool		is_synthesised_item	= false;		bool is_synthesised_item_active = false;
	bool		is_enchantment_item = false;		bool is_enchantment_item_active = false;

	bool		is_elder_map = false;				bool is_elder_map_active = false;
	bool		is_shaper_map = false;				bool is_shaper_map_active = false;

	bool is_font_size_active = false;
	int font_size=30;
	
	bool is_text_color_active = false;
	int text_color_red=255;
	int text_color_green=255;
	int text_color_blue=255;
	int text_color_alpha=255;

	bool is_bg_color_active = false;
	int bg_red = 128;
	int bg_green = 128;
	int bg_blue = 128;
	int bg_alpha = 255;

	bool is_rama_color_active = false;
	int rama_red = 0;
	int rama_green = 0;
	int rama_blue = 0;
	int rama_alpha = 255;

	int debug_text_y = 0;
	int debug_text_x = 0;

	bool is_alert_sound = false;
	string alert_sound_name = "1";
	int alert_sound_volume = 100;

	bool is_ray = false;
	Enums::GameColors ray_color = Enums::GameColors::WHITE;

	bool is_minimap_icon = false;
	Enums::GameColors minimap_icon_color = Enums::GameColors::WHITE;
	Enums::IconShape minimap_icon_shape = Enums::IconShape::CIRCLE;
	Enums::IconSize minimap_icon_size = Enums::IconSize::SMALL;

	bool is_identified = false;
	bool is_identified_active = false;



	std::vector<string*> class_list;
	std::vector<string*> base_type_list;
	std::vector<string*> explicit_mod_list;
	std::vector<string*> prophecy_list;

	string YNE_value[3] =  { "yes", "no", "either" };
	

	bool is_show = true;
	bool disable_drop_sound = false;

	static int rarity_text_to_id(string _text)
	{
		for (int i = 0; i < rarity_value->length(); i++)
		{
			if (rarity_value[i] == _text) { return i; }
		}

		return -1;
	}

	static string bool_to_string(bool _b)
	{
		if (_b)
		{
			return "true";
		}
		else
		{
			return "false";
		}

	}

	FilterBlock()
	{

	}

	~FilterBlock()
	{

	}

	void draw(Batcher* _batch)
	{
		if (is_show)
		{_batch->setcolor_255(0, 0, 0, 100);}
		else
		{_batch->setcolor_255(64, 32, 16, 100);}

		_batch->draw_rect_with_uv(x,y,size_x,size_y,0,0,1,1);

		_batch->setcolor_255(rama_red, rama_green, rama_blue, rama_alpha / 2.55f);
		_batch->draw_rect_with_uv(x + size_x - 102, y + 3, 104, 29, 0, 0, 1, 1);

		_batch->setcolor_255(bg_red, bg_green, bg_blue, bg_alpha/2.55f);
		_batch->draw_rect_with_uv(x+size_x-100, y+5, 100, 25, 0, 0, 1, 1);

		if (ray_color == Enums::GameColors::RED) { _batch->setcolor_255(255, 0, 0, 100); }
		if (ray_color == Enums::GameColors::GREEN) { _batch->setcolor_255(0, 255, 0, 100); }
		if (ray_color == Enums::GameColors::BLUE) { _batch->setcolor_255(0, 0, 255, 100); }
		if (ray_color == Enums::GameColors::BROWN) { _batch->setcolor_255(255, 128, 64, 100); }
		if (ray_color == Enums::GameColors::WHITE) { _batch->setcolor_255(255, 255, 255, 100); }
		if (ray_color == Enums::GameColors::YELLOW) { _batch->setcolor_255(255, 255, 0, 100); }

		_batch->draw_rect_with_uv(x + size_x - 120, y + 5, 5, 50, 0, 0, 1, 1);
	}

	void add_debug(bool _if, string _text, EFont* _font, Batcher* _batch)
	{
		if (!_if)
		{ _batch->setcolor(1, 0, 0, 1); }
		else
		{ _batch->setcolor(1, 1, 1, 1); } 

		if (_if)
		{
			_font->draw(_batch, _text, x + debug_text_x, y + debug_text_y);

			debug_text_y += 20;
			if (debug_text_y + 20 > size_y)
			{
				debug_text_y = 0;
				debug_text_x += 100;
			}
		}
	}

	void text_pass(EFont* _font,Batcher* _batch)
	{
		_batch->setcolor(1, 1, 1, 1);

		debug_text_y = 0;
		debug_text_x = 0;

		add_debug(is_socket_active, "Sockets " + socket_condition + " " + std::to_string(socket_count), _font, _batch);
		add_debug(is_links_active, "Links " + links_condition + " " + std::to_string(links_count), _font, _batch);

		add_debug(is_item_level_active, "Item level " + item_level_condition+ " " + std::to_string(item_level), _font, _batch);

		add_debug(is_corrupted_active, "Rarity "+ rarity_condition + " " + item_rarity, _font, _batch);
		add_debug(is_alert_sound, "Aler sound: " + alert_sound_name, _font, _batch);
		add_debug(is_ray, "Ray", _font, _batch);

		add_debug(is_corrupted_active, "Corrupted: " + bool_to_string(is_corrupted), _font, _batch);
		add_debug(is_shaper_item_active, "Shaper item: " + bool_to_string(is_shaper_item), _font, _batch);
		add_debug(is_identified_active, "Identified: " + bool_to_string(is_identified), _font, _batch);

		//add_debug(is_text_color, "Font size: " + rarity_value[item_rarity], _font, _batch);


		_font->x_adding = 0;
		for (int i = 0; i < class_list.size(); i++)
		{
			_batch->setcolor(1.0f, 0.8f, 0.6f, 1.0f);

			
			_font->add_draw(_batch, *class_list.at(i)+"   ", debug_text_x+100, y+10);
		}

		_font->x_adding = 0;
		for (int i = 0; i < base_type_list.size(); i++)
		{
			_batch->setcolor(0.6f, 1.0f, 0.6f, 1.0f);

			_font->add_draw(_batch, *base_type_list.at(i)+"   ", debug_text_x + 100, y + 20);
		}

		_font->x_adding = 0;
		for (int i = 0; i < explicit_mod_list.size(); i++)
		{
			_batch->setcolor(0.6f, 0.7f, 1.0f, 1.0f);

			_font->add_draw(_batch, *explicit_mod_list.at(i)+"   ", debug_text_x + 100, y + 40);
		}

		_font->x_adding = 0;
		for (int i = 0; i < prophecy_list.size(); i++)
		{
			_batch->setcolor(1.0f, 0.0f, 1.0f, 1.0f);

			_font->add_draw(_batch, *prophecy_list.at(i) + "   ", debug_text_x + 100, y + 60);
		}

		_batch->setcolor_255(text_color_red, text_color_green, text_color_blue, text_color_alpha);

		//_font->x_adding = 0;
		_font->draw(_batch, "Just a Text", x + size_x - 97, y + 10);
		
	}

};