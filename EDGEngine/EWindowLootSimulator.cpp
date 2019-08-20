
#include "EControl.h"
#include "Enums.h"

#include "StaticData.h"
#include "EWindowLootSimulator.h"
#include <time.h>


	EWindowLootSimulator::EWindowLootSimulator(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		window_size_x = 1600.0;
		window_size_y = 900.0f;

		align_x = Enums::PositionMode::LEFT;

		bg_color->set_alpha(EColorCollection::GRAY, 0.5f);

		is_active = false;
	}

	void EWindowLootSimulator::fill_random_pool(std::string _class, std::string _subclass, std::string _cost)
	{
	

		for (DADItem* item : ItemList::item_list)
		{
			if
			(
				((EString::to_lower(_class) == EString::to_lower(item->base_class)) || (_class == ""))
				&&
				((EString::to_lower(_subclass) == EString::to_lower(item->subcategory)) || (_subclass == ""))
				&&
				((EString::to_lower(_cost) == EString::to_lower(item->cost_group)) || (_cost == ""))
			)
			{
				random_loot_pool.push_back(item);
			}
		}

		
	}

	void EWindowLootSimulator::update(float _d)
	{
		drop_cooldown -= _d;

		if (drop_cooldown < 0)
		{
			drop_cooldown += 0.1f;

			if (drop_count > 0)
			{
				int selected = rand() % prepared_pattern_list.size();

				LootItem* loot = new LootItem();
//				loot->name = ItemList::item_list.at(rand() % ItemList::item_list.size())->item_name;

				
				//***************************ITEM NAME SECTION**************************************
				//**********************************************************************************
				loot->name = prepared_pattern_list.at(selected)->item_name;
				loot->base_class = prepared_pattern_list.at(selected)->base_class;

				std::cout << "base class of item [" << loot->name << "] is <" << loot->base_class << ">" << std::endl;
				//**********************************************************************************
				//**********************************************************************************

				prepared_pattern_list.erase(prepared_pattern_list.begin() + selected);

				main_loot_item_list.push_back(loot);

				find_filter_block(loot);
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
		_batch->setcolor_alpha(EColorCollection::GRAY, 0.5f);
		_batch->draw_simple_rect(pos_x, pos_y, 800.0f, 800.0f);

		for (LootItem* loot:main_loot_item_list)
		{
			//loot->filter_block_link = StaticData::window_filter_block->filter_block_list.at(rand() % StaticData::window_filter_block->filter_block_list.size());

			EFont::font_arial->set_align_once(Enums::PositionMode::MID);

			if (loot->filter_block_link != NULL)
			{EFont::font_arial->scale = loot->filter_block_link->font_size / 32.0f;}
			else
			{EFont::font_arial->scale = 20.0f / 32.0f;}

			float w = EFont::font_arial->get_width(EFont::font_arial, loot->name);
			float h = 20.0f * EFont::font_arial->scale;

			if (loot->filter_block_link != NULL)
			{_batch->setcolor(loot->filter_block_link->bg_red / 255.0f, loot->filter_block_link->bg_green / 255.0f, loot->filter_block_link->bg_blue / 255.0f, loot->filter_block_link->bg_alpha / 255.0f);}
			else
			{_batch->setcolor_alpha (EColorCollection::GRAY, 0.8f);}
			_batch->draw_rect_with_uv(pos_x + loot->pos_x, pos_y + loot->pos_y, w + 13.0f, h, DefaultGabarite::gabarite_white);

			if (loot->filter_block_link != NULL)
			{_batch->setcolor (loot->filter_block_link->text_color_red / 255.0f, loot->filter_block_link->text_color_green / 255.0f, loot->filter_block_link->text_color_blue / 255.0f, loot->filter_block_link->text_color_alpha / 255.0f);}
			else
			{_batch->setcolor(EColorCollection::WHITE);}
			EFont::font_arial->draw(_batch, loot->name, pos_x + loot->pos_x + w / 2.0f + 5.0f, pos_y + loot->pos_y + 3.0f);

			if (loot->filter_block_link != NULL)
			{_batch->setcolor(loot->filter_block_link->rama_red / 255.0f, loot->filter_block_link->rama_green / 255.0f, loot->filter_block_link->rama_blue / 255.0f, loot->filter_block_link->rama_alpha / 255.0f);}
			else
			{_batch->setcolor_alpha (EColorCollection::WHITE, 0.7f);}
			_batch->draw_rama(pos_x + loot->pos_x, pos_y + loot->pos_y, w + 13.0f, h, 3.0f, DefaultGabarite::gabarite_white);
			

			EFont::font_arial->scale = 1.0f;

		}

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
	}

	bool EWindowLootSimulator::check_condition(std::string _condition, int _num_a, int num_b)
	{

		std::cout << "condition symbol [" << _condition << "] num a [" << _num_a << "] num b [" << num_b << "]" << std::endl;

		if ((_condition == "<") && (_num_a >= num_b)) { return false; }
		if ((_condition == "<=") && (_num_a > num_b)) { return false; }
		if ((_condition == "=") && (_num_a != num_b)) { return false; }
		if ((_condition == ">=") && (_num_a < num_b)) { return false; }
		if ((_condition == ">") && (_num_a <= num_b)) { return false; }

		return true;
	}

	void EWindowLootSimulator::find_filter_block(LootItem* _l)
	{
		bool match_detect = false;

		bool temp_match = false;

		


			int fb_id = 0;

			for (FilterBlock* fb : StaticData::window_filter_block->filter_block_list)
			{
				if (fb->filter_block_items_button_list.size() <= 0) { match_detect = true; }
				for (EButton* b : fb->filter_block_items_button_list)
				{
					if
					(EString::to_lower(b->data_string, false).find(EString::to_lower(_l->name, false)) != std::string::npos)
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
						(EString::to_lower(b->data_string, false).find(EString::to_lower(_l->base_class, false)) != std::string::npos)
						{
							temp_match = true;
						}
					}

					match_detect = temp_match;
				}


				if ((fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SOCKETS)) && (!check_condition(fb->socket_condition, _l->sockets, fb->socket_count)))
				{
					match_detect = false;
				}

				if
				(
					(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP))
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
				}

				//std::cout << "is active=" << std::to_string(fb->is_synthesised_item_active) << " is synthesised block=" << std::to_string(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SYNTHESISED)) << "is synthesised item=" << std::to_string(_l->synthesised_item) << std::endl;

				if
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED))
					&&
					(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SYNTHESISED) != _l->synthesised_item)
				)
				{match_detect = false;}

				if
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED))
					&&
					(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_FRACTURED) != _l->fractured_item)
				)
				{match_detect = false;}


				
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
				{match_detect = false;}

				if
				(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM))
					&&
					(fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM) != _l->shaper_item)
				)
				{match_detect = false;}



				if (match_detect)
				{
					_l->filter_block_link = fb;

					_l->name += " " + std::to_string(fb_id);

					break;
				}

				fb_id++;
			}

			

			if (!match_detect)
			{
				_l->filter_block_link = NULL;
				_l->name += " #";
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
				EFont::font_arial->scale = _l->filter_block_link->font_size / 32.0f;
			}
			else
			{
				EFont::font_arial->scale = 16.0f / 32.0f;
			}

			w = EFont::font_arial->get_width(EFont::font_arial, _l->name);

			for (int i=0; i<100; i++)
			for (int j=0; j<200; j++)
			{
					bool detect_block = false;

					for (int sy = i; sy <= i + (int)(EFont::font_arial->scale * 22.0f / 8.0f); sy++)
					for (int sx = j; sx <= j + (int)(w / 8.0f) + 1; sx++)
					{
						if ((sx >= 0) && (sy > 0) && (sx < 200) && (sy < 100) && (free_space[sx][sy]))
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
						float xx = j - 100.0f + w / 16.0f;
						float yy = i - 50.0f + EFont::font_arial->scale * 22.0f / 16.0f;


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

				w = EFont::font_arial->get_width(EFont::font_arial, _l->name);
				for (int sy = good_pos_y - 0.0f; sy <= good_pos_y + (int)(EFont::font_arial->scale * 22.0f / 8.0f) + 1; sy++)
				for (int sx = good_pos_x - 3.0f; sx <= good_pos_x + (int)(w / 8.0f) + 3; sx++)
				{
					if ((sx < 200) && (sy < 100) && (sx >= 0) && (sy >= 0))
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

		for (int i = 0; i < 100; i++)
		for (int j = 0; j < 200; j++)
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

				random_loot_pool.clear();

				pattern->item_name = pattern_item_list.at(i)->item_name;
				pattern->base_class = pattern_item_list.at(i)->base_class;
				if
					(
					(pattern_item_list.at(i)->random_class != "")
					||
					(pattern_item_list.at(i)->random_subclass != "")
					||
					(pattern_item_list.at(i)->random_cost_group != "")
					)
				{
					fill_random_pool(pattern_item_list.at(i)->random_class, pattern_item_list.at(i)->random_subclass, pattern_item_list.at(i)->random_cost_group);
				}


				if (random_loot_pool.size() > 0)
				{
					int random_selected_item = rand() % random_loot_pool.size();

					pattern->item_name = random_loot_pool.at(random_selected_item)->item_name;
					pattern->base_class = random_loot_pool.at(random_selected_item)->base_class;
				}

				prepared_pattern_list.push_back(pattern);
			}
			//**********************************************************************************
			//**********************************************************************************

			
		}

		drop_count = prepared_pattern_list.size();
		loot_vector_id = 0;
	}
