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
#include "EButtonFilterItem.h"
#include "EButtonDropCondition.h"
#include "EButtonInputBaseData.h"
#include "EButtonDropRarity.h"
#include "EButtonService.h"
#include "EButtonCheck.h"
#include "EButtonRemove.h"
#include "EButtonPlusWide.h"
#include "EButtonSocketGroup.h"
#include "EButtonExplicit.h"

#include "ExplicitGroup.h"
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

	void FilterBlock::add_base_buttons(string _text, Enums::ButtonType _condition_type, Enums::ButtonType _button_type, bool _sep, int _id)
	{
		base_filter_data_name.push_back(_text);
		base_filter_separator.push_back(_sep);

		

		if (_condition_type != Enums::ButtonType::BUTTON_NONE)
		{
			EButtonDropCondition* but;
			but = new EButtonDropCondition(0, 0, 30, 13, _condition_type);
			but->master_block = this;
			but->master_window = StaticData::window_filter_block;

			base_filter_condition_list.push_back(but);

			//std::cout << "Added: " << _text << std::endl;
		}
		else
		{
			//std::cout << "NULL: " << _text << std::endl;
			base_filter_condition_list.push_back(NULL);
		}

		if (_button_type != Enums::ButtonType::BUTTON_NONE)
		{
			EButton* but=NULL;

			if (_button_type!=Enums::ButtonType::BUTTON_RARITY)
			{
				if (_button_type == Enums::ButtonType::BUTTON_SOCKET_GROUP) { but = new EButtonSocketGroup(0, 0, 100, 17, _button_type); }
				else
				if
				(
					(_button_type == Enums::ButtonType::BUTTON_SHAPER_ITEM) ||
					(_button_type == Enums::ButtonType::BUTTON_SHAPER_MAP) ||
					(_button_type == Enums::ButtonType::BUTTON_ELDER_ITEM) ||
					(_button_type == Enums::ButtonType::BUTTON_ELDER_MAP) ||

					(_button_type == Enums::ButtonType::BUTTON_CORRUPTION) ||
					(_button_type == Enums::ButtonType::BUTTON_FRACTURED) ||
					(_button_type == Enums::ButtonType::BUTTON_SYNTHESISED) ||
					(_button_type == Enums::ButtonType::BUTTON_IDENTIFIED) ||
					(_button_type == Enums::ButtonType::BUTTON_ANY_ENCHANTMENT)
				)
				{
					//cout << "Запилил" << endl;
					but = new EButtonCheck(0, 0, 20, 20, _button_type);
				}
				else
				{
					but = new EButtonInputBaseData(0, 0, 65, 17, _button_type);
				}
			}
			else
			{
				if (_button_type == Enums::ButtonType::BUTTON_RARITY) { but = new EButtonDropRarity(0, 0, 65, 17, _button_type);}
				//if (_button_type == Enums::ButtonType::BUTTON_SOCKET_GROUP) { but = new EButtonDropRarity(0, 0, 16, 17, _button_type);}
			}

			but->master_block = this;
			but->master_window = StaticData::window_filter_block;

			base_filter_buttons.push_back(but);
		}
		else
		{
			base_filter_buttons.push_back(NULL);
		}

		base_filter_data_active.push_back(false);

		EButton* but_remove = new EButtonRemove(0, 0, 17, 17, Enums::ButtonType::BUTTON_REMOVE_BASE_DATA);
		but_remove->master_window = StaticData::window_filter_block;
		but_remove->master_block = this;
		but_remove->data_id = _id;

		base_filter_data_remove_buttons.push_back(but_remove);

	}

	FilterBlock::FilterBlock()
	{
		//zzz = new EButton();
		//zzz->button_x = 200;

		button_plus = new EButtonFilterItem(0, 0, 45, 45);
		button_plus->gabarite = DefaultGabarite::gabarite_plus;

		button_plus->master_block = this;
		button_plus->master_window = StaticData::window_filter_block;

		button_plus->master_position = Enums::FILTER_BLOCK;
		button_plus->is_plus = true;
		button_plus->description_text = "Add new item";

		button_list.push_back(button_plus);


		/*
		button_service = new EButtonService(0, 0, 45, 45,Enums::ButtonType::BUTTON_FILTER_BLOCK_TO_CONSOLE);
		button_service->master_block = this;
		button_service->master_window = StaticData::window_filter_block;
		button_service->gabarite = DefaultGabarite::gabarite_undefined;*/

		EButton*
		but = new EButtonService(-5,-5,30,30,Enums::ButtonType::BUTTON_SYS_VISUAL_MODE);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonService(-40, -5, 30, 30, Enums::ButtonType::BUTTON_SYS_PLAY_SOUND);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		sound_button_link = but;
		button_list.push_back(but);


		button_add_new_base_data = new EButtonPlusWide(0, 0, 17, 17,Enums::ButtonType::BUTTON_OPEN_BASE_DATA_WINDOW);

		button_add_new_base_data->master_block = this;
		button_add_new_base_data->master_window = StaticData::window_filter_block;

		button_list.push_back(button_add_new_base_data);




		button_add_new_EPC = new EButtonPlusWide(0, 0, 17, 17, Enums::ButtonType::BUTTON_OPEN_EXPLICIT_PROPHECY_CLASS_WINDOW);
		button_add_new_EPC->master_block = this;
		button_add_new_EPC->master_window = StaticData::window_filter_block;
		button_list.push_back(button_add_new_EPC);


		//std::cout << "_______________________________________ " << std::endl;
		add_base_buttons("Rarity",				Enums::ButtonType::BUTTON_CONDITION_RARITY,			Enums::ButtonType::BUTTON_RARITY,			false,	0);//0
		add_base_buttons("Item level",			Enums::ButtonType::BUTTON_CONDITION_ITEM_LEVEL,		Enums::ButtonType::BUTTON_ITEM_LEVEL,		false,	1);//1
		add_base_buttons("Req. level",			Enums::ButtonType::BUTTON_CONDITION_DROP_LEVEL,		Enums::ButtonType::BUTTON_DROP_LEVEL,		false,	2);//2
		add_base_buttons("Sockets",				Enums::ButtonType::BUTTON_CONDITION_SOCKETS,		Enums::ButtonType::BUTTON_SOCKETS,			false,	3);//3
		add_base_buttons("Links",				Enums::ButtonType::BUTTON_CONDITION_LINKS,			Enums::ButtonType::BUTTON_LINKS,			false,	4);//4
		add_base_buttons("Socket color",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_SOCKET_GROUP,		false,	5);//5

		add_base_buttons("Quality",				Enums::ButtonType::BUTTON_CONDITION_QUALITY,		Enums::ButtonType::BUTTON_QUALITY,			true,	6);//6
		add_base_buttons("Gem level",			Enums::ButtonType::BUTTON_CONDITION_GEM_LEVEL,		Enums::ButtonType::BUTTON_GEM_LEVEL,		false,	7);//7

		add_base_buttons("Map tier",			Enums::ButtonType::BUTTON_CONDITION_MAP_TIER,		Enums::ButtonType::BUTTON_MAP_TIER,			true,	8);//8
		add_base_buttons("Shaped map?",			Enums::ButtonType::BUTTON_CONDITION_MAP_TIER,		Enums::ButtonType::BUTTON_SHAPER_MAP,		true,	9);//9
		add_base_buttons("Elder map?",			Enums::ButtonType::BUTTON_CONDITION_MAP_TIER,		Enums::ButtonType::BUTTON_ELDER_MAP,		true,	10);//10

		add_base_buttons("Width",				Enums::ButtonType::BUTTON_CONDITION_WIDTH,			Enums::ButtonType::BUTTON_WIDTH,			true,	11);//11
		add_base_buttons("Height",				Enums::ButtonType::BUTTON_CONDITION_HEIGHT,			Enums::ButtonType::BUTTON_HEIGHT,			false,	12);//12
		add_base_buttons("Stack size",			Enums::ButtonType::BUTTON_CONDITION_STACK_SIZE,		Enums::ButtonType::BUTTON_STACK_SIZE,		false,	13);//13

		add_base_buttons("Corrupted?",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_CORRUPTION,		true,	14);//14
		add_base_buttons("Shaper item?",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_SHAPER_ITEM,		false,	15);//15
		add_base_buttons("Elder item?",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_ELDER_ITEM,		false,	16);//16
		add_base_buttons("Synthesised?",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_SYNTHESISED,		false,	17);//17
		add_base_buttons("Fractured?",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_FRACTURED,		false,	18);//18
		add_base_buttons("Any enchantment?",	Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_ANY_ENCHANTMENT,	false,	19);//19
		add_base_buttons("Identified?",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_IDENTIFIED,		false,	20);//20

		
		for (int i = 0; i < 6; i++)
		{
			ExplicitGroup* ex = new ExplicitGroup();
			explicit_list.push_back(ex);

			EButton* but_close = new EButtonRemove(0,0,17,17, Enums::ButtonType::BUTTON_REMOVE_EXPLICIT_GROUP);

			but_close->master_block = this;
			but_close->master_window = StaticData::window_filter_block;
			but_close->is_active = false;
			but_close->data_id = i;

			ex->button_close=but_close;
			button_list.push_back(but_close);

			EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_LIST);
			explicit_button->text = "+";
			explicit_button->master_block = this;
			explicit_button->master_window = StaticData::window_filter_block;
			explicit_button->button_size_x = EFont::get_width(EFont::font_arial, "+") + 5.0f;
			explicit_button->can_be_removed = false;
			explicit_button->have_input_mode = false;
			explicit_button->is_plus = true;
			explicit_button->is_active = false;
			explicit_button->data_id = i;

			ex->button_add = explicit_button;
			button_list.push_back(explicit_button);

			



		}

		plus_class_button_link = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLASS_LIST);
		plus_class_button_link->text = "+";
		plus_class_button_link->master_block = this;
		plus_class_button_link->master_window = StaticData::window_filter_block;
		plus_class_button_link->button_size_x = EFont::get_width(EFont::font_arial, "+") + 5.0f;
		plus_class_button_link->can_be_removed = false;
		plus_class_button_link->have_input_mode = false;
		plus_class_button_link->is_plus = true;
		plus_class_button_link->is_active = false;

		button_list.push_back(plus_class_button_link);




		std::cout << "Remove button created" << std::endl;
		remove_base_class_button = new EButtonRemove(0, 0, 17, 17, Enums::ButtonType::BUTTON_REMOVE_BASE_CLASS);

		remove_base_class_button->master_block = this;
		remove_base_class_button->master_window = StaticData::window_filter_block;
		remove_base_class_button->is_active = false;

		button_list.push_back(remove_base_class_button);

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

		for (EButton* b : button_list) { if (b->is_active) { b->update(_d); } }


		//button_plus->update(_d);
		
		//button_service->update(_d);

		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			if (filter_block_items_button_list.at(i)->need_remove)
			{
				filter_block_items_button_list.erase(filter_block_items_button_list.begin()+i);
				i--;
			}
		}

		for (int i = 0; i < button_list.size(); i++)
		{
			if (button_list.at(i)->need_remove)
			{
				button_list.erase(button_list.begin() + i);
				i--;
			}
		}


		for (int i = 0; i < base_class_list.size(); i++)
		{
			if (base_class_list.at(i)->need_remove)
			{
				base_class_list.erase(base_class_list.begin() + i);
				i--;
			}
		}

		for (ExplicitGroup* ex : explicit_list)
		{
			for (int i = 0; i < ex->button_list.size(); i++)
			{
				if (ex->button_list.at(i)->need_remove)
				{
					ex->button_list.erase(ex->button_list.begin() + i);
					i--;
				}
			}
		}

			float data_x = x + 155;
			float data_y = 25;

			for (int i = 0; i < base_filter_data_active.size(); i++)
			if (base_filter_data_active.at(i))
			{
				if (base_filter_condition_list.at(i) != NULL)
				{
					base_filter_condition_list.at(i)->button_x = data_x;
					base_filter_condition_list.at(i)->button_y = size_y-data_y;

					base_filter_condition_list.at(i)->update(_d);

					base_filter_buttons.at(i)->button_x = data_x + 35;
					base_filter_buttons.at(i)->button_y = size_y - data_y;
				}
				else
				{
					base_filter_buttons.at(i)->button_x = data_x;
					base_filter_buttons.at(i)->button_y = size_y - data_y;
				}



				base_filter_data_remove_buttons.at(i)->button_x = x-5;
				base_filter_data_remove_buttons.at(i)->button_y = size_y - data_y;

				
				
				base_filter_data_remove_buttons.at(i)->update(_d);


				base_filter_buttons.at(i)->update(_d);

				data_y += _data_y_offset;
			}

			button_add_new_base_data->button_x = x-5;
			button_add_new_base_data->button_y = size_y - data_y;

			//button_add_new_base_data->update(_d);


	}

	void FilterBlock::draw(Batcher* _batch)
	{
		max_h = 100;

		
		
		

		if (is_show)
		{_batch->setcolor_255(210,200,190,25);}
		else
		{_batch->setcolor_255(64, 32, 16, 25);}


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

		float temp_pos_x = 310;
		float temp_pos_y = 10;

		
			
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->button_x = temp_pos_x;
			filter_block_items_button_list.at(i)->button_y = temp_pos_y;

			filter_block_items_button_list.at(i)->default_draw(_batch);
			filter_block_items_button_list.at(i)->additional_draw(_batch);
			//filter_block_items_button_list.at(i)->text_pass(EFont::font, _batch);

			if (filter_block_items_button_list.at(i)->gabarite != NULL)
			{
				temp_pos_x += filter_block_items_button_list.at(i)->button_size_x + 5;

				if (temp_pos_x + 50 > size_x - 200)
				{
					temp_pos_x = 310;
					temp_pos_y += 50;

					if (temp_pos_y + 50 > max_h) { max_h = temp_pos_y + 50; }
				}
			}
		}

		max_h += 35;

		button_plus->button_x = temp_pos_x;
		button_plus->button_y = temp_pos_y;

		float ex_x = 310;
		float ex_y = -10;

		int close_button_id=0;

		for (ExplicitGroup* ex : explicit_list)
		{
			ex_x = 310;

			if (ex->is_active)
			{
				//std::cout << "Try align close button <" << close_button_id << std::endl;

				ex->button_close->button_x=ex_x;
				ex->button_close->button_y=ex_y;

				//std::cout << "SUCCESS"<< std::endl;

				ex_x += 20;

				for (EButton* b : ex->button_list)
				{
					b->button_x = ex_x;
					b->button_y = ex_y;

					ex_x += b->button_size_x+5;
					if (b->button_x + b->button_size_x > size_x - 200.0f)
					{
						ex_x = 310.0f;
						ex_y -= 25.0f;
					}

				}

				ex->button_add->button_x = ex_x;
				ex->button_add->button_y = ex_y;

				max_h += 35.0f;
				ex_y -= 35.0f;
				close_button_id++;
			}
		}

		

		ex_x = 310;


		if (is_base_class_active)
		{
			remove_base_class_button->button_x = ex_x;
			remove_base_class_button->button_y = ex_y;

			ex_x += 20;

			for (EButtonExplicit* b : base_class_list)
			{
				b->button_x = ex_x;
				b->button_y = ex_y;

				ex_x += b->button_size_x + 5;
				if (b->button_x + b->button_size_x > size_x - 200.0f)
				{
					ex_x = 310.0f;
					ex_y -= 25.0f;
				}
			}

			plus_class_button_link->button_x = ex_x;
			plus_class_button_link->button_y = ex_y;

			max_h += 35.0f;
			ex_y -= 35.0f;
		}

		button_add_new_EPC->button_x = 310;
		button_add_new_EPC->button_y = ex_y;



		//if (ex_y * -1.0f + 85.0f > max_h) { max_h = ex_y * -1.0f + 85.0f; }

		//button_service->draw(_batch);

		/*for (int i = 0; i < filter_flock_button_list.size(); i++)
		{
			filter_flock_button_list.at(i)->draw(_batch);
		}*/



		float data_x = x + 155;
		float data_y = 25;

		
		for (int i = 0; i < base_filter_data_active.size(); i++)
		{
			if (base_filter_data_active.at(i))
			{
				_batch->setcolor_alpha(EColorCollection::WHITE, 0.17f);
				_batch->draw_rect_with_uv(data_x - 150, y + size_y - data_y - 3, 155, 21, DefaultGabarite::gabarite_white);

				EFont::font_arial->align_x = Enums::RIGHT;
				_batch->setcolor(EColorCollection::BLACK);

				EFont::font_arial->draw(_batch, base_filter_data_name.at(i), data_x, y + size_y - data_y);
				
				if (base_filter_condition_list.at(i) != NULL)
				{
					//base_filter_condition_list.at(i)->description_text = std::to_string(size_y - data_y);
					base_filter_condition_list.at(i)->default_draw(_batch);
					base_filter_condition_list.at(i)->additional_draw(_batch);
				}
				else
				{
					//base_filter_data_remove_buttons.at(i)->button_x = 0;
					//base_filter_data_remove_buttons.at(i)->button_y = 0;
				}

				base_filter_buttons.at(i)->default_draw(_batch);

				base_filter_data_remove_buttons.at(i)->default_draw(_batch);
				base_filter_data_remove_buttons.at(i)->additional_draw(_batch);

				_batch->setcolor_alpha(EColorCollection::BLACK, 0.17f);
				_batch->draw_rama(data_x - 150, y + size_y - data_y - 3, 155, 21, 1, DefaultGabarite::gabarite_white);
				
				data_y += _data_y_offset;
			}
		}

		for (EButton* b : button_list) { if (b->is_active) { b->default_draw(_batch);} }

		EFont::font_arial->align_x = Enums::LEFT;

		if (data_y > max_h) { max_h = data_y; }

		size_y = max_h;

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

	void FilterBlock::text_pass(Batcher* _batch)
	{
		_batch->setcolor(1, 1, 1, 1);

		for (EButton* b : button_list) { if (b->is_active) { b->text_pass(_batch); } }

		/*


		add_debug(is_socket_active, "Sockets " + socket_condition + " " + std::to_string(socket_count), EFont::font_arial, _batch);
		add_debug(is_links_active, "Links " + links_condition + " " + std::to_string(links_count), EFont::font_arial, _batch);

		add_debug(is_item_level_active, "Item level " + item_level_condition+ " " + std::to_string(item_level), EFont::font_arial, _batch);

		add_debug(is_corrupted_active, "Rarity "+ rarity_condition + " " + item_rarity, EFont::font_arial, _batch);
		add_debug(is_alert_sound, "Aler sound: " + alert_sound_name, EFont::font_arial, _batch);
		add_debug(is_ray, "Ray", EFont::font_arial, _batch);

		add_debug(is_corrupted_active, "Corrupted: " + bool_to_string(is_corrupted), EFont::font_arial, _batch);
		add_debug(is_shaper_item_active, "Shaper item: " + bool_to_string(is_shaper_item), EFont::font_arial, _batch);
		add_debug(is_identified_active, "Identified: " + bool_to_string(is_identified), EFont::font_arial, _batch);
		*/
		//add_debug(is_text_color, "Font size: " + rarity_value[item_rarity], _font, _batch);


		/*
		EFont::font_arial->x_adding = 0;
		for (int i = 0; i < class_list.size(); i++)
		{
			_batch->setcolor(1.0f, 0.8f, 0.6f, 1.0f);

			
			EFont::font_arial->add_draw(_batch, *class_list.at(i)+"   ", debug_text_x+250, y+10);
		}

		EFont::font_arial->x_adding = 0;
		for (int i = 0; i < base_type_list.size(); i++)
		{
			_batch->setcolor(0.6f, 1.0f, 0.6f, 1.0f);

			EFont::font_arial->add_draw(_batch, *base_type_list.at(i)+"   ", debug_text_x + 250, y + 30);
		}

		EFont::font_arial->x_adding = 0;
		for (int i = 0; i < explicit_mod_list.size(); i++)
		{
			_batch->setcolor(0.6f, 0.7f, 1.0f, 1.0f);

			EFont::font_arial->add_draw(_batch, *explicit_mod_list.at(i)+"   ", debug_text_x + 250, y + 50);
		}

		EFont::font_arial->x_adding = 0;
		for (int i = 0; i < prophecy_list.size(); i++)
		{
			_batch->setcolor(1.0f, 0.0f, 1.0f, 1.0f);

			EFont::font_arial->add_draw(_batch, *prophecy_list.at(i) + "   ", debug_text_x + 250, y + 70);
		}
		*/
		_batch->setcolor_255(text_color_red, text_color_green, text_color_blue, text_color_alpha);
		
		//_font->x_adding = 0;
		EFont::font_arial->draw(_batch, "Just a Text", x + size_x - 97, y + 10);

		/*
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->text_pass(_font,_batch);
		}*/

		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->text_pass(_batch);
		}

		for (int i = 0; i < base_filter_data_active.size(); i++)
		{
			if (base_filter_data_active.at(i))
			{
				if (base_filter_condition_list.at(i)!=NULL) { base_filter_condition_list.at(i)->text_pass(_batch); }
				base_filter_buttons.at(i)->text_pass(_batch);

				base_filter_data_remove_buttons.at(i)->text_pass(_batch);
			}
		}

		//button_service->text_pass(_batch);
		
		//EFont::font_arial->draw(_batch, std::to_string(y), x, y);
	}

	void FilterBlock::init()
	{

	}

	void FilterBlock::data_change()
	{
		for (EButtonDropCondition* b : base_filter_condition_list)
		{
			if (b!=NULL)
			{b->incoming_data(this);}
		}

		for (EButton* b : base_filter_buttons)
		{
			if (b != NULL)
			{b->incoming_data(this);}
		}

		change_color_consume(this);

		if (!is_alert_sound)
		{
			sound_button_link->deactivate();
		}
					
		/*
		base_filter_data_active.at(0)=is_item_rarity_active;
		base_filter_data_active.at(1)=is_item_level_active;
		base_filter_data_active.at(2)=is_required_level_active;
		base_filter_data_active.at(3)=is_socket_active;
		base_filter_data_active.at(4)=is_links_active;
		base_filter_data_active.at(5)=is_socket_group_active;
		base_filter_data_active.at(6)=is_item_qualityt_active;
		base_filter_data_active.at(7)=is_gem_level_active;
		base_filter_data_active.at(8)=is_map_tier_active;
		base_filter_data_active.at(9)=is_item_width_active;
		base_filter_data_active.at(10)=is_item_height_active;
		base_filter_data_active.at(11)=is_stack_size_active;
		base_filter_data_active.at(12)=is_corrupted;
		base_filter_data_active.at(13)=is_shaper_item;
		base_filter_data_active.at(14)=is_elder_item_active;
		base_filter_data_active.at(15)=is_synthesised_item;
		base_filter_data_active.at(16)=is_fractured_item;
		base_filter_data_active.at(17)=is_enchantment_item;*/
		
	}

	void FilterBlock::change_color_consume(FilterBlock* _fb)
	{
		EMath::rgb temp_rgb;
		EMath::hsv temp_hsv;

		temp_rgb.r = _fb->bg_red;						temp_rgb.g = _fb->bg_green;							temp_rgb.b = _fb->bg_blue;
		temp_hsv = EMath::rgb2hsv(temp_rgb);
		_fb->bg_hue = temp_hsv.h;						_fb->bg_saturation = temp_hsv.s;					_fb->bg_value = temp_hsv.v;

		temp_rgb.r = _fb->text_color_red;				temp_rgb.g = _fb->text_color_green;					temp_rgb.b = _fb->text_color_blue;
		temp_hsv = EMath::rgb2hsv(temp_rgb);
		_fb->text_color_hue = temp_hsv.h;				_fb->text_color_saturation = temp_hsv.s;			_fb->text_color_value = temp_hsv.v;


		temp_rgb.r = _fb->rama_red;						temp_rgb.g = _fb->rama_green;						temp_rgb.b = _fb->rama_blue;
		temp_hsv = EMath::rgb2hsv(temp_rgb);
		_fb->rama_hue = temp_hsv.h;						_fb->rama_saturation = temp_hsv.s;					_fb->rama_value = temp_hsv.v;
	}

	void FilterBlock::change_color_extract(FilterBlock* _fb)
	{
		EMath::rgb temp_rgb;
		EMath::hsv temp_hsv;

		temp_hsv.h = _fb->bg_hue;							temp_hsv.s = _fb->bg_saturation;					temp_hsv.v = _fb->bg_value;
		temp_rgb = EMath::hsv2rgb(temp_hsv);
		_fb->bg_red = temp_rgb.r;							_fb->bg_green = temp_rgb.g;							_fb->bg_blue = temp_rgb.b;




		temp_hsv.h = _fb->text_color_hue;					temp_hsv.s = _fb->text_color_saturation;			temp_hsv.v = _fb->text_color_value;
		temp_rgb = EMath::hsv2rgb(temp_hsv);
		_fb->text_color_red = temp_rgb.r;					_fb->text_color_green = temp_rgb.g;					_fb->text_color_blue = temp_rgb.b;





		temp_hsv.h = _fb->rama_hue;							temp_hsv.s = _fb->rama_saturation;					temp_hsv.v = _fb->rama_value;
		temp_rgb = EMath::hsv2rgb(temp_hsv);
		_fb->rama_red = temp_rgb.r;							_fb->rama_green = temp_rgb.g;						_fb->rama_blue = temp_rgb.b;
	}

