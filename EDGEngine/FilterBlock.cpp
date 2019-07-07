#pragma once
#include "FilterBlock.h"

#include "Enums.h"

#include "Batcher.h"
#include "EFont.h"
#include "Helper.h"
#include <vector>
#include "EButton.h"
#include "ETexture.h"
#include "EGabarite.h"

//#include "EButton.cpp"



	//std::vector<EButton*> filter_block_button_list;

	int FilterBlock::rarity_text_to_id(string _text)
	{
		for (int i = 0; i < rarity_value->length(); i++)
		{
			if (rarity_value[i] == _text) { return i; }
		}

		return -1;
	}

	string FilterBlock::bool_to_string(bool _b)
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

	FilterBlock::FilterBlock()
	{
		//zzz = new EButton();
		//zzz->button_x = 200;
	}

	FilterBlock::~FilterBlock()
	{

	}

	void FilterBlock::update(float _d)
	{
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->update(_d);
		}
	}

	void FilterBlock::draw(Batcher* _batch)
	{
		if (is_show)
		{_batch->setcolor_255(210,200,190,100);}
		else
		{_batch->setcolor_255(64, 32, 16, 100);}


		if (DefaultGabarite::gabarite_white != NULL)
		{
			_batch->draw_rect_with_uv(x, y, size_x, size_y, DefaultGabarite::gabarite_white);
		}

		_batch->setcolor_255(rama_red, rama_green, rama_blue, rama_alpha / 2.55f);
		_batch->draw_rect_with_uv(x + size_x - 102, y + 3, 104, 29, DefaultGabarite::gabarite_white);

		_batch->setcolor_255(bg_red, bg_green, bg_blue, bg_alpha/2.55f);
		_batch->draw_rect_with_uv(x+size_x-100, y+5, 100, 25, DefaultGabarite::gabarite_white);

		if (ray_color == Enums::GameColors::RED) { _batch->setcolor_255(255, 0, 0, 100); }
		if (ray_color == Enums::GameColors::GREEN) { _batch->setcolor_255(0, 255, 0, 100); }
		if (ray_color == Enums::GameColors::BLUE) { _batch->setcolor_255(0, 0, 255, 100); }
		if (ray_color == Enums::GameColors::BROWN) { _batch->setcolor_255(255, 128, 64, 100); }
		if (ray_color == Enums::GameColors::WHITE) { _batch->setcolor_255(255, 255, 255, 100); }
		if (ray_color == Enums::GameColors::YELLOW) { _batch->setcolor_255(255, 255, 0, 100); }

		_batch->draw_rect_with_uv(x + size_x - 120, y + 5, 5, 50, DefaultGabarite::gabarite_white);

		float temp_pos_x = 250;
		float temp_pos_y = 0;

		
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->button_x = temp_pos_x;
			filter_block_items_button_list.at(i)->draw(_batch);


			if (filter_block_items_button_list.at(i)->gabarite != NULL)
			{
				temp_pos_x += filter_block_items_button_list.at(i)->button_size_x + 3;

			}
		}

		/*for (int i = 0; i < filter_flock_button_list.size(); i++)
		{
			filter_flock_button_list.at(i)->draw(_batch);
		}*/
	}

	void FilterBlock::add_debug(bool _if, string _text, EFont* _font, Batcher* _batch)
	{
		if (!_if)
		{ _batch->setcolor(1, 0, 0, 1); }
		else
		{ _batch->setcolor(0, 0.1f, 0.2f, 0.9f); } 

		if (_if)
		{
			_font->draw(_batch, _text, x + debug_text_x, y + debug_text_y);

			debug_text_y += 20;
			if (debug_text_y + 20 > size_y)
			{
				debug_text_y = 0;
				debug_text_x += 200;
			}
		}
	}

	void FilterBlock::text_pass(EFont* _font,Batcher* _batch)
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

			
			_font->add_draw(_batch, *class_list.at(i)+"   ", debug_text_x+250, y+10);
		}

		_font->x_adding = 0;
		for (int i = 0; i < base_type_list.size(); i++)
		{
			_batch->setcolor(0.6f, 1.0f, 0.6f, 1.0f);

			_font->add_draw(_batch, *base_type_list.at(i)+"   ", debug_text_x + 250, y + 30);
		}

		_font->x_adding = 0;
		for (int i = 0; i < explicit_mod_list.size(); i++)
		{
			_batch->setcolor(0.6f, 0.7f, 1.0f, 1.0f);

			_font->add_draw(_batch, *explicit_mod_list.at(i)+"   ", debug_text_x + 250, y + 50);
		}

		_font->x_adding = 0;
		for (int i = 0; i < prophecy_list.size(); i++)
		{
			_batch->setcolor(1.0f, 0.0f, 1.0f, 1.0f);

			_font->add_draw(_batch, *prophecy_list.at(i) + "   ", debug_text_x + 250, y + 70);
		}

		_batch->setcolor_255(text_color_red, text_color_green, text_color_blue, text_color_alpha);

		//_font->x_adding = 0;
		_font->draw(_batch, "Just a Text", x + size_x - 97, y + 10);

		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->text_pass(_font,_batch);
		}
		

	}

