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
//#include "EButtonCheck.h"

#include "ExplicitGroup.h"
#include "BaseClass.h"
#include "FilterBlockSeparator.h"
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

			
		}
		else
		{
			
			base_filter_condition_list.push_back(NULL);
		}

		if (_button_type != Enums::ButtonType::BUTTON_NONE)
		{
			EButton* but=NULL;

			if (_button_type!=Enums::ButtonType::BUTTON_RARITY)
			{
				if
				(
					(_button_type == Enums::ButtonType::BUTTON_SOCKETS_GROUP_COLORS_AND_LINKS)
					||
					(_button_type == Enums::ButtonType::BUTTON_SOCKETS_COLORS_AND_COUNT)
				)
				{ but = new EButtonSocketGroup(0, 0, 130, 17, _button_type); }
				
				else
				if
				(
					(_button_type == Enums::ButtonType::BUTTON_SHAPER_ITEM) ||
					(_button_type == Enums::ButtonType::BUTTON_ELDER_ITEM) ||

					(_button_type == Enums::ButtonType::BUTTON_SHAPER_MAP) ||
					(_button_type == Enums::ButtonType::BUTTON_ELDER_MAP) ||

					(_button_type == Enums::ButtonType::BUTTON_CORRUPTION) ||
					(_button_type == Enums::ButtonType::BUTTON_FRACTURED) ||
					(_button_type == Enums::ButtonType::BUTTON_SYNTHESISED) ||
					(_button_type == Enums::ButtonType::BUTTON_IDENTIFIED) ||
					(_button_type == Enums::ButtonType::BUTTON_ANY_ENCHANTMENT)||
					(_button_type == Enums::ButtonType::BUTTON_BLIGHTED)||
					(_button_type == Enums::ButtonType::BUTTON_MIRRORED_ITEM)
				)
				{
					
					but = new EButtonCheck(0, 0, 20, 20, _button_type);
				}
				else
				{
					if
					(
						(_button_type != Enums::ButtonType::BUTTON_OR_ELDER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_OR_SHAPER_ITEM) &&

						(_button_type != Enums::ButtonType::BUTTON_OR_HUNTER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_OR_REDEEMER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_OR_CRUSADER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_OR_WARLORD_ITEM) &&

						(_button_type != Enums::ButtonType::BUTTON_AND_ELDER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_AND_HUNTER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_AND_REDEEMER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_AND_CRUSADER_ITEM) &&
						(_button_type != Enums::ButtonType::BUTTON_AND_WARLORD_ITEM)
					)
					{but = new EButtonInputBaseData(0, 0, 65, 17, _button_type); but->input_auto_clear_text = true;}
					else
					{but = NULL; }
				}
			}
			else
			{
				if (_button_type == Enums::ButtonType::BUTTON_RARITY) { but = new EButtonDropRarity(0, 0, 65, 17, _button_type);}
				//if (_button_type == Enums::ButtonType::BUTTON_SOCKET_GROUP) { but = new EButtonDropRarity(0, 0, 16, 17, _button_type);}
			}

			if (but != NULL)
			{
				but->master_block = this;
				but->master_window = StaticData::window_filter_block;
				but->data_id = _id;

				
			}

			base_filter_buttons.push_back(but);
			
		}
		else
		{
			base_filter_buttons.push_back(NULL);
		}

		base_filter_data_active.push_back(false);
		base_filter_data_bool.push_back(true);

		EButton* but_remove = new EButtonRemove(0, 0, 19, 19, Enums::ButtonType::BUTTON_REMOVE_BASE_DATA);
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
		button_plus->is_full_equal_mode = false;
	
		button_plus->can_be_removed = false;

		button_list.push_back(button_plus);



		button_plus_equal = new EButtonFilterItem(0, 0, 45, 45);
		button_plus_equal->gabarite = DefaultGabarite::gabarite_plus_equal;

		button_plus_equal->master_block = this;
		button_plus_equal->master_window = StaticData::window_filter_block;

		button_plus_equal->master_position = Enums::FILTER_BLOCK;
		button_plus_equal->is_plus = true;
		button_plus_equal->is_full_equal_mode = true;

		button_plus_equal->can_be_removed = false;

		button_list.push_back(button_plus_equal);


		/*
		button_service = new EButtonService(0, 0, 45, 45,Enums::ButtonType::BUTTON_FILTER_BLOCK_TO_CONSOLE);
		button_service->master_block = this;
		button_service->master_window = StaticData::window_filter_block;
		button_service->gabarite = DefaultGabarite::gabarite_undefined;*/

		EButton*
		but = new EButtonService(-155.0f - right_side_buttons_offset ,50.0f,30.0f,30.0f,Enums::ButtonType::BUTTON_SYS_VISUAL_MODE);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);
		

		but = new EButtonService(-155.0f - right_side_buttons_offset, 9.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_SYS_PLAY_SOUND);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		sound_button_link = but;
		button_list.push_back(but);
		


		button_add_new_base_data = new EButtonPlusWide(0, 0, 19, 19,Enums::ButtonType::BUTTON_OPEN_BASE_DATA_WINDOW);

		button_add_new_base_data->master_block = this;
		button_add_new_base_data->master_window = StaticData::window_filter_block;

		button_list.push_back(button_add_new_base_data);
		//button_add_new_base_data->description_text = "Добавить новое свойство блока (редкость, гнёзда, уровень и т.д.)";




		button_add_new_EPC = new EButtonPlusWide(0, 0, 19, 19, Enums::ButtonType::BUTTON_OPEN_EXPLICIT_PROPHECY_CLASS_WINDOW);
		button_add_new_EPC->master_block = this;
		button_add_new_EPC->master_window = StaticData::window_filter_block;
		button_list.push_back(button_add_new_EPC);
		//button_add_new_EPC->description_text = "Добавить новое свойство блока (класс, аффиксы, пророчества, название предмета)";


		
		add_base_buttons("Редкость",			Enums::ButtonType::BUTTON_CONDITION_RARITY,			Enums::ButtonType::BUTTON_RARITY,					false,	Enums::BoolData::BOOL_RARITY);//0
		add_base_buttons("Уровень",				Enums::ButtonType::BUTTON_CONDITION_ITEM_LEVEL,		Enums::ButtonType::BUTTON_ITEM_LEVEL,				false,	Enums::BoolData::BOOL_ITEM_LEVEL);//1
		add_base_buttons("Треб. уровень",		Enums::ButtonType::BUTTON_CONDITION_DROP_LEVEL,		Enums::ButtonType::BUTTON_DROP_LEVEL,				false,	Enums::BoolData::BOOL_DROP_LEVEL);//2
		add_base_buttons("Уровень области",		Enums::ButtonType::BUTTON_CONDITION_AREA_LEVEL,		Enums::ButtonType::BUTTON_AREA_LEVEL,				false,	Enums::BoolData::BOOL_AREA_LEVEL);//3

		add_base_buttons("Сокеты",				Enums::ButtonType::BUTTON_CONDITION_SOCKETS,		Enums::ButtonType::BUTTON_SOCKETS_COLORS_AND_COUNT,	true,	Enums::BoolData::BOOL_SOCKETS);//4
		add_base_buttons("Связи",				Enums::ButtonType::BUTTON_CONDITION_LINKS,			Enums::ButtonType::BUTTON_LINKS,					false,	Enums::BoolData::BOOL_LINKS);//5
		add_base_buttons("Цвета гнёзд",			Enums::ButtonType::BUTTON_CONDITION_SOCKET_GROUP,	Enums::ButtonType::BUTTON_SOCKETS_GROUP_COLORS_AND_LINKS,				false,	Enums::BoolData::BOOL_SOCKET_GROUP);//6
																																								
		add_base_buttons("Качество",			Enums::ButtonType::BUTTON_CONDITION_QUALITY,		Enums::ButtonType::BUTTON_QUALITY,					true,	Enums::BoolData::BOOL_QUALITY);//7
		add_base_buttons("Ур. камня",			Enums::ButtonType::BUTTON_CONDITION_GEM_LEVEL,		Enums::ButtonType::BUTTON_GEM_LEVEL,				false,	Enums::BoolData::BOOL_GEM_LEVEL);//8
																																								
		add_base_buttons("Тир карты",			Enums::ButtonType::BUTTON_CONDITION_MAP_TIER,		Enums::ButtonType::BUTTON_MAP_TIER,					true,	Enums::BoolData::BOOL_MAP_TIER);//9
		add_base_buttons("Шейпер карта",		Enums::ButtonType::BUTTON_CONDITION_MAP_TIER,		Enums::ButtonType::BUTTON_SHAPER_MAP,				false,	Enums::BoolData::BOOL_SHAPER_MAP);//10
		add_base_buttons("Карта древнего",		Enums::ButtonType::BUTTON_CONDITION_MAP_TIER,		Enums::ButtonType::BUTTON_ELDER_MAP,				false,	Enums::BoolData::BOOL_ELDER_MAP);//11
																																								
		add_base_buttons("Ширина",				Enums::ButtonType::BUTTON_CONDITION_WIDTH,			Enums::ButtonType::BUTTON_WIDTH,					true,	Enums::BoolData::BOOL_WIDTH);//12
		add_base_buttons("Высота",				Enums::ButtonType::BUTTON_CONDITION_HEIGHT,			Enums::ButtonType::BUTTON_HEIGHT,					false,	Enums::BoolData::BOOL_HEIGHT);//13
		add_base_buttons("Количество",			Enums::ButtonType::BUTTON_CONDITION_STACK_SIZE,		Enums::ButtonType::BUTTON_STACK_SIZE,				false,	Enums::BoolData::BOOL_STACK_SIZE);//14																																			
		add_base_buttons("Осквернённый",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_CORRUPTION,				false,	Enums::BoolData::BOOL_CORRUPTION);//15
		
		add_base_buttons("(и) Пр. шейпера",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_AND_SHAPER_ITEM,			true,	Enums::BoolData::BOOL_AND_SHAPER);//16
		add_base_buttons("(или) Пр. шейпера",	Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_OR_SHAPER_ITEM,			false,	Enums::BoolData::BOOL_OR_SHAPER);//17
		
		add_base_buttons("(и) Пр. элдера",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_AND_ELDER_ITEM,			true,	Enums::BoolData::BOOL_AND_ELDER);//18
		add_base_buttons("(или) Пр. элдера",	Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_OR_ELDER_ITEM,			false,	Enums::BoolData::BOOL_OR_ELDER);//19
		
		add_base_buttons("(и) Пр. крестоносца",		Enums::ButtonType::BUTTON_NONE,					Enums::ButtonType::BUTTON_AND_CRUSADER_ITEM,		true,	Enums::BoolData::BOOL_AND_CRUSADER);//20
		add_base_buttons("(или) Пр. крестоносца",	Enums::ButtonType::BUTTON_NONE,					Enums::ButtonType::BUTTON_OR_CRUSADER_ITEM,			false,	Enums::BoolData::BOOL_OR_CRUSADER);//21
		
		add_base_buttons("(и) Пр. redemeer",		Enums::ButtonType::BUTTON_NONE,					Enums::ButtonType::BUTTON_AND_REDEEMER_ITEM,		true,	Enums::BoolData::BOOL_AND_REDEEMER);//22
		add_base_buttons("(или) Пр. redemeer",	Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_OR_REDEEMER_ITEM,			false,	Enums::BoolData::BOOL_OR_REDEEMER);//23
		
		add_base_buttons("(и) Пр. охотника",		Enums::ButtonType::BUTTON_NONE,					Enums::ButtonType::BUTTON_AND_HUNTER_ITEM,			true,	Enums::BoolData::BOOL_AND_HUNTER);//24
		add_base_buttons("(или) Пр. охотника",	Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_OR_HUNTER_ITEM,			false,	Enums::BoolData::BOOL_OR_HUNTER);//25
		
		add_base_buttons("(и) Пр. воеводы",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_AND_WARLORD_ITEM,			true,	Enums::BoolData::BOOL_AND_WARLORD);//26
		add_base_buttons("(или) Пр. воеводы",	Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_OR_WARLORD_ITEM,			false,	Enums::BoolData::BOOL_OR_WARLORD);//27

		add_base_buttons("Синтезир.",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_SYNTHESISED,				true,	Enums::BoolData::BOOL_SYNTHESISED);//28
		add_base_buttons("Разбитый",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_FRACTURED,				false,	Enums::BoolData::BOOL_FRACTURED);//29
		add_base_buttons("Зачарование",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_ANY_ENCHANTMENT,			false,	Enums::BoolData::BOOL_ANY_ENCHANTMENT);//30
		add_base_buttons("Опознанный",			Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_IDENTIFIED,				false,	Enums::BoolData::BOOL_IDENTIFIED);//31
		add_base_buttons("Зараж. карта",		Enums::ButtonType::BUTTON_NONE,						Enums::ButtonType::BUTTON_BLIGHTED,					false,	Enums::BoolData::BOOL_BLIGHTED);//32

		add_base_buttons("Пр. Шейпера",		Enums::ButtonType::BUTTON_NONE,							Enums::ButtonType::BUTTON_SHAPER_ITEM,				true,	Enums::BoolData::BOOL_SHAPER);//33
		add_base_buttons("Пр. Древнего",	Enums::ButtonType::BUTTON_NONE,							Enums::ButtonType::BUTTON_ELDER_ITEM,				false,	Enums::BoolData::BOOL_ELDER);//34

		add_base_buttons("Оскв. свойства",	Enums::ButtonType::BUTTON_CONDITION_CORRUPTION_IMPLICITES,	Enums::ButtonType::BUTTON_CORRUPTION_IMPLICITES,	true,	Enums::BoolData::BOOL_CORRUPTION_IMPLICITES);//35
		add_base_buttons("Отражённый",		Enums::ButtonType::BUTTON_NONE,								Enums::ButtonType::BUTTON_MIRRORED_ITEM,			false,	Enums::BoolData::BOOL_MIRRORED_ITEM);//36
		
		
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

			EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST);
			explicit_button->text = "+";
			explicit_button->master_block = this;
			explicit_button->master_window = StaticData::window_filter_block;

			explicit_button->button_size_x = EFont::get_width(EFont::active_font, "+") + 5.0f;
			explicit_button->button_min_size_x = explicit_button->button_size_x;

			explicit_button->can_be_removed = false;
			explicit_button->have_input_mode = false;
			explicit_button->is_plus = true;
			explicit_button->is_active = false;
			explicit_button->data_id = i;


			ex->button_add = explicit_button;
			button_list.push_back(explicit_button);

			



		}

		for (int i = 0; i < 5; i++)
		{
			EButtonCheck* but = new EButtonCheck(-150.0f + 20.0f * i, -5.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_CHECK_AUTOGEN);
			but->master_window = StaticData::window_filter_block;
			but->master_block = this;

			but->data_id = i;

			but->position_mode_x = Enums::PositionMode::RIGHT;
			but->position_mode_y = Enums::PositionMode::UP;

			autogen_button_link.push_back(but);
			button_list.push_back(but);
		}

		plus_class_button_link = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
		plus_class_button_link->text = "+";
		plus_class_button_link->master_block = this;
		plus_class_button_link->master_window = StaticData::window_filter_block;

		plus_class_button_link->button_size_x = EFont::get_width(EFont::active_font, "+") + 5.0f;
		plus_class_button_link->button_min_size_x = plus_class_button_link->button_size_x;


		plus_class_button_link->can_be_removed = false;
		plus_class_button_link->have_input_mode = false;
		plus_class_button_link->is_plus = true;
		plus_class_button_link->is_active = false;
	

		button_list.push_back(plus_class_button_link);



		plus_prophecy_button_link = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST);
		plus_prophecy_button_link->text = "+";
		plus_prophecy_button_link->master_block = this;
		plus_prophecy_button_link->master_window = StaticData::window_filter_block;

		plus_prophecy_button_link->button_size_x = EFont::get_width(EFont::active_font, "+") + 5.0f;
		plus_prophecy_button_link->button_min_size_x = plus_prophecy_button_link->button_size_x;

		plus_prophecy_button_link->can_be_removed = false;
		plus_prophecy_button_link->have_input_mode = false;
		plus_prophecy_button_link->is_plus = true;
		plus_prophecy_button_link->is_active = false;

		button_list.push_back(plus_prophecy_button_link);



		plus_enchantment_button_link = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST);
		plus_enchantment_button_link->text = "+";
		plus_enchantment_button_link->master_block = this;
		plus_enchantment_button_link->master_window = StaticData::window_filter_block;
		
		plus_enchantment_button_link->button_size_x = EFont::get_width(EFont::active_font, "+") + 5.0f;
		plus_enchantment_button_link->button_min_size_x = plus_prophecy_button_link->button_size_x;
		
		plus_enchantment_button_link->can_be_removed = false;
		plus_enchantment_button_link->have_input_mode = false;
		plus_enchantment_button_link->is_plus = true;
		plus_enchantment_button_link->is_active = false;

		button_list.push_back(plus_enchantment_button_link);




		
		remove_base_class_button = new EButtonRemove(0, 0, 17, 17, Enums::ButtonType::BUTTON_REMOVE_BASE_CLASS);

		remove_base_class_button->master_block = this;
		remove_base_class_button->master_window = StaticData::window_filter_block;
		remove_base_class_button->is_active = false;

		button_list.push_back(remove_base_class_button);



		remove_prophecy_button = new EButtonRemove(0, 0, 17, 17, Enums::ButtonType::BUTTON_REMOVE_PROPHECY);

		remove_prophecy_button->master_block = this;
		remove_prophecy_button->master_window = StaticData::window_filter_block;
		remove_prophecy_button->is_active = false;

		button_list.push_back(remove_prophecy_button);


		remove_enchantment_button = new EButtonRemove(0, 0, 17, 17, Enums::ButtonType::BUTTON_REMOVE_ENCHANTEMENT);

		remove_enchantment_button->master_block = this;
		remove_enchantment_button->master_window = StaticData::window_filter_block;
		remove_enchantment_button->is_active = false;

		button_list.push_back(remove_enchantment_button);

		but = new EButtonService(-150.0f, 45.0f - 20.0f * 0.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_SHOW_HIDE);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);



		but = new EButtonService(-5.0f, 45.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_UP);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonService(-5.0f, 25.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_PLUS_NEW_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonService(-5.0f, 5.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_DOWN);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);


		but = new EButtonService(-130.0f, 45.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_CUT_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonService(-110.0f, 45.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_CLONE_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonService(-90.0f, 45.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_ADD_SEPARATOR_TO_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonService(-70.0f, 45.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_SET_BLOCK_CONTINUE);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);
		link_to_continue_button = but;



		but = new EButtonService(-50.0f, 45.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_REMOVE_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		button_list.push_back(but);

		but = new EButtonText(0.0f, 0.0f, 400.0f, 60.0f, Enums::ButtonType::BUTTON_CANCEL_REMOVE_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		but->is_active = false;
		link_to_cancel_remove_button = but;
		//button_list.push_back(but);
		but->bg_color = EColorCollection::GREEN;

		random_bg_offset_y = rand() % 1080;



		but = new EButtonService(0.0f, 27.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_SEPARATOR_COLLAPSE);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		but->is_active = false;
		but->bg_color = EColorCollection::DARK_GRAY;
		but->text_color = EColorCollection::YELLOW;
		but->gabarite = DefaultGabarite::gabarite_button_collapse;
		but->have_input_mode = false;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::UP;
		but->master_position = Enums::PositionMaster::FILTER_BLOCK;
		link_to_header_collapse_separator = but;
		button_list.push_back(but);
		header_button_list.push_back(but);


		but = new EButtonService(22.0f, 27.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_DISABLE_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		but->is_active = false;
		but->bg_color = EColorCollection::DARK_GRAY;
		but->text_color = EColorCollection::YELLOW;
		but->gabarite = DefaultGabarite::gabarite_button_disable_block;
		but->have_input_mode = false;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::UP;
		but->master_position = Enums::PositionMaster::FILTER_BLOCK;
		button_list.push_back(but);
		header_button_list.push_back(but);

		but = new EButtonService(42.0f, 27.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_ENABLE_FILTER_BLOCK);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		but->is_active = false;
		but->bg_color = EColorCollection::DARK_GRAY;
		but->text_color = EColorCollection::YELLOW;
		but->gabarite = DefaultGabarite::gabarite_button_enable_block;
		but->have_input_mode = false;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::UP;
		but->master_position = Enums::PositionMaster::FILTER_BLOCK;
		button_list.push_back(but);
		header_button_list.push_back(but);

		but = new EButtonService(65.0f, 27.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_REMOVE_SEPARATOR);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		but->is_active = false;
		but->bg_color = EColorCollection::DARK_GRAY;
		but->text_color = EColorCollection::YELLOW;
		but->gabarite = DefaultGabarite::gabarite_remove_block;
		but->have_input_mode = false;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::UP;
		but->master_position = Enums::PositionMaster::FILTER_BLOCK;
		link_to_header_destroy_separator = but;
		button_list.push_back(but);
		header_button_list.push_back(but);

		but = new EButtonText(90.0f, 27.0f, 777.0f, 20.0f, Enums::ButtonType::BUTTON_HEADER_SEPARATOR);
		but->master_block = this;
		but->master_window = StaticData::window_filter_block;
		but->is_active = false;
		but->bg_color = EColorCollection::DARK_GRAY;
		but->text_color = EColorCollection::YELLOW;
		but->rama_color = EColorCollection::YELLOW;
		but->rama_thikness = 3.0f;
		but->have_input_mode = true;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::UP;
		but->master_position = Enums::PositionMaster::FILTER_BLOCK;
		link_to_header_separator = but;
		but->hint_color = EColorCollection::GRAY;
		button_list.push_back(but);
		header_button_list.push_back(but);
	}

	FilterBlock::~FilterBlock()
	{
		for (EButton* b : button_list)
		{
			b->text = "";
			b->description_text = "";

			delete b;
		}
	}

	void FilterBlock::remove_button_from_list(std::vector<EButton*> _v)
	{
		for (int i = 0; i < _v.size(); i++)
		{
			if (_v.at(i)->need_remove)
			{
				_v.erase(_v.begin() + i);
				i--;
			}
		}
	}

	void FilterBlock::update(float _d)
	{
		if (remove_timer > 0)
		{
			remove_timer -= _d;

			if (remove_timer <= 0)
			{
				need_remove = true;
			}
		}

		if (remove_timer < 0)
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->update(_d);
		}

		if (remove_timer < 0)
		{
			for (EButton* b : button_list) { if (b->is_active) { b->update(_d); } }
		}


		//button_plus->update(_d);
		
		//button_service->update(_d);
		//remove_button_from_list(filter_block_items_button_list);
		//remove_button_from_list(filter_block_items_button_list);
		//remove_button_from_list(button_list);
		if (remove_timer < 0)
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			if (filter_block_items_button_list.at(i)->need_remove)
			{
				filter_block_items_button_list.erase(filter_block_items_button_list.begin()+i);
				i--;
			}
		}

		if (remove_timer < 0)
		for (int i = 0; i < button_list.size(); i++)
		{
			if (button_list.at(i)->need_remove)
			{
				button_list.erase(button_list.begin() + i);
				i--;
			}
		}

		if (remove_timer < 0)
		for (int i = 0; i < base_class_list.size(); i++)
		{
			if (base_class_list.at(i)->need_remove)
			{
				base_class_list.erase(base_class_list.begin() + i);
				i--;
			}
		}

		if (remove_timer < 0)
		for (int i = 0; i < prophecy_list.size(); i++)
		{
			if (prophecy_list.at(i)->need_remove)
			{
				prophecy_list.erase(prophecy_list.begin() + i);
				i--;
			}
		}

		if (remove_timer < 0)
			for (int i = 0; i < enchantment_list.size(); i++)
			{
				if (enchantment_list.at(i)->need_remove)
				{
					enchantment_list.erase(enchantment_list.begin() + i);
					i--;
				}
			}

		if (remove_timer < 0)
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

			float data_x = x + 185;
			float data_y = 25;

			if (remove_timer < 0)
			{
				for (int i = 0; i < base_filter_data_active.size(); i++)
				if (base_filter_data_active.at(i))
				{
					if (base_filter_condition_list.at(i) != NULL)
					{
						base_filter_condition_list.at(i)->button_x = data_x;
						base_filter_condition_list.at(i)->button_y = size_y - data_y;

						base_filter_condition_list.at(i)->update(_d);

						if (base_filter_buttons.at(i) != NULL)
						{
							base_filter_buttons.at(i)->button_x = data_x + 35;
							base_filter_buttons.at(i)->button_y = size_y - data_y;
						}
					}
					else
					{
						if (base_filter_buttons.at(i) != NULL)
						{
							base_filter_buttons.at(i)->button_x = data_x;
							base_filter_buttons.at(i)->button_y = size_y - data_y;
						}
					}



					base_filter_data_remove_buttons.at(i)->button_x = x;
					base_filter_data_remove_buttons.at(i)->button_y = size_y - data_y;



					base_filter_data_remove_buttons.at(i)->update(_d);


					if (base_filter_buttons.at(i) != NULL)
					{base_filter_buttons.at(i)->update(_d);}

					data_y += _data_y_offset;
				}
			}

			button_add_new_base_data->button_x = x;
			button_add_new_base_data->button_y = size_y - data_y;

			//button_add_new_base_data->update(_d);
			if (highlight_time > 0) { highlight_time -= _d; }

			 ray_cooldown -= _d;

			 if (ray_cooldown <= 0)
			 {
				 ray_cooldown += 0.33f;

				 ray_semitransarent = !ray_semitransarent;
			 }

			if (link_to_cancel_remove_button->is_active)
			{link_to_cancel_remove_button->update(_d);}
	}

	void FilterBlock::draw(Batcher* _batch)
	{
		max_h = 75.0f;


		if (is_show) { _batch->setcolor_255(210, 210, 210, 100); }
		else { _batch->setcolor_255(64, 32, 16, 100); }

		if (disabled)
		{
			_batch->setcolor_alpha(EColorCollection::RED, 0.55f);
		}

		if (random_bg_offset_y + size_y > 1000.0f)
		{
			random_bg_offset_y -= random_bg_offset_y + size_y - 1000.0f;
		}

		if (random_bg_offset_y > 800) { random_bg_offset_y = 800; }
		if (random_bg_offset_y < 0) { random_bg_offset_y = 0; }

		_batch->draw_rect_gabarite_custom_uv(x, y, size_x, size_y, DefaultGabarite::gabarite_wood_bg, 0, random_bg_offset_y, size_x, random_bg_offset_y + size_y);

		if
		(
			(base_filter_data_bool.at(Enums::BoolData::BOOL_AND_SHAPER))
			&&
			(base_filter_data_active.at(Enums::BoolData::BOOL_AND_SHAPER))
		)
		{
			if (is_show) { _batch->setcolor_255(180, 180, 180, 180); } else { _batch->setcolor_255(150, 50, 25, 100); }

			_batch->draw_rect_gabarite_custom_uv(x, y, size_x, size_y, DefaultGabarite::gabarite_shaper_bg, x / 2.0f, y / 2.0f, (x + size_x) / 2.0f, (y + size_y) / 2.0f);

			
		}
		else
		if
		(
			(base_filter_data_bool.at(Enums::BoolData::BOOL_AND_ELDER))
			&&
			(base_filter_data_active.at(Enums::BoolData::BOOL_AND_ELDER))
		)
		{
			if (is_show) {_batch->setcolor_255(255, 255, 255, 200);} else {_batch->setcolor_255(200, 150, 100, 150);}

			float move_x = (1000.0f - size_x) / 2.0f;
			if (move_x < 0) { move_x = 0; }

			float move_y = (300.0f - size_y) / 2.0f;
			if (move_y < 0) { move_y = 0; }

			float orig_size_x = size_x;
			if (orig_size_x > 1000.0f) { orig_size_x = 1000.0f; }

			float orig_size_y = size_y;
			if (orig_size_y > 300.0f) { orig_size_y = 300.0f; }

			float offset_x = (size_x - orig_size_x) / 2.0f;
			float offset_y = (size_y - orig_size_y) / 2.0f;

			_batch->draw_rect_gabarite_custom_uv(x + offset_x, y + offset_y, orig_size_x, orig_size_y, DefaultGabarite::gabarite_elder_bg, move_x, move_y, 1000.0f - move_x, 300.0f - move_y);
		}

		if ((is_continue) && (!disabled))
		{
			_batch->setcolor_alpha(EColorCollection::CYAN, 0.33f);
			_batch->draw_rect_with_uv(x, y, size_x, size_y, DefaultGabarite::gabarite_white);
		}

		_batch->setcolor_alpha(EColorCollection::BLACK, 0.25f);
		_batch->draw_rama(x + 5.0f, y + 5.0f, 355.0f, size_y - 10.0f, 3.0f, DefaultGabarite::gabarite_white);

		
		

		





		
			//shaper bg (moved to up)
	

		if (highlight_time > 0)
		{
			_batch->setcolor_alpha(EColorCollection::GREEN, highlight_time / 0.5f);
			_batch->draw_rect_with_uv(x, y, size_x, size_y, DefaultGabarite::gabarite_white);
		}



		EFont::active_font->scale = font_size / 32.0f;

		float text_w = EFont::get_width(EFont::active_font, "Just a Text");
		float text_h = 12.0f * EFont::active_font->scale;

		float rx = text_w + 10.0f;
		float ry = text_h + 10.0f;

		_batch->setcolor(EColorCollection::WHITE);
		_batch->draw_rect_with_uv(x + size_x - 145.0f - right_side_buttons_offset, y + 7.0f, 145.0f, 28.0f, DefaultGabarite::gabarite_bg_noise);

		_batch->setcolor_255(bg_red, bg_green, bg_blue, bg_alpha / 2.55f);
		_batch->draw_rect_with_uv(x + size_x - 145.0f + (145.0 - rx) / 2.0f - right_side_buttons_offset, y + 10.0f, rx, ry, DefaultGabarite::gabarite_white);

		_batch->setcolor_255(text_color_red, text_color_green, text_color_blue, text_color_alpha);
		//_font->x_adding = 0;

		EFont::active_font->set_align_once(Enums::PositionMode::LEFT);
		EFont::active_font->draw(_batch, "Just a Text", x + size_x - 140.0f + (145.0 - rx) / 2.0f - right_side_buttons_offset, y + 15.0f);
		EFont::active_font->scale = 1.0f;



		_batch->setcolor_255(rama_red, rama_green, rama_blue, rama_alpha / 2.55f);
		_batch->draw_rama(x + size_x - 145.0f + (145.0 - rx) / 2.0f - right_side_buttons_offset, y + 10.0f, rx, ry, 3.0f, DefaultGabarite::gabarite_white);


		//ray color
		if (is_ray)
		{
			int transparent = 100;

			if ((ray_semitransarent) && (ray_is_temp)) { transparent = 33; }

			if (ray_color == Enums::GameColors::RAY_RED) { _batch->setcolor_255(255, 0, 0, transparent); }
			if (ray_color == Enums::GameColors::RAY_GREEN) { _batch->setcolor_255(0, 255, 0, transparent); }
			if (ray_color == Enums::GameColors::RAY_BLUE) { _batch->setcolor_255(0, 0, 255, transparent); }
			if (ray_color == Enums::GameColors::RAY_BROWN) { _batch->setcolor_255(255, 128, 64, transparent); }
			if (ray_color == Enums::GameColors::RAY_WHITE) { _batch->setcolor_255(255, 255, 255, transparent); }
			if (ray_color == Enums::GameColors::RAY_YELLOW) { _batch->setcolor_255(255, 255, 0, transparent); }

			if (ray_color == Enums::GameColors::RAY_CYAN) { _batch->setcolor_255(0, 255, 255, transparent); }
			if (ray_color == Enums::GameColors::RAY_GREY) { _batch->setcolor_255(128, 128, 128, transparent); }
			if (ray_color == Enums::GameColors::RAY_ORANGE) { _batch->setcolor_255(255, 128, 0, transparent); }
			if (ray_color == Enums::GameColors::RAY_PINK) { _batch->setcolor_255(255, 128, 255, transparent); }
			if (ray_color == Enums::GameColors::RAY_PURPLE) { _batch->setcolor_255(255, 0, 128, transparent); }


			//draw ray
			_batch->draw_rect_with_uv(x + size_x - 213.0f - right_side_buttons_offset, y + 5.0f, 30, 60, DefaultGabarite::gabarite_ray_icon);
		}
		//minimap icon
		if (is_minimap_icon)
		{
			float siz = 1.0 / (minimap_icon_size * 0.5f + 1.0);

			_batch->setcolor(EColorCollection::MINIMAP_ICON_COLOR[minimap_icon_color]);

			_batch->draw_rect_with_uv(x + size_x - 240.0f - right_side_buttons_offset, y + 10.0f, 35.0f * siz, 35.0f * siz, DefaultGabarite::gabarite_minimap_icon[minimap_icon_shape]);
		}

		float temp_pos_x = start_position_draw_x;
		float temp_pos_y = 10;


		button_h_max = 0.0f;

		if (remove_timer == -100)
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->button_x = temp_pos_x;
			filter_block_items_button_list.at(i)->button_y = temp_pos_y;

			filter_block_items_button_list.at(i)->button_size_x = 45.0f;
			filter_block_items_button_list.at(i)->button_size_y = 45.0f;

			filter_block_items_button_list.at(i)->default_draw(_batch);
			filter_block_items_button_list.at(i)->additional_draw(_batch);
			//filter_block_items_button_list.at(i)->text_pass(EFont::font, _batch);

			if (filter_block_items_button_list.at(i)->gabarite != NULL)
			{
				temp_pos_x += filter_block_items_button_list.at(i)->button_size_x + 8;

				if (temp_pos_x + 53.0f > size_x - 300.0f)
				{
					temp_pos_x = start_position_draw_x;
					temp_pos_y += 53.0f;

					if (temp_pos_y + 105 > max_h) { max_h = temp_pos_y + 105; button_h_max = max_h; }
				}
			}
		}


		//max_h += 35;

		button_plus->button_x = temp_pos_x;
		button_plus->button_y = temp_pos_y;
		temp_pos_x += 53.0f;

		button_plus_equal->button_x = temp_pos_x;
		button_plus_equal->button_y = temp_pos_y;
		temp_pos_x += 53.0f;
		
		for (int i = 0; i < 25; i++)
		if (temp_pos_x + 53.0f < size_x - 260.0f)
		{
			_batch->setcolor_alpha(EColorCollection::BLACK, 0.25f);
			_batch->draw_rect_with_uv(x + temp_pos_x, y + temp_pos_y, 45.0f, 45.0f, DefaultGabarite::gabarite_white);

			temp_pos_x += 53.0f;
		}

		float ex_x = start_position_draw_x;
		float ex_y = -10;

		int close_button_id = 0;

		if (remove_timer < 0)
		for (ExplicitGroup* ex : explicit_list)
		{
			ex_x = start_position_draw_x;

			if (ex->is_active)
			{


				ex->button_close->button_x = ex_x;
				ex->button_close->button_y = ex_y;



				ex_x += 20;

				for (EButton* b : ex->button_list)
				{
					b->button_x = ex_x;
					b->button_y = ex_y;

					ex_x += b->button_size_x + 5;
					if (b->button_x + b->button_size_x > size_x - 270.0f)
					{
						ex_x = start_position_draw_x;
						ex_y -= 22.0f;
					}

				}

				ex->button_add->button_x = ex_x;
				ex->button_add->button_y = ex_y;

				_batch->setcolor_alpha(EColorCollection::CYAN, 0.125f);
				_batch->draw_rect_with_uv(ex->button_add->master_position_x, ex->button_add->master_position_y, size_x - ex->button_add->master_position_x - 270.0f, 20.0f, DefaultGabarite::gabarite_white);


				ex_y -= 30.0f;
				close_button_id++;
			}
		}



		ex_x = start_position_draw_x;


		if ((is_base_class_active) && ((remove_timer < 0)))
		{
			remove_base_class_button->button_x = ex_x;
			remove_base_class_button->button_y = ex_y;

			ex_x += 20;

			for (EButtonExplicit* b : base_class_list)
			{
				b->button_x = ex_x;
				b->button_y = ex_y;

				ex_x += b->button_size_x + 5;
				if (b->button_x + b->button_size_x > size_x - 270.0f)
				{
					ex_x = start_position_draw_x;
					ex_y -= 22.0f;
				}
			}

			plus_class_button_link->button_x = ex_x;
			plus_class_button_link->button_y = ex_y;

			_batch->setcolor_alpha		(EColorCollection::GREEN, 0.1f);
			_batch->draw_rect_with_uv(plus_class_button_link->master_position_x, plus_class_button_link->master_position_y, size_x - plus_class_button_link->master_position_x - 270.0f, 20.0f, DefaultGabarite::gabarite_white);


			ex_y -= 30.0f;
		}

		ex_x = start_position_draw_x;


		if ((is_prophecy_active) && (remove_timer < 0))
		{
			remove_prophecy_button->button_x = ex_x;
			remove_prophecy_button->button_y = ex_y;

			ex_x += 20;

			for (EButtonExplicit* b : prophecy_list)
			{
				b->button_x = ex_x;
				b->button_y = ex_y;

				ex_x += b->button_size_x + 5;
				if (b->button_x + b->button_size_x > size_x - 270.0f)
				{
					ex_x = start_position_draw_x;
					ex_y -= 22.0f;
				}
			}

			plus_prophecy_button_link->button_x = ex_x;
			plus_prophecy_button_link->button_y = ex_y;

			_batch->setcolor_alpha(EColorCollection::PINK, 0.15f);
			_batch->draw_rect_with_uv(plus_prophecy_button_link->master_position_x, plus_prophecy_button_link->master_position_y, size_x - plus_prophecy_button_link->master_position_x - 270.0f, 20.0f, DefaultGabarite::gabarite_white);

			ex_y -= 30.0f;
		}

		ex_x = start_position_draw_x;
		if ((is_enchantment_active) && (remove_timer < 0))
		{
			remove_enchantment_button->button_x = ex_x;
			remove_enchantment_button->button_y = ex_y;

			ex_x += 20;

			for (EButtonExplicit* b : enchantment_list)
			{
				b->button_x = ex_x;
				b->button_y = ex_y;

				ex_x += b->button_size_x + 5;
				if (b->button_x + b->button_size_x > size_x - 270.0f)
				{
					ex_x = start_position_draw_x;
					ex_y -= 22.0f;

					b->button_x = ex_x;
					b->button_y = ex_y;

					ex_x += b->button_size_x + 5;
				}
			}

			plus_enchantment_button_link->button_x = ex_x;
			plus_enchantment_button_link->button_y = ex_y;

			_batch->setcolor_alpha(EColorCollection::BLACK, 0.15f);
			_batch->draw_rect_with_uv(plus_enchantment_button_link->master_position_x, plus_enchantment_button_link->master_position_y, size_x - plus_enchantment_button_link->master_position_x - 270.0f, 20.0f, DefaultGabarite::gabarite_white);

			ex_y -= 30.0f;
		}

		button_add_new_EPC->button_x = start_position_draw_x;
		button_add_new_EPC->button_y = ex_y;
		max_h += 5;
		if (-ex_y > 0)
		{
			max_h += (-ex_y);
		}

		
		_batch->setcolor_alpha(EColorCollection::WHITE, 0.1f);
		_batch->draw_rect_with_uv(button_add_new_EPC->master_position_x, button_add_new_EPC->master_position_y, size_x - button_add_new_EPC->master_position_x -270.0f, 20.0f, DefaultGabarite::gabarite_white);




		//if (ex_y * -1.0f + 85.0f > max_h) { max_h = ex_y * -1.0f + 85.0f; }

		//button_service->draw(_batch);

		/*for (int i = 0; i < filter_flock_button_list.size(); i++)
		{
			filter_flock_button_list.at(i)->draw(_batch);
		}*/



		float data_x = x + 155;
		float data_y = 25;

		if (remove_timer < 0)
		for (int i = 0; i < base_filter_data_active.size(); i++)
		{
			if (base_filter_data_active.at(i))
			{
				_batch->setcolor_alpha(EColorCollection::BLACK, 0.8f);
				_batch->draw_rect_with_uv(data_x - 150, y + size_y - data_y - 3, 185, 21, DefaultGabarite::gabarite_white);

				EFont::active_font->align_x = Enums::RIGHT;
				_batch->setcolor(EColorCollection::GRAY);

				EFont::active_font->draw(_batch, base_filter_data_name.at(i), data_x + 30, y + size_y - data_y);
				
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

				if (base_filter_buttons.at(i) != NULL)
				{base_filter_buttons.at(i)->default_draw(_batch);}

				base_filter_data_remove_buttons.at(i)->default_draw(_batch);
				base_filter_data_remove_buttons.at(i)->additional_draw(_batch);

				_batch->setcolor_alpha(EColorCollection::BLACK, 0.17f);
				_batch->draw_rama(x + 5, y + size_y - data_y - 3, 185, 21, 1, DefaultGabarite::gabarite_white);
				
				data_y += _data_y_offset;
			}
		}



		if (remove_timer < 0)
		{
			for (EButton* b : button_list) { if (b->is_active) { b->default_draw(_batch); } }
		}

		EFont::active_font->align_x = Enums::LEFT;

		if (data_y > max_h) { max_h = data_y; }

		size_y = max_h;


		if (remove_timer > 0)
		{
			_batch->setcolor_alpha(EColorCollection::RED, 0.8);
			_batch->draw_rect_with_uv(x, y, size_x * (1.0f - remove_timer / 3.0f), size_y, DefaultGabarite::gabarite_white);
		}

		if (link_to_cancel_remove_button->is_active)
		{link_to_cancel_remove_button->default_draw(_batch);}

		_batch->setcolor_alpha(EColorCollection::WHITE, 0.35f);
		_batch->draw_rama(x, y, size_x, size_y, 3.0f, DefaultGabarite::gabarite_white);

		EFont::active_font->set_align_once(Enums::PositionMode::RIGHT);
		_batch->setcolor_alpha(EColorCollection::WHITE, 0.8f);
		EFont::active_font->draw(_batch, "#" + std::to_string(order_id), x + size_x -5.0f, y+size_y - 25.0f);
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

		if (remove_timer < 0)
		{for (EButton* b : button_list) { if (b->is_active) { b->text_pass(_batch); } }}




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
		



		/*
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->text_pass(_font,_batch);
		}*/

		if (remove_timer < 0)
		for (int i = 0; i < filter_block_items_button_list.size(); i++)
		{
			filter_block_items_button_list.at(i)->text_pass(_batch);
		}

		if (remove_timer < 0)
		for (int i = 0; i < base_filter_data_active.size(); i++)
		{
			if (base_filter_data_active.at(i))
			{
				if (base_filter_condition_list.at(i)!=NULL) { base_filter_condition_list.at(i)->text_pass(_batch); }

				if (base_filter_buttons.at(i) != NULL)
				{base_filter_buttons.at(i)->text_pass(_batch);}

				base_filter_data_remove_buttons.at(i)->text_pass(_batch);
			}
		}

		//button_service->text_pass(_batch);
		
		//EFont::font_arial->draw(_batch, std::to_string(y), x, y);
		if (link_to_cancel_remove_button->is_active)
		{link_to_cancel_remove_button->text_pass(_batch);}
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

		if ((!is_alert_sound)&&(!is_custom_alert_sound))
		{
			sound_button_link->deactivate();
		}
		else
		{
			sound_button_link->activate();
		}

		int autogen_id = 0;
		for (EButtonCheck* b : autogen_button_link)
		{
			b->change_state(autogen_include.at(autogen_id));
			autogen_id++;
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

	void FilterBlock::update_localisation()
	{
		base_filter_data_name.at(0) = EString::localize_it("base_data_text_rarity");
		base_filter_data_name.at(1) = EString::localize_it("base_data_text_level");//	"Уровень",
		base_filter_data_name.at(2) = EString::localize_it("base_data_text_req_level");
		base_filter_data_name.at(3) = EString::localize_it("base_data_text_area_level");

		base_filter_data_name.at(4) = EString::localize_it("base_data_text_sockets");
		base_filter_data_name.at(5) = EString::localize_it("base_data_text_links");
		base_filter_data_name.at(6) = EString::localize_it("base_data_text_sockets_colour");
		
		base_filter_data_name.at(7) = EString::localize_it("base_data_text_quality");
		base_filter_data_name.at(8) = EString::localize_it("base_data_text_gem_level");
		
		base_filter_data_name.at(9) = EString::localize_it("base_data_text_map_tier");
		base_filter_data_name.at(10) = EString::localize_it("base_data_text_shaper_map");
		base_filter_data_name.at(11) = EString::localize_it("base_data_text_elder_map");
		
		base_filter_data_name.at(12) = EString::localize_it("base_data_text_height");
		base_filter_data_name.at(13) = EString::localize_it("base_data_text_width");
		base_filter_data_name.at(14) = EString::localize_it("base_data_text_quantity");
		
		base_filter_data_name.at(15) = EString::localize_it("base_data_text_corrupted");

		base_filter_data_name.at(16) = EString::localize_it("base_data_text_and_shaper");
		base_filter_data_name.at(17) = EString::localize_it("base_data_text_or_shaper");

		base_filter_data_name.at(18) = EString::localize_it("base_data_text_and_elder");
		base_filter_data_name.at(19) = EString::localize_it("base_data_text_or_elder");

		base_filter_data_name.at(20) = EString::localize_it("base_data_text_and_crusader");
		base_filter_data_name.at(21) = EString::localize_it("base_data_text_or_crusader");

		base_filter_data_name.at(22) = EString::localize_it("base_data_text_and_redeemer");
		base_filter_data_name.at(23) = EString::localize_it("base_data_text_or_redeemer"); //крестоносца 23:52:40 15.12.2019

		base_filter_data_name.at(24) = EString::localize_it("base_data_text_and_hunter");
		base_filter_data_name.at(25) = EString::localize_it("base_data_text_or_hunter");

		base_filter_data_name.at(26) = EString::localize_it("base_data_text_and_warlord");
		base_filter_data_name.at(27) = EString::localize_it("base_data_text_or_warlord");

		base_filter_data_name.at(28) = EString::localize_it("base_data_text_synthesis");
		base_filter_data_name.at(29) = EString::localize_it("base_data_text_fractured");
		base_filter_data_name.at(30) = EString::localize_it("base_data_text_enchanted");
		base_filter_data_name.at(31) = EString::localize_it("base_data_text_identified");
		base_filter_data_name.at(32) = EString::localize_it("base_data_text_blighted");

		base_filter_data_name.at(33) = EString::localize_it("base_data_text_shaper_item");
		base_filter_data_name.at(34) = EString::localize_it("base_data_text_elder_item");

		base_filter_data_name.at(35) = EString::localize_it("base_data_text_corruption_implicites");
		base_filter_data_name.at(36) = EString::localize_it("base_data_text_mirrored_item");

		/*
		base_filter_data_name.at(26) = EString::localize_it("base_data_text_elder_item");
		base_filter_data_name.at(27) = EString::localize_it("base_data_text_elder_item");
		*/
		//base_filter_data_name.at(24) = EString::localize_it("base_data_text_blighted");

		link_to_cancel_remove_button->update_localisation();

		for (EButton* but : button_list)
		{
			but->update_localisation();
		}
	}

