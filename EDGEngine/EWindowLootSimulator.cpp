
#include "EControl.h"
#include "Enums.h"

#include "StaticData.h"
#include "EWindowLootSimulator.h"
#include <time.h>


EWindowLootSimulator::EWindowLootSimulator(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
{
	window_size_x = 1000.0f;
	window_size_y = 750.0f;

	//relative_x = 16.0f;

	//align_x = Enums::PositionMode::LEFT;

	bg_color->set_alpha(EColorCollection::GRAY, 0.75f);

	is_active = false;

	EButton* but = new EButtonText(15.0f, -15.0f, 250.0f, 20.0f, Enums::BUTTON_OPEN_PATTERN_WINDOW);
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
}

void EWindowLootSimulator::fill_random_pool(std::string _class, std::string _subclass, std::string _cost)
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
			loot->base_class = p->base_class;

			if (p->max_quality > 0)
			{
				if (p->max_quality > p->min_quality)
				{
					loot->quality = p->min_quality + (rand() % (p->max_quality - p->min_quality));
				}
				else
				{
					loot->quality = p->max_quality;
				}

				if (loot->quality < 0) { loot->quality = 0; }
			}

			//std::cout << "min sockets=" << p->min_sockets << std::endl;
			//std::cout << "max sockets=" << p->max_sockets << std::endl;
			if (p->max_sockets > 0)
			{
				if (p->max_sockets > p->min_sockets)
				{
					loot->sockets = p->min_sockets + (rand() % (p->max_sockets - p->min_sockets));
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
					loot->links = p->min_links + (rand() % (p->max_links - p->min_links));
				}
				else
				{
					loot->links = p->max_links;
				}

				if (loot->links < 0) { loot->links = 0; }
				if (loot->links > loot->sockets) { loot->links = loot->sockets; }
			}

			if (p->max_map_tier > 0)
			{
				if (p->max_map_tier > p->min_map_tier)
				{
					loot->map_tier = p->min_map_tier + (rand() % (p->max_map_tier - p->min_map_tier));
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

					if (selected_color == 0) { loot->red_socket++; }
					if (selected_color == 1) { loot->green_socket++; }
					if (selected_color == 2) { loot->blue_socket++; }
					if (selected_color == 3) { loot->white_socket++; }
				}
			}

			//std::cout << "min_item_level=" << p->min_item_level << std::endl;
			//std::cout << "max_item_level=" << p->max_item_level << std::endl;

			if (p->max_item_level > 0)
			{
				if (p->max_item_level > p->min_item_level)
				{
					loot->item_level = p->min_item_level + (rand() % (p->max_item_level - p->min_item_level));
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
					loot->numeric_rarity = p->min_rarity + (rand() % (p->max_rarity - p->min_rarity));
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

			main_loot_item_list.push_back(loot);

			find_filter_block(loot, StaticData::window_filter_block, false);
			find_filter_block(loot, StaticData::default_filter_block, true);

			place(loot);

			drop_count--;

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

			ESound::flip_sound->setDefaultVolume(0.5f);
			ESound::engine->play2D(ESound::flip_sound);

			loot_vector_id++;
		}
	}


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
			EFont::active_font->scale = loot->filter_block_link->font_size / 32.0f;
		}
		else
		{
			if (loot->default_filter_block_link != NULL)
			{EFont::active_font->scale = loot->default_filter_block_link->font_size / 32.0f;}
			else
			{EFont::active_font->scale = 20.0f / 32.0f;}
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
		if (loot->filter_block_link != NULL)
		{
			EFont::active_font->scale = loot->filter_block_link->font_size / 32.0f;
		}
		else
		{
			EFont::active_font->scale = 20.0f / 32.0f;
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
			if ((EControl::mouse_pressed)&&(loot->filter_block_link != NULL))
			{
				EControl::block_scroll = loot->filter_block_link->order_id;

				loot->filter_block_link->highlight_time = 0.5f;
			}

			EFont::active_font->align_x = Enums::PositionMode::LEFT;

			float xx = EControl::mouse_x + 8.0f;
			if (xx + 300.0f > EWindow::SCR_WIDTH) { xx = EWindow::SCR_WIDTH - 300.0f; }

			float yy = EControl::mouse_y;
			if (yy + 380.0f > EWindow::SCR_HEIGHT) { yy = EWindow::SCR_HEIGHT - 380.0f; }

			EFont::active_font->scale = 1.0f;
			_batch->setcolor_alpha(EColorCollection::BLACK, 0.9f);
			_batch->draw_simple_rect(xx, yy, 300, 300);
			_batch->setcolor(EColorCollection::WHITE);

			yy += 280.0f;

			float dy = 20.0f;
			float move_y = 0.0f;

			

			if (loot->filter_block_link != NULL)
			{
				EFont::active_font->draw(_batch, "Block id: " + std::to_string(loot->filter_block_link->order_id), xx + 5.0f, yy - dy * move_y); move_y++;
			}
			else
			{
				EFont::active_font->draw(_batch, "Block id: NONE", xx + 5.0f, yy - 18.0 * 2); move_y++;
			}

			EFont::active_font->draw(_batch, "Name: " + loot->name, xx + 5.0f, yy - dy * move_y); move_y++;
			EFont::active_font->draw(_batch, "Class: " + loot->base_class, xx + 5.0f, yy - dy * move_y); move_y++;

			if (loot->rarity == "Normal")	{ _batch->setcolor(EColorCollection::DAD_NORMAL); }
			if (loot->rarity == "Magic")	{ _batch->setcolor(EColorCollection::DAD_MAGIC); }
			if (loot->rarity == "Rare")		{ _batch->setcolor(EColorCollection::DAD_RARE); }
			if (loot->rarity == "Unique")	{ _batch->setcolor(EColorCollection::DAD_UNIQUE); }

			EFont::active_font->draw(_batch, loot->rarity, xx + 5.0f, yy - dy * move_y); move_y++;

			_batch->setcolor(EColorCollection::WHITE);
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

			_batch->setcolor(EColorCollection::RED);
			EFont::active_font->draw(_batch, "RED: " + std::to_string(loot->red_socket), xx + 5.0f, yy - dy * move_y); move_y++;

			_batch->setcolor(EColorCollection::GREEN);
			EFont::active_font->draw(_batch, "GREEN: " + std::to_string(loot->green_socket), xx + 5.0f, yy - dy * move_y); move_y++;

			_batch->setcolor(EColorCollection::CYAN);
			EFont::active_font->draw(_batch, "BLUE: " + std::to_string(loot->blue_socket), xx + 5.0f, yy - dy * move_y); move_y++;

			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, "WHITE: " + std::to_string(loot->white_socket), xx + 5.0f, yy - dy * move_y); move_y++;


		}
	}

	EFont::active_font->scale = 1.0f;
	EFont::active_font->align_x = Enums::PositionMode::LEFT;
	//_batch->setcolor_alpha(EColorCollection::RED, 0.15f);

	/*for (int i=0; i<100; i++)
	for (int j=0; j<100; j++)
	if (!free_space[j][i])
	{
		_batch->draw_simple_rect(pos_x + j * 8.0f, pos_y + i * 8.0f, 8.0f, 8.0f);
	}*/



}


void EWindowLootSimulator::update_localisation()
{
	for (EButton* b : button_list)
	{b->update_localisation();}
}

bool EWindowLootSimulator::check_condition(std::string _condition, int _num_a, int num_b)
{

	//std::cout << "condition symbol [" << _condition << "] num a [" << _num_a << "] num b [" << num_b << "]" << std::endl;

	if ((_condition == "<") && (_num_a >= num_b)) { return false; }
	if ((_condition == "<=") && (_num_a > num_b)) { return false; }
	if ((_condition == "=") && (_num_a != num_b)) { return false; }
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




	int fb_id = 0;

	for (FilterBlock* fb : _w->filter_block_list)
	{
		if (fb->filter_block_items_button_list.size() <= 0) { match_detect = true; }

		for (EButton* b : fb->filter_block_items_button_list)
		{
			if
			(
				(EString::to_lower(_l->name, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
			)
			{
				match_detect = true;
			}
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
		}

		if (match_detect)
		{
			temp_match = false;
			if (!fb->is_prophecy_active) { temp_match = true; }
			/*
			for (EButton* b : fb->prophecy_list)
			{
				if
					(EString::to_lower(_l->, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
				{
					temp_match = true;
				}
			}*/

			match_detect = temp_match;
		}	

		if (match_detect)
		{
			temp_match = false;
			if (!fb->is_enchantment_active) { temp_match = true; }
			/*
			for (EButton* b : fb->prophecy_list)
			{
				if
					(EString::to_lower(_l->, false).find(EString::to_lower(b->data_string, false)) != std::string::npos)
				{
					temp_match = true;
				}
			}*/

			match_detect = temp_match;
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

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_REQUIRED_LEVEL)) && (!check_condition(fb->required_level_condition, _l->req_level, fb->required_level)))
		{
			match_detect = false;
			if (!_default) { rejection("req", _l); }
		}


		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS)) && (!check_condition(fb->socket_condition, _l->sockets, fb->socket_count)))
		{
			match_detect = false;
			if (!_default) { rejection("sockets", _l); }
		}

		if ((fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_LINKS)) && (!check_condition(fb->links_condition, _l->links, fb->links_count)))
		{
			match_detect = false;
			if (!_default) { rejection("links", _l); }
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





		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP))
				&&
				(
					(_l->red_socket < fb->red_sockets)
					||
					(_l->green_socket < fb->green_sockets)
					||
					(_l->blue_socket < fb->blue_sockets)
					||
					(_l->white_socket < fb->white_sockets)
					)
				)
		{
			match_detect = false;
			if (!_default) { rejection("socket colour", _l); }
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
			}

		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_ELDER_ITEM) != _l->elder_item)
				)
		{
			match_detect = false;
			if (!_default) { rejection("elder item", _l); }
		}

		if
			(
			(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM))
				&&
				(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM) != _l->shaper_item)
				)
		{
			match_detect = false;
			if (!_default) { rejection("shaper item", _l); }
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
			

			if (_default)
			{_l->default_filter_block_link = fb; std::cout << "Match detect [default]! (" << _l->name << ")" << std::endl;}
			else
			{_l->filter_block_link = fb; std::cout << "Match detect! (" << _l->name << ")" << std::endl;}

			//_l->name += " " + std::to_string(fb_id);

			break;
		}

		if (match_detect) { break;}
		fb_id++;
	}



	if (!match_detect)
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

	if (_l->filter_block_link != NULL)
	{
		EFont::active_font->scale = _l->filter_block_link->font_size / 32.0f;
	}
	else
	{
		EFont::active_font->scale = 16.0f / 32.0f;
	}

	w = EFont::active_font->get_width(EFont::active_font, _l->name);

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 200; j++)
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

		w = EFont::active_font->get_width(EFont::active_font, _l->name);
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
			pattern->base_class = pattern_item_list.at(i)->base_class;

			for (int l = 0; l < ItemList::item_list.size(); l++)
			{
				if (EString::to_lower(ItemList::item_list.at(l)->item_name) == EString::to_lower(pattern->item_name))
				{
					pattern->base_class = ItemList::item_list.at(l)->base_class;

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
					(pattern_item_list.at(i)->random_cost_group != "") || (EString::to_lower(pattern_item_list.at(i)->random_cost_group) == "any")
					)
			{
				fill_random_pool(pattern_item_list.at(i)->random_class, pattern_item_list.at(i)->random_subclass, pattern_item_list.at(i)->random_cost_group);
			}


			if (random_item_pool.size() > 0)
			{
				int random_selected_item = rand() % random_item_pool.size();

				pattern->item_name = random_item_pool.at(random_selected_item)->item_name;
				pattern->base_class = random_item_pool.at(random_selected_item)->base_class;

				pattern->height = random_item_pool.at(random_selected_item)->height;
				pattern->width = random_item_pool.at(random_selected_item)->width;

				
			}

			pattern->min_quality = pattern_item_list.at(i)->min_quality;
			pattern->max_quality = pattern_item_list.at(i)->max_quality;

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

			if (pattern->item_name != "")
			{
				prepared_pattern_list.push_back(pattern);
			}
		}
		//**********************************************************************************
		//**********************************************************************************


	}

	drop_count = prepared_pattern_list.size();
	loot_vector_id = 0;
}
