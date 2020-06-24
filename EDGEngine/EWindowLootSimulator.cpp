
#include "EControl.h"
#include "Enums.h"

#include "StaticData.h"
#include "EWindowLootSimulator.h"
#include <time.h>
#include "EButtonFilterItem.h"
#include "EButtonAutogenLootSimulator.h"

int sockets_postition_x[] = { 0, 1, 1, 0, 0, 1 };
int sockets_postition_y[] = { 0, 0, 1, 1, 2, 2 };

float links_postition_x[] = { 26.0f, 52.0f, 26.0f, 14.0f, 26.0f};
float links_postition_y[] = { 12.0f, -16.0f, -28.0f, -56.0f, -69.0f};

EWindowLootSimulator::EWindowLootSimulator(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
{
	window_size_x = 1000.0f;
	window_size_y = 750.0f;

	relative_y = 50.0f;

	//relative_x = 16.0f;

	align_y = Enums::PositionMode::DOWN;

	bg_color->set_alpha(EColorCollection::GRAY, 0.75f);

	is_active = false;

	EButton* but = new EButtonText(15.0f, -15.0f, 220.0f, 20.0f, Enums::BUTTON_OPEN_PATTERN_WINDOW);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonService(240.0f, -15.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_REMOVE_LOOT_FROM_SIMULATOR);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonService(280.0f, -15.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_REFRESH_LOOT_SIMULATOR);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonService(320.0f, -15.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_CHANGE_BG_BRIGHT);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonService(355.0f, -15.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_CHANGE_BG_DARK);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonService(390.0f, -15.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_OPEN_MANUAL_LOOT_WINDOW);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonSlider(425.0f, -15.0f, 200.0f, 20.0f, Enums::ButtonType::SLIDER_LOOT_DROP_SIZE);
	but->master_window = this;
	button_list.push_back(but);
	

	link_to_autogen_drop_button = new EButtonAutogenLootSimulator(650.0f, -15.0f, 200.0f, 20.0f, Enums::ButtonType::BUTTON_CONDITION_AUTOGEN_LOOT_SIMULATOR);
	link_to_autogen_drop_button->master_window = this;
	button_list.push_back(link_to_autogen_drop_button);

	but = new EButtonText(860.0f, -15.0f, 50.0f, 20.0f, Enums::ButtonType::BUTTON_AREA_LEVEL_FOR_LOOT_SIMULATOR);
	but->master_window = this;
	button_list.push_back(but);
	but->text = std::to_string(area_level);
	//link_to_autogen_drop_button = but;
}

void EWindowLootSimulator::fill_random_pool(std::string _class, std::string _subclass, std::string _cost, std::string _category)
{


	for (DADItem* item : ItemList::item_list)
	{
		if
			(
			((EString::to_lower(_class) == EString::to_lower(item->base_class)) || (_class == "") || (EString::to_lower(_class) == "any"))
				&&
				((EString::to_lower(_subclass) == EString::to_lower(item->subcategory)) || (_subclass == "") || (EString::to_lower(_subclass) == "any"))
				&&
				((EString::to_lower(_cost) == EString::to_lower(item->cost_group)) || (_cost == "") || (EString::to_lower(_cost) == "any"))
				&&
				((EString::to_lower(_category) == EString::to_lower(item->category)) || (_category == "") || (EString::to_lower(_category) == "any"))
				)
		{
			random_item_pool.push_back(item);
		}
	}


}

void EWindowLootSimulator::update(float _d)
{
	drop_cooldown -= _d;

	if (drop_cooldown < 0)
	{
		drop_cooldown += 0.05f + (rand() % 10) / 100.0f;

		if (drop_count > 0)
		{
			//std::cout << std::endl;
			//std::cout << "try drop (" << loot_vector_id << ")" << std::endl;
			int selected = rand() % prepared_pattern_list.size();

			LootPatternItem* p = prepared_pattern_list.at(selected);
			LootItem* loot = new LootItem();
			//				loot->name = ItemList::item_list.at(rand() % ItemList::item_list.size())->item_name;


							//***************************ITEM NAME SECTION**************************************
							//**********************************************************************************
			loot->name = p->item_name;
			loot->data_name = p->item_base_name;

			loot->base_class = p->base_class;

			loot->is_shaper_map = p->shaped_map;
			loot->is_elder_map = p->elder_map;
			loot->is_blighted_map = p->blighted_map;
			loot->is_mirrored = p->mirrored;

			if (p->max_quality > 0)
			{
				if (p->max_quality > p->min_quality)
				{
					loot->quality = p->min_quality + (rand() % (p->max_quality - p->min_quality + 1));
				}
				else
				{
					loot->quality = p->max_quality;
				}

				if (loot->quality < 0) { loot->quality = 0; }
			}

			if ((p->corruption_chance > 0) && (rand() % 100 <= p->corruption_chance))
			{
				loot->corrupted = true;

				loot->corrupted_mods = (rand() % 3);
			}

			if ((p->mirrored_chance > 0) && (rand() % 100 <= p->mirrored_chance))
			{
				loot->is_mirrored = true;
			}

			if (p->max_gem_level > 0)
			{
				if (p->max_gem_level > p->min_gem_level)
				{
					loot->gem_level = p->min_gem_level + (rand() % (p->max_gem_level - p->min_gem_level + 1));
				}
				else
				{
					loot->gem_level = p->max_gem_level;
				}

				if (loot->gem_level < 0) { loot->gem_level = 0; }
			}

			//std::cout << "min sockets=" << p->min_sockets << std::endl;
			//std::cout << "max sockets=" << p->max_sockets << std::endl;
			if (p->max_sockets > 0)
			{
				if (p->max_sockets > p->min_sockets)
				{
					loot->sockets = p->min_sockets + (rand() % (p->max_sockets - p->min_sockets + 1));
				}
				else
				{
					loot->sockets = p->max_sockets;
				}

				if (loot->sockets < 0) { loot->sockets = 0; }
			}


			if (p->max_links > 0)
			{
				if (p->max_links > p->min_links)
				{
					loot->links = p->min_links + (rand() % (p->max_links - p->min_links + 1));
				}
				else
				{
					loot->links = p->max_links;
				}

				if (loot->links < 0) { loot->links = 0; }
				if (loot->links == 1) { loot->links = 2; }
				if (loot->links > loot->sockets) { loot->links = loot->sockets; }
			}

			if (p->max_map_tier > 0)
			{
				if (p->max_map_tier > p->min_map_tier)
				{
					loot->map_tier = p->min_map_tier + (rand() % (p->max_map_tier - p->min_map_tier + 1));
				}
				else
				{
					loot->map_tier = p->max_map_tier;
				}

				if (loot->map_tier < 0) { loot->map_tier = 0; }
				//if (loot->links > loot->sockets) { loot->links = loot->sockets; }
			}

			int random_red = -1;
			int random_green = -1;
			int random_blue = -1;
			int random_white = -1;

			float total_w = 0;
			
			std::vector <int> color_pool;

			loot->red_socket = 0;
			loot->green_socket = 0;
			loot->blue_socket = 0;
			loot->white_socket = 0;

			//if (p->red_weight + p->green_weight + p->blue_weight + p->white_weight > 0)
			{
				for (int i=0; i < loot->sockets; i++)
				{
					int max = 0;
					color_pool.clear();

					if (p->red_weight > 0)		{ random_red = rand() % p->red_weight;			if (random_red > max){max = random_red;} }
					if (p->green_weight > 0)	{ random_green = rand() % p->green_weight;		if (random_green > max){max = random_green;} }
					if (p->blue_weight > 0)		{ random_blue = rand() % p->blue_weight;		if (random_blue > max){max = random_blue;} }
					if (p->white_weight > 0)	{ random_white = rand() % p->white_weight;		if (random_white > max){max = random_white;} }

					if (random_red == max) { color_pool.push_back(0); }
					if (random_green == max) { color_pool.push_back(1); }
					if (random_blue == max) { color_pool.push_back(2); }
					if (random_white == max) { color_pool.push_back(3); }

					int selected_color = -1;

					if (color_pool.size() == 1) { selected_color = color_pool.at(0); }
					if (color_pool.size() > 1) { selected_color = color_pool.at(rand() % color_pool.size()); }

					if (selected_color == 0) { loot->red_socket++; loot->socket_color.push_back(EColorCollection::RED); }
					if (selected_color == 1) { loot->green_socket++; loot->socket_color.push_back(EColorCollection::GREEN);}
					if (selected_color == 2) { loot->blue_socket++; loot->socket_color.push_back(EColorCollection::BLUE);}
					if (selected_color == 3) { loot->white_socket++; loot->socket_color.push_back(EColorCollection::WHITE);}

					if (i < loot->links)
					{
						if (selected_color == 0) { loot->linked_red_socket++; }
						if (selected_color == 1) { loot->linked_green_socket++; }
						if (selected_color == 2) { loot->linked_blue_socket++; }
						if (selected_color == 3) { loot->linked_white_socket++; }
					}


				}
			}

			int random_shaper = 0;
			int random_elder = 0;
			int random_normal = 0;

			int max_value = 0;

			if (p->shaper_item_weight > 0) { random_shaper = rand() % p->shaper_item_weight; }
			if (p->elder_item_weight > 0) { random_elder = rand() % p->elder_item_weight; }
			if (p->normal_item_weight > 0) { random_normal = rand() % p->normal_item_weight; }

			if (random_shaper > max_value)	{	max_value = random_shaper;	}
			if (random_elder > max_value)	{	max_value = random_elder;	}
			if (random_normal > max_value)	{	max_value = random_normal;	}

			if (max_value == random_shaper) { loot->shaper_item = true;	}
			if (max_value == random_elder) { loot->elder_item = true;	}

			loot->enchantment = p->enchantment;
			loot->cluster_enchantment = p->cluster_enchantment;


			loot->prophecy = p->prophecy_name;

			if ((loot->prophecy == "%random%") && (EString::prophecy_list.size() > 0))
			{
				loot->prophecy = EString::prophecy_list.at(rand() % EString::prophecy_list.size())->base_name;
			}

			if (loot->prophecy != "")
			{
				loot->name = loot->prophecy;

				if (EString::active_localisation == Enums::RU)
				for (int i=0; i < EString::prophecy_list.size(); i++)
				{
					if (EString::to_lower(EString::prophecy_list.at(i)->base_name) == EString::to_lower(loot->prophecy))
					{
						loot->name = EString::prophecy_list.at(i)->ru_name;
					}
				}
			}

			if (p->enchantment != "")
			{
				loot->any_enchantment = true;
			}

			for (std::string s : p->explicit_list)
			{
				//std::cout << "added explicit <" << s << "> to" << loot->name << std::endl;
				loot->explicit_list.push_back(s);
			}

			//std::cout << "min_item_level=" << p->min_item_level << std::endl;
			//std::cout << "max_item_level=" << p->max_item_level << std::endl;

			if (p->max_item_level > 0)
			{
				if (p->max_item_level > p->min_item_level)
				{
					loot->item_level = p->min_item_level + (rand() % (p->max_item_level - p->min_item_level + 1));
				}
				else
				{
					loot->item_level = p->max_item_level;
				}

				if (loot->item_level < 1) { loot->item_level = 1; }
				//if (loot->item_level > loot->iteml) { loot->links = loot->sockets; }
			}

			//std::cout << "item_level=" << loot->item_level << std::endl;

			if (p->max_rarity > 0)
			{
				if (p->max_rarity > p->min_rarity)
				{
					loot->numeric_rarity = p->min_rarity + (rand() % (p->max_rarity - p->min_rarity + 1));
				}
				else
				{
					loot->numeric_rarity = p->max_rarity;
				}

				if (loot->numeric_rarity < 0) { loot->numeric_rarity = 0; }
				if (loot->numeric_rarity > 3) { loot->numeric_rarity = 3; }

				if (loot->numeric_rarity == 0) { loot->rarity = "Normal"; }
				if (loot->numeric_rarity == 1) { loot->rarity = "Magic"; }
				if (loot->numeric_rarity == 2) { loot->rarity = "Rare"; }
				if (loot->numeric_rarity == 3) { loot->rarity = "Unique"; }
			}

			//std::cout << "base class of item [" << loot->name << "] is <" << loot->base_class << ">" << std::endl;
			//std::cout << "sockets [" << loot->sockets << "]  links <" << loot->links << ">" << std::endl;

			//std::cout << "item name [" << loot->name << "]" << std::endl;
			//**********************************************************************************
			//**********************************************************************************

			prepared_pattern_list.erase(prepared_pattern_list.begin() + selected);

			put_loot(loot);

			loot_vector_id++;
			drop_count--;
		}
	}


}

void EWindowLootSimulator::put_loot(LootItem*& loot)
{
	main_loot_item_list.push_back(loot);

	find_filter_block(loot, StaticData::window_filter_block, false);
	find_filter_block(loot, StaticData::default_filter_block, true);

	place(loot);



	if (loot->filter_block_link != NULL)
	{
		if ((loot->filter_block_link->is_alert_sound) && (loot->filter_block_link->alert_sound_name != ""))
		{
			ESound::default_drop_sound.at(loot->filter_block_link->alert_sound_id)->setDefaultVolume(StaticData::window_filter_block->sound_volume);
			ESound::engine->play2D(ESound::default_drop_sound.at(loot->filter_block_link->alert_sound_id));
		}

		if ((loot->filter_block_link->is_custom_alert_sound) && (loot->filter_block_link->custom_alert_sound_name != ""))
		{
			ESound::get_sound_by_name(loot->filter_block_link->custom_alert_sound_name)->setDefaultVolume(StaticData::window_filter_block->sound_volume);
			ESound::engine->play2D(ESound::get_sound_by_name(loot->filter_block_link->custom_alert_sound_name));
		}
	}

	ESound::flip_sound->setDefaultVolume(StaticData::window_filter_block->sound_volume);
	ESound::engine->play2D(ESound::flip_sound);
}

void EWindowLootSimulator::draw(Batcher* _batch, float _delta)
{
	//_batch->setcolor_alpha(EColorCollection::GRAY, 0.5f);
	//_batch->draw_simple_rect(pos_x, pos_y, 800.0f, 800.0f);
	
	_batch->setcolor(EColorCollection::WHITE);
	if (is_bright_bg)
	{_batch->draw_rect_with_uv(pos_x, pos_y, 1000.0f, 700.0f, DefaultGabarite::gabarite_bg_bright);}
	else
	{_batch->draw_rect_with_uv(pos_x, pos_y, 1000.0f, 700.0f, DefaultGabarite::gabarite_bg_dark);}

	EFont::active_font->scale = 1.0f;

	for (LootItem* loot : main_loot_item_list)
	if
	(
		(
			(loot->filter_block_link != NULL)
			&&
			(loot->filter_block_link->is_show)
			&&
			(loot->filter_block_link->autogen_include.at(link_to_autogen_drop_button->selected_element))
		)
		||
		(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		||
		(loot->filter_block_link == NULL)
	)
	{
		//loot->filter_block_link = StaticData::window_filter_block->filter_block_list.at(rand() % StaticData::window_filter_block->filter_block_list.size());

		//std::cout << "___" << std::endl;
		EFont::active_font->set_align_once(Enums::PositionMode::MID);

		if ((loot->filter_block_link != NULL) && (loot->filter_block_link->is_font_size_active))
		{
			EFont::active_font->scale = loot->filter_block_link->font_size / 32.0f * font_scale_factor;
		}
		else
		{
			if (loot->default_filter_block_link != NULL)
			{EFont::active_font->scale = loot->default_filter_block_link->font_size / 32.0f * font_scale_factor;}
			else
			{EFont::active_font->scale = 20.0f / 32.0f * font_scale_factor;}
		}

		if ((loot->filter_block_link != NULL) && (!loot->filter_block_link->autogen_include.at(link_to_autogen_drop_button->selected_element)))
		{
			EFont::active_font->scale = 16.0f / 32.0f * font_scale_factor;
		}

		float w = EFont::active_font->get_width(EFont::active_font, loot->name);
		float h = 20.0f * EFont::active_font->scale;


		if ((loot->filter_block_link != NULL) && (loot->filter_block_link->is_bg_color_active))
		{
			_batch->setcolor(loot->filter_block_link->bg_red / 255.0f, loot->filter_block_link->bg_green / 255.0f, loot->filter_block_link->bg_blue / 255.0f, loot->filter_block_link->bg_alpha / 255.0f);
		}
		else
		{
			if (loot->default_filter_block_link != NULL)
			{_batch->setcolor(loot->default_filter_block_link->bg_red / 255.0f, loot->default_filter_block_link->bg_green / 255.0f, loot->default_filter_block_link->bg_blue / 255.0f, loot->default_filter_block_link->bg_alpha / 255.0f);}
			else
			{_batch->setcolor_alpha(EColorCollection::GRAY, 0.9f);}
		}

		//LOOT BG
		_batch->draw_rect_with_uv(pos_x + loot->pos_x, pos_y + loot->pos_y, w + 13.0f, h, DefaultGabarite::gabarite_white);


		//std::cout << "try set color" << std::endl;
		if ((loot->filter_block_link != NULL) && (loot->filter_block_link->is_text_color_active))
		{
			_batch->setcolor(loot->filter_block_link->text_color_red / 255.0f, loot->filter_block_link->text_color_green / 255.0f, loot->filter_block_link->text_color_blue / 255.0f, loot->filter_block_link->text_color_alpha / 255.0f);
		}
		else
		{
			if (loot->default_filter_block_link != NULL)
			{_batch->setcolor(loot->default_filter_block_link->text_color_red / 255.0f, loot->default_filter_block_link->text_color_green / 255.0f, loot->default_filter_block_link->text_color_blue / 255.0f, loot->default_filter_block_link->text_color_alpha / 255.0f);}
			else
			{_batch->setcolor(EColorCollection::WHITE);}
		}


		//std::cout << "try draw font (text=" << loot->name << ")" << std::endl;
		EFont::active_font->draw(_batch, loot->name, pos_x + loot->pos_x + w / 2.0f + 5.0f, pos_y + loot->pos_y + 3.0f);
		//std::cout << "success"  << std::endl;

		
		if ((loot->filter_block_link != NULL) && (loot->filter_block_link->is_rama_color_active))
		{_batch->setcolor(loot->filter_block_link->rama_red / 255.0f, loot->filter_block_link->rama_green / 255.0f, loot->filter_block_link->rama_blue / 255.0f, loot->filter_block_link->rama_alpha / 255.0f);}
		else
		{
			if (loot->default_filter_block_link != NULL)
			{_batch->setcolor(loot->default_filter_block_link->rama_red / 255.0f, loot->default_filter_block_link->rama_green / 255.0f, loot->default_filter_block_link->rama_blue / 255.0f, loot->default_filter_block_link->rama_alpha / 255.0f);}
			else
			{_batch->setcolor_alpha (EColorCollection::WHITE, 0.7f);}
		}



		_batch->draw_rama(pos_x + loot->pos_x, pos_y + loot->pos_y, w + 13.0f, h, 2.0f, DefaultGabarite::gabarite_white);
		
		
		if ((loot->filter_block_link != NULL) && (loot->filter_block_link->is_minimap_icon))
		{
			_batch->setcolor(EColorCollection::MINIMAP_ICON_COLOR[loot->filter_block_link->minimap_icon_color]);
			float siz = 1.0f / (1.0f + loot->filter_block_link->minimap_icon_size / 2.0f) * 30.0f;

			_batch->draw_rect_with_uv(pos_x + loot->pos_x - siz / 2.0f, pos_y + loot->pos_y + siz /2.0f, siz, siz, DefaultGabarite::gabarite_minimap_icon[loot->filter_block_link->minimap_icon_shape]);
		}


	}


	for (LootItem* loot : main_loot_item_list)
	if
	(
		(
			(loot->filter_block_link != NULL)
			&&
			(loot->filter_block_link->is_show)
		)
		||
		(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		||
		(loot->filter_block_link == NULL)
	)
	{
		if ((loot->filter_block_link != NULL) && (loot->filter_block_link->is_font_size_active))
		{
			EFont::active_font->scale = loot->filter_block_link->font_size / 32.0f * font_scale_factor;
		}
		else
		{
			if (loot->default_filter_block_link != NULL)
			{
				EFont::active_font->scale = loot->default_filter_block_link->font_size / 32.0f * font_scale_factor;
			}
			else
			{
				EFont::active_font->scale = 20.0f / 32.0f * font_scale_factor;
			}
		}

		if ((loot->filter_block_link != NULL) && (!loot->filter_block_link->autogen_include.at(link_to_autogen_drop_button->selected_element)))
		{
			EFont::active_font->scale = 16.0f / 32.0f * font_scale_factor;
		}

		float w = EFont::active_font->get_width(EFont::active_font, loot->name);
		float h = 20.0f * EFont::active_font->scale;

		if
			(
			(EControl::mouse_x >= loot->pos_x + pos_x)
			&&
			(EControl::mouse_x <= loot->pos_x + pos_x + w + 13.0f)
			&&
			(EControl::mouse_y >= loot->pos_y + pos_y)
			&&
			(EControl::mouse_y <= loot->pos_y + pos_y + h)
			)
		{
			if ((EControl::mouse_pressed) && (loot->filter_block_link != NULL))
			{
				int temp_scroll = -1;

				/*
				for (int i = 0; i <= loot->filter_block_link->order_id; i++)
				{
					if ((!StaticData::window_filter_block->filter_block_list.at(i)->hided_by_separator) || (StaticData::window_filter_block->filter_block_list.at(i)->contain_start_separator))
					{
						temp_scroll++;
					}
				}*/

				//EControl::block_scroll = temp_scroll;
				EControl::block_scroll = loot->filter_block_link->order_id;

				//loot->filter_block_link->hided_by_separator = false;
				//StaticData::window_filter_block->recalculate_filter_block_separator();
				loot->filter_block_link->highlight_time = 0.5f;
				//loot->filter_block_link->hided_by_separator = false;

				for (FilterBlock* f : StaticData::window_filter_block->filter_block_list)
				{
					f->force_enabled = false;
				}

				loot->filter_block_link->force_enabled = true;
				//if (!loot->filter_block_link->hided_by_separator) {  }
			}

			EFont::active_font->align_x = Enums::PositionMode::LEFT;

			float xx = EControl::mouse_x + 8.0f;
			if (xx + 300.0f > EWindow::SCR_WIDTH) { xx = EWindow::SCR_WIDTH - 300.0f; }

			xx = round(xx);

			float yy = EControl::mouse_y;
			if (yy + 380.0f > EWindow::SCR_HEIGHT) { yy = EWindow::SCR_HEIGHT - 380.0f; }

			yy = round(yy);

			float dy = 20.0f;
			float move_y = 1.0f;

			EFont::active_font->scale = 1.0f;
			EFont::active_font->align_x = Enums::PositionMode::MID;


			//loot description bg
			if ((loot->is_shaper_map) || (loot->shaper_item))
			{
				_batch->setcolor_alpha(EColorCollection::WHITE, 0.95f);
				_batch->draw_rect_with_uv(xx, yy, 434, 300, DefaultGabarite::gabarite_shaper_small);
			}
			else
			if ((loot->is_elder_map) || (loot->elder_item))
			{
				_batch->setcolor_alpha(EColorCollection::WHITE, 0.95f);
				_batch->draw_rect_with_uv(xx, yy, 434, 300, DefaultGabarite::gabarite_elder_small);
			}
			else
			if ((loot->is_blighted_map))
			{
				_batch->setcolor_alpha(EColorCollection::WHITE, 0.95f);
				_batch->draw_rect_with_uv(xx, yy, 434, 300, DefaultGabarite::gabarite_blighted_small);
			}
			else
			{
				_batch->setcolor_alpha(EColorCollection::BLACK, 0.95f);
				_batch->draw_simple_rect(xx, yy, 434, 300);
			}

			_batch->setcolor_alpha(EColorCollection::GRAY, 0.9f);
			if (loot->rarity == "Normal") { _batch->setcolor(EColorCollection::DAD_NORMAL); }
			if (loot->rarity == "Magic") { _batch->setcolor(EColorCollection::DAD_MAGIC); }
			if (loot->rarity == "Rare") { _batch->setcolor(EColorCollection::DAD_RARE); }
			if (loot->rarity == "Unique") { _batch->setcolor(EColorCollection::DAD_UNIQUE); }

			_batch->draw_rect_with_uv(xx, yy + 266, 434, 34, DefaultGabarite::gabarite_cap);

			_batch->draw_rama(xx, yy, 434, 300, 3, DefaultGabarite::gabarite_cap);

			EFont::active_font->draw(_batch, loot->name, xx + 5.0f + 222.0f, yy + 282.0f);

			if (loot->enchantment != "")
			{
				_batch->setcolor(EColorCollection::GREEN);
				EFont::active_font->draw(_batch, loot->enchantment, xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y); move_y++;
			}

			if (loot->cluster_enchantment != "")
			{
				_batch->setcolor(EColorCollection::GRAY);
				EFont::active_font->draw(_batch, loot->cluster_enchantment, xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y); move_y++;
			}

			_batch->setcolor(EColorCollection::GRAY);
			EFont::active_font->draw(_batch, loot->base_class, xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y); move_y++;

			if (loot->quality > 0)
			{
				_batch->setcolor(EColorCollection::GRAY);
				EFont::active_font->draw(_batch, cached_quality_text + "   ", xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				_batch->setcolor(EColorCollection::WHITE);
				EFont::active_font->add_draw(_batch, std::to_string(loot->quality) + "%", xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				move_y++;
			}

			if (loot->gem_level > 0)
			{
				_batch->setcolor(EColorCollection::GRAY);
				EFont::active_font->draw(_batch, cached_gem_level + "   ", xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				_batch->setcolor(EColorCollection::WHITE);
				EFont::active_font->add_draw(_batch, std::to_string(loot->gem_level), xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				move_y++;
			}

			if (loot->item_level > 0)
			{
				_batch->setcolor(EColorCollection::GRAY);
				EFont::active_font->draw(_batch, cached_item_level + "   ", xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				_batch->setcolor(EColorCollection::WHITE);
				EFont::active_font->add_draw(_batch, std::to_string(loot->item_level), xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				move_y++;
			}

			if (loot->map_tier > 0)
			{
				_batch->setcolor(EColorCollection::GRAY);
				EFont::active_font->draw(_batch, cached_map_tier + "   ", xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				_batch->setcolor(EColorCollection::WHITE);
				EFont::active_font->add_draw(_batch, std::to_string(loot->map_tier), xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				move_y++;
			}

			if (loot->corrupted)
			{
				_batch->setcolor(EColorCollection::RED);
				EFont::active_font->draw(_batch, cached_corrupted, xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				move_y++;

				EFont::active_font->draw(_batch, cached_corrupted_mods_count + std::to_string(loot->corrupted_mods), xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);
				move_y++;
			}

			if (loot->is_mirrored)
			{
				_batch->setcolor(EColorCollection::CYAN);
				EFont::active_font->draw(_batch, cached_mirrored, xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

				move_y++;

				//EFont::active_font->draw(_batch, cached_corrupted_mods_count + std::to_string(loot->corrupted_mods), xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);

			}

			move_y++;
			for (std::string s : loot->explicit_list)
			{
				_batch->setcolor(EColorCollection::CYAN);
				EFont::active_font->draw(_batch, s, xx + 5.0f + 210.0f, yy + 270.0f - dy * move_y);
			}

			_batch->setcolor(EColorCollection::GRAY);

			int temp_red = loot->red_socket;
			int temp_green = loot->green_socket;
			int temp_blue = loot->blue_socket;
			int temp_white = loot->white_socket;


			//LOOT PREVIEW SOCKETS BG
			_batch->setcolor(EColorCollection::DARK_GRAY);
			_batch->draw_rect_with_uv(xx + 354.0f, yy + 30.0f, 76.0f, 120.0f, DefaultGabarite::gabarite_white);

			_batch->setcolor(EColorCollection::GRAY);
			_batch->draw_rama(xx + 354.0f, yy + 30.0f, 76.0f, 120.0f, 3.0f, DefaultGabarite::gabarite_white);


			//LOOT PREVIEW SOCKETS
			for (int i = 0; i < loot->sockets; i++)
			{
				if (temp_red > 0)
				{
					_batch->setcolor(EColorCollection::RED);
					temp_red--;
				}
				else
				if (temp_green > 0)
				{
					_batch->setcolor(EColorCollection::GREEN);
					temp_green--;
				}
				else
				if (temp_blue > 0)
				{
					_batch->setcolor(EColorCollection::BLUE);
					temp_blue--;
				}
				else
				{
					_batch->setcolor(EColorCollection::WHITE);
				}

				_batch->setcolor(loot->socket_color.at(i));

				_batch->draw_rect_with_uv(xx + 354.0f + sockets_postition_x[i] * 40.0f, yy + 115.0f - sockets_postition_y[i] * 40.0f, 36.0f, 36.0f, DefaultGabarite::gabarite_socket);

				_batch->setcolor(EColorCollection::WHITE);

				

				
				

			}

			bool is_link_horizontal = true;
			for (int i = 0; i < loot->links - 1; i++)
			{
				if (is_link_horizontal)
				{
					_batch->draw_rect_with_uv(xx + 354.0f + links_postition_x[i], yy + 115.0f  + links_postition_y[i], 24.0f, 11.0f, DefaultGabarite::gabarite_link_horizontal);
				}
				else
				{
					_batch->draw_rect_with_uv(xx + 354.0f + links_postition_x[i], yy + 115.0f  + links_postition_y[i], 11.0f, 24.0f, DefaultGabarite::gabarite_link_vertical);
				}

				is_link_horizontal = !is_link_horizontal;
			}

			yy += 280.0f;




			

			/*
			if (loot->filter_block_link != NULL)
			{
				EFont::active_font->draw(_batch, "Block id: " + std::to_string(loot->filter_block_link->order_id), xx + 5.0f, yy - dy * move_y); move_y++;
			}
			else
			{
				EFont::active_font->draw(_batch, "Block id: NONE", xx + 5.0f, yy - 18.0 * 2); move_y++;
			}*/


			
			//EFont::active_font->draw(_batch, "Class: " + loot->base_class, xx + 5.0f, yy - dy * move_y); move_y++;

			/*
			if (loot->rarity == "Normal")	{ _batch->setcolor(EColorCollection::DAD_NORMAL); }
			if (loot->rarity == "Magic")	{ _batch->setcolor(EColorCollection::DAD_MAGIC); }
			if (loot->rarity == "Rare")		{ _batch->setcolor(EColorCollection::DAD_RARE); }
			if (loot->rarity == "Unique")	{ _batch->setcolor(EColorCollection::DAD_UNIQUE); }*/

			//EFont::active_font->draw(_batch, loot->rarity, xx + 5.0f, yy - dy * move_y); move_y++;

			//_batch->setcolor(EColorCollection::WHITE);
			/*
			if (loot->item_level > 0) { EFont::active_font->draw(_batch, "item level: " + std::to_string(loot->item_level), xx + 5.0f, yy - dy * move_y); move_y++;}


			if (loot->sockets >= 6) { _batch->setcolor_lum(EColorCollection::GREEN, 0.90f); }
			else { _batch->setcolor(EColorCollection::WHITE); }
			if (loot->sockets > 0) { EFont::active_font->draw(_batch, "sockets: " + std::to_string(loot->sockets), xx + 5.0f, yy - dy * move_y); move_y++;}

			if (loot->links == 5) { _batch->setcolor_lum(EColorCollection::GREEN, 0.90f); }
			else { _batch->setcolor(EColorCollection::WHITE); }
			if (loot->links >= 6) { _batch->setcolor_lum(EColorCollection::PINK, 0.90f); }
			else { _batch->setcolor(EColorCollection::WHITE); }
			if (loot->links > 0) { EFont::active_font->draw(_batch, "links: " + std::to_string(loot->links), xx + 5.0f, yy - dy * move_y); move_y++;}

			if (loot->map_tier < 6) { _batch->setcolor_lum(EColorCollection::WHITE, 0.90f); }
			else { _batch->setcolor(EColorCollection::WHITE); }
			if (loot->map_tier < 11) { _batch->setcolor_lum(EColorCollection::YELLOW, 0.90f); }
			else { _batch->setcolor(EColorCollection::RED); }
			if (loot->map_tier > 0) { EFont::active_font->draw(_batch, "Map tier: " + std::to_string(loot->map_tier), xx + 5.0f, yy - dy * move_y); move_y++; }

			if (loot->red_socket > 0)
			{
				_batch->setcolor(EColorCollection::RED);
				EFont::active_font->draw(_batch, "RED: " + std::to_string(loot->red_socket), xx + 5.0f, yy - dy * move_y); move_y++;
			}

			if (loot->green_socket > 0)
			{
				_batch->setcolor(EColorCollection::GREEN);
				EFont::active_font->draw(_batch, "GREEN: " + std::to_string(loot->green_socket), xx + 5.0f, yy - dy * move_y); move_y++;
			}

			if (loot->blue_socket > 0)
			{
				_batch->setcolor(EColorCollection::CYAN);
				EFont::active_font->draw(_batch, "BLUE: " + std::to_string(loot->blue_socket), xx + 5.0f, yy - dy * move_y); move_y++;
			}

			if (loot->white_socket > 0)
			{
				_batch->setcolor(EColorCollection::WHITE);
				EFont::active_font->draw(_batch, "WHITE: " + std::to_string(loot->white_socket), xx + 5.0f, yy - dy * move_y); move_y++;
			}*/

		}
	}


	EFont::active_font->scale = 1.0f;
	EFont::active_font->align_x = Enums::PositionMode::LEFT;
	
	/*


	_batch->setcolor_alpha(EColorCollection::RED, 0.5f);

	for (int i=0; i<87; i++)
	for (int j=0; j<125; j++)
	if (!free_space[j][i])
	{
		_batch->draw_simple_rect(pos_x + j * 8.0f, pos_y + i * 8.0f, 8.0f, 8.0f);
	}
	
	*/



}


void EWindowLootSimulator::update_localisation()
{
	for (EButton* b : button_list)
	{b->update_localisation();}

	cached_quality_text = EString::localize_it("quality_text");
	cached_gem_level = EString::localize_it("gem_level_text");
	cached_item_level = EString::localize_it("item_level_text");
	cached_map_tier = EString::localize_it("map_tier_text");
	cached_corrupted = EString::localize_it("corrupted_text");
	cached_corrupted_mods_count = EString::localize_it("corrupted_text_mods_count");
	cached_mirrored = EString::localize_it("mirrored_text");
}

bool EWindowLootSimulator::check_condition(std::string _condition, int _num_a, int num_b)
{

	//std::cout << "condition symbol [" << _condition << "] num a [" << _num_a << "] num b [" << num_b << "]" << std::endl;

	if ((_condition == "<") && (_num_a >= num_b)) { return false; }
	if ((_condition == "<=") && (_num_a > num_b)) { return false; }
	if ((_condition == "=") && (_num_a != num_b)) { return false; }
	if ((_condition == "==") && (_num_a != num_b)) { return false; }
	if ((_condition == ">=") && (_num_a < num_b)) { return false; }
	if ((_condition == ">") && (_num_a <= num_b)) { return false; }

	return true;
}

int EWindowLootSimulator::rarity_to_number(std::string _rarity)
{
	if (EString::to_lower(_rarity) == "normal") { return 0; }
	if (EString::to_lower(_rarity) == "magic") { return 1; }
	if (EString::to_lower(_rarity) == "rare") { return 2; }
	if (EString::to_lower(_rarity) == "unique") { return 3; }

	return -1;
}

void rejection(std::string _s, LootItem* _l)
{
	//std::cout << "item: " << _l->name << "   rejected by: " + _s << std::endl;
}

void EWindowLootSimulator::find_filter_block(LootItem* _l, EWindowFilterBlock* _w, bool _default)
{
	bool match_detect = false;

	bool temp_match = false;

	bool any_detect = false;




	int fb_id = 0;

	for (FilterBlock* fb : _w->filter_block_list)
	{
		match_detect = false;

		if (fb->filter_block_items_button_list.size() <= 0) { match_detect = true; }

		for (EButton* b : fb->filter_block_items_button_list)
		{
			if
				(
				(
					(!((EButtonFilterItem*)b)->is_full_equal_mode)
					&&
					(EString::to_lower(_l->data_name, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
					)
					||
					(
					(((EButtonFilterItem*)b)->is_full_equal_mode)
						&&
						(_l->data_name == b->data_string)
						)
					)
			{
				match_detect = true;
			}

			/*if (()&&())
			{

			}*/

		}

		/*
		if (!fb->autogen_include.at(link_to_autogen_drop_button->selected_element))
		{
			match_detect = false;

			if ((!_default) && (!match_detect)) { rejection("autogenerator exclude", _l); }
		}*/

		if (fb->disabled)
		{
			match_detect = false;

			if ((!_default) && (!temp_match)) { rejection("disabled", _l); }
		}

		if (match_detect)
		{
			temp_match = false;
			if (!fb->is_base_class_active) { temp_match = true; }

			for (EButton* b : fb->base_class_list)
			{
				if
					(EString::to_lower(_l->base_class, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
				{
					temp_match = true;
				}
			}

			match_detect = temp_match;

			if ((!_default) && (!temp_match)) { rejection("base_class", _l); }
		}

		if (match_detect)
		{
			temp_match = false;
			if (!fb->is_enchantment_active) { temp_match = true; }

			//std::cout << "ench: " << _l->enchantment << std::endl;

			for (EButton* b : fb->enchantment_list)
			{
				if
					(EString::to_lower(_l->enchantment, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
				{
					temp_match = true;
				}
			}

			match_detect = temp_match;

			if ((!_default) && (!temp_match)) { rejection("enchantment", _l); }

		}

		if (match_detect)
		{
			temp_match = false;
			if (!fb->is_cluster_enchantment_active) { temp_match = true; }

			//std::cout << "ench: " << _l->enchantment << std::endl;

			for (EButton* b : fb->cluster_enchantment_list)
			{
				if
					(EString::to_lower(_l->cluster_enchantment, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
				{
					temp_match = true;
				}
			}

			match_detect = temp_match;

			if ((!_default) && (!temp_match)) { rejection("cluster enchantment", _l); }

		}

		if (match_detect)
		{
			temp_match = true;

			if (!fb->is_explicit)
			{
				temp_match = true;
			}
			else
			{
				//std::cout << "explicit size in #" << std::to_string(fb->order_id) << " =" << std::to_string(fb->explicit_list.size()) << std::endl;
				for (ExplicitGroup* ex : fb->explicit_list)
					if (match_detect)
					{
						if (ex->button_list.size() > 0)
						{
							temp_match = false;
						}
						else
						{
							temp_match = true;
						}

						for (EButton* b : ex->button_list)
						{
							for (std::string s : _l->explicit_list)
							{
								if (EString::to_lower(s, false).find(EString::to_lower(b->text, false)) != std::string::npos)
								{
									temp_match = true;
								}
								else
								{
									if (!_default)
									{
										std::cout << "explicit from loot '" << s << "' not equal '" << b->text << "'" << std::endl;
									}
								}
							}
						}

						if (!temp_match) { match_detect = false; }

						//match_detect = temp_match;
					}
			}



		}

		if (match_detect)
		{
			temp_match = false;
			if (!fb->is_prophecy_active) { temp_match = true; }

			for (EButton* b : fb->prophecy_list)
			{
				if
					(EString::to_lower(_l->prophecy, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
				{
					temp_match = true;
				}
			}

			match_detect = temp_match;
			if ((!_default) && (!match_detect)) { rejection("prophecy", _l); }
		}


		//std::cout << "data rarity is active =" << std::to_string(true) << std::endl;

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_RARITY)) && (!check_condition(fb->rarity_condition, rarity_to_number(_l->rarity), rarity_to_number(fb->item_rarity))))
		{
			match_detect = false;
			if (!_default) { rejection("rarity", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ITEM_LEVEL)) && (!check_condition(fb->item_level_condition, _l->item_level, fb->item_level)))
		{
			match_detect = false;
			if (!_default) { rejection("itemlevel", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AREA_LEVEL)) && (!check_condition(fb->area_level_condition, area_level, fb->area_level)))
		{
			match_detect = false;
			if (!_default) { rejection("area level", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_REQUIRED_LEVEL)) && (!check_condition(fb->required_level_condition, _l->req_level, fb->required_level)))
		{
			match_detect = false;
			if (!_default) { rejection("req", _l); }
		}

		/*
		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS)) && (!check_condition(fb->socket_condition, _l->sockets, fb->socket_count)))
		{
			match_detect = false;
			if (!_default) { rejection("sockets", _l); }
		}*/

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_LINKS)) && (!check_condition(fb->links_condition, _l->links, fb->links_count)))
		{
			match_detect = false;
			if (!_default) { rejection("links", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_CORRUPTION_MODS)) && (!check_condition(fb->corrupted_mods_condition, _l->corrupted_mods, fb->corrupted_mods_count)))
		{
			match_detect = false;
			if (!_default) { rejection("corruption mods", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_QUALITY)) && (!check_condition(fb->item_quality_condition, _l->quality, fb->item_quality)))
		{
			match_detect = false;
			if (!_default) { rejection("quality", _l); }
		}


		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_GEM_LEVEL)) && (!check_condition(fb->gem_level_condition, _l->gem_level, fb->gem_level)))
		{
			match_detect = false;
			if (!_default) { rejection("gem level", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MAP_TIER)) && (!check_condition(fb->map_tier_condition, _l->map_tier, fb->map_tier)))
		{
			match_detect = false;
			if (!_default) { rejection("map tier", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_HEIGHT)) && (!check_condition(fb->item_height_condition, _l->height, fb->item_height)))
		{
			match_detect = false;
			if (!_default) { rejection("height", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_WIDTH)) && (!check_condition(fb->item_width_condition, _l->width, fb->item_width)))
		{
			match_detect = false;
			if (!_default) { rejection("width", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_STACK_SIZE)) && (!check_condition(fb->item_stack_size_condition, _l->quantity, fb->item_stack_size)))
		{
			match_detect = false;
			if (!_default) { rejection("data stack size", _l); }
		}





		if ((match_detect) && (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP)))
			{
				//bool microreject = true;
				match_detect = false;
				for (int i = 0; i < fb->red_sockets_group.size(); i++)
				if
				(
					(
						(fb->socket_group_links.at(i) > 0) ||
						(fb->red_sockets_group.at(i)>0)||
						(fb->green_sockets_group.at(i)>0)||
						(fb->blue_sockets_group.at(i)>0)||
						(fb->white_sockets_group.at(i)>0)||
						(fb->abyss_sockets_group.at(i)>0)||
						(fb->delve_sockets_group.at(i)>0)
					)
					&&
					(
					(
							(
								check_condition(fb->socket_group_condition, _l->links, fb->socket_group_links.at(i)))
								||
								(fb->socket_group_links.at(i) == 0)
							)
							&&
							(
								(check_condition(fb->socket_group_condition, _l->linked_red_socket, fb->red_sockets_group.at(i)))
								||
								(fb->red_sockets_group.at(i) == 0)
							)
							&&
							(
								(check_condition(fb->socket_group_condition, _l->linked_green_socket, fb->green_sockets_group.at(i)))
								||
								(fb->green_sockets_group.at(i) == 0)
							)
							&&
							(
								(check_condition(fb->socket_group_condition, _l->linked_blue_socket, fb->blue_sockets_group.at(i)))
								||
								(fb->blue_sockets_group.at(i) == 0)
							)
							&&
							(
								(check_condition(fb->socket_group_condition, _l->linked_white_socket, fb->white_sockets_group.at(i)))
								||
								(fb->white_sockets_group.at(i) == 0)
							)
					)
				)
				{
					match_detect = true;
				}

				if (!match_detect)
				{
					if (!_default) { rejection("socket colour", _l); }
				}
			}

		if((match_detect)&&(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS)))
		{
			
			/*std::cout << "[" << 0
				<< "] sockets: " << fb->socket_count.at(0)
				<< ", red: " << fb->red_sockets.at(0)
				<< ", green: " << fb->green_sockets.at(0)
				<< ", blue: " << fb->blue_sockets.at(0)
				<< ", white: " << fb->white_sockets.at(0)
				<< ", abyss: " << fb->abyss_sockets.at(0)
				<< ", delve: " << fb->delve_sockets.at(0)
				<< ", equation: " << fb->socket_condition
				<< std::endl;

			std::cout << "[" << "item param"
				<< "] sockets: " << _l->sockets
				<< ", red: " << _l->red_socket
				<< ", green: " << _l->green_socket
				<< ", blue: " << _l->blue_socket
				<< ", white: " << _l->white_socket
				<< ", abyss: " << _l->abyss_socket
				<< ", delve: " << _l->delve_socket
				<< std::endl;*/

			//bool microreject = true;
			match_detect = false;
			for (int i = 0; i < fb->socket_count.size(); i++)
			{


				if
					(
					(
						(fb->socket_count.at(i) > 0) ||
						(fb->red_sockets.at(i) > 0) ||
						(fb->green_sockets.at(i) > 0) ||
						(fb->blue_sockets.at(i) > 0) ||
						(fb->white_sockets.at(i) > 0) ||
						(fb->abyss_sockets.at(i) > 0) ||
						(fb->delve_sockets.at(i) > 0)
						)
						&&
						(
						(
							(
								check_condition(fb->socket_condition, _l->sockets, fb->socket_count.at(i)))
							||
							(fb->socket_count.at(i) == 0)
							)
							&&
							(
							(check_condition(fb->socket_condition, _l->red_socket, fb->red_sockets.at(i)))
								||
								(fb->red_sockets.at(i) == 0)
								)
							&&
							(
							(check_condition(fb->socket_condition, _l->green_socket, fb->green_sockets.at(i)))
								||
								(fb->green_sockets.at(i) == 0)
								)
							&&
							(
							(check_condition(fb->socket_condition, _l->blue_socket, fb->blue_sockets.at(i)))
								||
								(fb->blue_sockets.at(i) == 0)
								)
							&&
							(
							(check_condition(fb->socket_condition, _l->white_socket, fb->white_sockets.at(i)))
								||
								(fb->white_sockets.at(i) == 0)
								)
							&&
							(
							(check_condition(fb->socket_condition, _l->abyss_socket, fb->abyss_sockets.at(i)))
								||
								(fb->abyss_sockets.at(i) == 0)
								)
							&&
							(
							(check_condition(fb->socket_condition, _l->delve_socket, fb->delve_sockets.at(i)))
								||
								(fb->delve_sockets.at(i) == 0)
								)
							)
						)
				{
					match_detect = true;
				}
			}

			if (!match_detect)
			{
				if (!_default) { rejection("socket colour", _l); }
			}
		}

		//std::cout << "is active=" << std::to_string(fb->is_synthesised_item_active) << " is synthesised block=" << std::to_string(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SYNTHESISED)) << "is synthesised item=" << std::to_string(_l->synthesised_item) << std::endl;

		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SYNTHESISED) != _l->synthesised_item)
				)
		{
			match_detect = false;
			if (!_default) { rejection("synthesised", _l); }
		}

		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_FRACTURED) != _l->fractured_item)
				)
		{
			match_detect = false;
			if (!_default) { rejection("fractured", _l); }
		}


		/*
		for (ExplicitGroup* ex : fb->explicit_list)
			if (match_detect)
			{
				if (ex->is_active)
				{
					temp_match = false;
					for (EButton* b : ex->button_list)
					{
						for (std::string el : _l->explicit_list)
						{
							if (el == b->data_string)
							{
								temp_match = true;
							}
						}
					}

					match_detect = temp_match;
				}
			}*/

		if
		(
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_ELDER))
				&&
				(!_l->elder_item)
			)
			||
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_SHAPER))
				&&
				(!_l->shaper_item)
			)
			||
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_CRUSADER))
				&&
				(!_l->crusader_item)
			)
			||
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_HUNTER))
				&&
				(!_l->hunter_item)
			)
			||
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_REDEEMER))
				&&
				(!_l->redeemer_item)
			)
			||
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_WARLORD))
				&&
				(!_l->warlord_item)
			)
			
		)
		{
			match_detect = false;
			if (!_default) { rejection("and shaper/elder/new influences", _l); }
		}

		if
		(
			!(
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_ELDER))
					&&
					(_l->elder_item)
				)
				||
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_SHAPER))
					&&
					(_l->shaper_item)
				)
				||
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_REDEEMER))
					&&
					(_l->redeemer_item)
				)
				||
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_CRUSADER))
					&&
					(_l->crusader_item)
				)
				||
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_HUNTER))
					&&
					(_l->hunter_item)
				)
				||
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_WARLORD))
					&&
					(_l->warlord_item)
				)
			)
			&&
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_ELDER))
				||
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_SHAPER))
				||
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_CRUSADER))
				||
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_HUNTER))
				||
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_REDEEMER))
				||
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_WARLORD))
			)
		)
		{
			match_detect = false;
			if (!_default) { rejection("or shaper/elder/new influences", _l); }
		}

		if
		(
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER))
				&&
				(!_l->shaper_item)
			)
		)
		{
			match_detect = false;
			if (!_default) { rejection("not shaper item", _l); }
		}

		if
		(
			(
				(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER))
				&&
				(!_l->elder_item)
			)
		)
		{
			match_detect = false;
			if (!_default) { rejection("not elder item", _l); }
		}

		if
		(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_BLIGHTED))
			&&
			(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_BLIGHTED) != _l->is_blighted_map)
		)
		{
			match_detect = false;
			if (!_default) { rejection("blight item", _l); }
		}

		if
		(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MIRRORED_ITEM))
			&&
			(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_MIRRORED_ITEM) != _l->is_mirrored)
		)
		{
			match_detect = false;
			if (!_default) { rejection("mirrored item", _l); }
		}

		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SHAPER_MAP) != _l->is_shaper_map)
				)
		{
			match_detect = false;
			if (!_default) { rejection("shaped map", _l); }
		}

		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_ELDER_MAP) != _l->is_elder_map)
				)
		{
			match_detect = false;
			if (!_default) { rejection("elder map", _l); }
		}


		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_CORRUPTED))
			&&
			(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_CORRUPTED) != _l->corrupted)
			)
		{
			match_detect = false;
			if (!_default) { rejection("data corrupted", _l); }
		}


		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ENCHANTMENT))
			&&
			(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_ENCHANTMENT) != _l->any_enchantment)
			)
		{
			match_detect = false;
			if (!_default) { rejection("enchant", _l); }
		}


		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_IDENTIFIED))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_IDENTIFIED) != _l->identified)
				)
		{
			match_detect = false;
			if (!_default) { rejection("identified", _l); }
		}



		if (match_detect)
		{
			any_detect = true;

			if (_default)
			{
				_l->default_filter_block_link = fb;
				std::cout << "Match detect [default]! (" << _l->name << ")" << std::endl;
			}
			else
			{
				_l->filter_block_link = fb;
				std::cout << "Match detect! (" << _l->name << ")" << std::endl;
			}

			//_l->name += " " + std::to_string(fb_id);

			if (!fb->is_continue) { break; }
		}

		if ((match_detect) && (!fb->is_continue)) { break;}

		fb_id++;
	}



	if (!any_detect)
	{

		if (_default)
		{
			_l->default_filter_block_link = NULL; std::cout << "NOT detect [default]! (" << _l->name << ")" << std::endl;
		}
		else
		{
			_l->filter_block_link = NULL; std::cout << "NOT detect! (" << _l->name << ")" << std::endl;
		}
		//_l->name += " #";
	}



}

void EWindowLootSimulator::place(LootItem* _l)
{




	float min_dist = 9999999.0f;
	int good_pos_x = 0;
	int good_pos_y = 0;

	float w = 16;

	if ((_l->filter_block_link != NULL)&&(_l->filter_block_link->is_font_size_active))
	{
		EFont::active_font->scale = _l->filter_block_link->font_size / 32.0f * font_scale_factor;

		//std::cout << "my loot filter font scale" << std::endl;
	}
	else
	{
		if (_l->default_filter_block_link != NULL)
		{
			EFont::active_font->scale = _l->default_filter_block_link->font_size / 32.0f * font_scale_factor; //EFont::active_font->scale = 16.0f / 32.0f;

			//std::cout << "default loot-filter scale" << std::endl;
		}
		else
		{
			EFont::active_font->scale = 0.5f * font_scale_factor;

			//std::cout << "have no any loot-filter link" << std::endl;
		}

		//EFont::active_font->scale = 0.2f;
	}

	if ((_l->filter_block_link != NULL) && (!_l->filter_block_link->autogen_include.at(link_to_autogen_drop_button->selected_element)))
	{
		EFont::active_font->scale = 0.5f * font_scale_factor;
	}

	w = EFont::active_font->get_width(EFont::active_font, _l->name);

	for (int i = 0; i < 87; i++)
	for (int j = 0; j < 128; j++)
		{
			bool detect_block = false;

			for (int sy = i; sy <= i + (int)(EFont::active_font->scale * 22.0f / 8.0f); sy++)
				for (int sx = j; sx <= j + (int)(w / 8.0f) + 1; sx++)
				{
					if ((sx >= 0) && (sy > 0) && (sx < 125) && (sy < 87) && (free_space[sx][sy]))
					{
						//detect_block = true;
					}
					else
					{
						detect_block = true;
					}

					if (detect_block) { break; }
				}

			if (!detect_block)
			{
				float xx = j - 62.5f + w / 16.0f;
				float yy = i - 43.5f + EFont::active_font->scale * 22.0f / 16.0f;


				float dist = xx * xx + yy * yy;

				detect_block = true;


				if (dist < min_dist)
				{
					//std::cout << "x=" << j << " y=" << i << " dist=" << dist << " min dist=" << min_dist << std::endl;

					min_dist = dist;

					good_pos_x = j;
					good_pos_y = i;
				}
			}
		}

	if ((good_pos_x >= 0) && (good_pos_y >= 0))
	{

		//w = EFont::active_font->get_width(EFont::active_font, _l->name);

		for (int sy = good_pos_y - 1.0f; sy <= good_pos_y + (int)(EFont::active_font->scale * 22.0f / 8.0f) + 1; sy++)
			for (int sx = good_pos_x - 2.0f; sx <= good_pos_x + (int)(w / 8.0f) + 2; sx++)
			{
				if ((sx < 125) && (sy < 87) && (sx >= 0) && (sy >= 0))
				{
					free_space[sx][sy] = false;
				}
			}

		_l->pos_x = good_pos_x * 8.0f;
		_l->pos_y = good_pos_y * 8.0f;
	}


}

void EWindowLootSimulator::manual_event()
{
	srand(time(NULL));
	//std::cout << "list size " << StaticData::window_filter_block->filter_block_list.size() << std::endl;

	//std::cout << "random select " << selected << std::endl;

	for (int i = 0; i < 87; i++)
	for (int j = 0; j < 125; j++)
	{
		free_space[j][i] = true;
	}


	main_loot_item_list.clear();
	prepared_pattern_list.clear();

	for (int i = 0; i < pattern_item_list.size(); i++)
	{

		//***************************ITEM NAME SECTION**************************************
		//**********************************************************************************

		for (int k = 0; k < pattern_item_list.at(i)->count; k++)
		{
			LootPatternItem* pattern = new LootPatternItem();
			//srand(time(NULL) + k * 25754);

			random_item_pool.clear();

			pattern->item_name = pattern_item_list.at(i)->item_name;
			pattern->item_base_name = pattern_item_list.at(i)->item_name;

			pattern->base_class = pattern_item_list.at(i)->base_class;

			for (int l = 0; l < ItemList::item_list.size(); l++)
			{
				if (EString::to_lower(ItemList::item_list.at(l)->item_name) == EString::to_lower(pattern->item_name))
				{
					pattern->base_class = ItemList::item_list.at(l)->base_class;

					if (EString::active_localisation == Enums::LocalisationList::RU)
					{pattern->item_name = ItemList::item_list.at(l)->item_name_ru;}

					if (EString::active_localisation == Enums::LocalisationList::EN)
					{pattern->item_name = ItemList::item_list.at(l)->item_name;}

					pattern->height = ItemList::item_list.at(l)->height;
					pattern->width = ItemList::item_list.at(l)->width;
				}
			}

			if
				(
					(pattern_item_list.at(i)->random_class != "") || (EString::to_lower(pattern_item_list.at(i)->random_class) == "any")
					||
					(pattern_item_list.at(i)->random_subclass != "") || (EString::to_lower(pattern_item_list.at(i)->random_subclass) == "any")
					||
					(pattern_item_list.at(i)->random_category != "") || (EString::to_lower(pattern_item_list.at(i)->random_category) == "any")
					||
					(pattern_item_list.at(i)->random_cost_group != "") || (EString::to_lower(pattern_item_list.at(i)->random_cost_group) == "any")
					)
			{
				fill_random_pool(pattern_item_list.at(i)->random_class, pattern_item_list.at(i)->random_subclass, pattern_item_list.at(i)->random_cost_group, pattern_item_list.at(i)->random_category);
			}


			if (random_item_pool.size() > 0)
			{
				int random_selected_item = rand() % random_item_pool.size();

				if (EString::active_localisation == Enums::LocalisationList::RU)
				{pattern->item_name = random_item_pool.at(random_selected_item)->item_name_ru;}

				if (EString::active_localisation == Enums::LocalisationList::EN)
				{pattern->item_name = random_item_pool.at(random_selected_item)->item_name;}

				pattern->item_base_name = random_item_pool.at(random_selected_item)->item_name;

				pattern->base_class = random_item_pool.at(random_selected_item)->base_class;

				pattern->height = random_item_pool.at(random_selected_item)->height;
				pattern->width = random_item_pool.at(random_selected_item)->width;
			}

			pattern->min_quality = pattern_item_list.at(i)->min_quality;
			pattern->max_quality = pattern_item_list.at(i)->max_quality;

			pattern->min_gem_level = pattern_item_list.at(i)->min_gem_level;
			pattern->max_gem_level = pattern_item_list.at(i)->max_gem_level;

			pattern->min_sockets = pattern_item_list.at(i)->min_sockets;
			pattern->max_sockets = pattern_item_list.at(i)->max_sockets;

			pattern->min_links = pattern_item_list.at(i)->min_links;
			pattern->max_links = pattern_item_list.at(i)->max_links;

			pattern->min_map_tier = pattern_item_list.at(i)->min_map_tier;
			pattern->max_map_tier = pattern_item_list.at(i)->max_map_tier;

			pattern->red_weight = pattern_item_list.at(i)->red_weight;
			pattern->green_weight = pattern_item_list.at(i)->green_weight;
			pattern->blue_weight = pattern_item_list.at(i)->blue_weight;
			pattern->white_weight = pattern_item_list.at(i)->white_weight;


			pattern->min_item_level = pattern_item_list.at(i)->min_item_level;
			pattern->max_item_level = pattern_item_list.at(i)->max_item_level;

			pattern->min_rarity = pattern_item_list.at(i)->min_rarity;
			pattern->max_rarity = pattern_item_list.at(i)->max_rarity;

			pattern->shaper_item_weight = pattern_item_list.at(i)->shaper_item_weight;
			pattern->elder_item_weight = pattern_item_list.at(i)->elder_item_weight;
			pattern->normal_item_weight = pattern_item_list.at(i)->normal_item_weight;

			pattern->shaped_map = pattern_item_list.at(i)->shaped_map;
			pattern->elder_map = pattern_item_list.at(i)->elder_map;
			pattern->blighted_map = pattern_item_list.at(i)->blighted_map;
			pattern->mirrored = pattern_item_list.at(i)->mirrored;

			pattern->enchantment = pattern_item_list.at(i)->enchantment;
			pattern->cluster_enchantment = pattern_item_list.at(i)->cluster_enchantment;

			pattern->prophecy_name = pattern_item_list.at(i)->prophecy_name;


			pattern->corruption_chance = pattern_item_list.at(i)->corruption_chance;
			pattern->mirrored_chance = pattern_item_list.at(i)->mirrored_chance;

			if (pattern->item_name != "")
			{
				prepared_pattern_list.push_back(pattern);
			}

			for (std::string s : pattern_item_list.at(i)->explicit_list)
			{
				pattern->explicit_list.push_back(s);
			}
		}
		//**********************************************************************************
		//**********************************************************************************


	}

	drop_count = prepared_pattern_list.size();
	loot_vector_id = 0;
}

void EWindowLootSimulator::close_action()
{
	StaticData::window_loot_simulator->align_x = Enums::PositionMode::MID;
	StaticData::window_filter_visual_editor->align_x = Enums::PositionMode::MID;

	//StaticData::window_filter_block->recalculate_filter_block_separator();

	for (FilterBlock* f : StaticData::window_filter_block->filter_block_list)
	{
		f->force_enabled = false;
	}
}
