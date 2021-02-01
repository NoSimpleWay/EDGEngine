#include "EWindow.h"
#include "EWindowFilterBlock.h"
#include "EControl.h"
#include "Enums.h"
#include "StaticData.h"
#include "EButtonSlider.h"





	EWindowFilterBlock::EWindowFilterBlock(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		have_bg = false;
		have_shadow = false;

		can_be_closed = false;

		EButton* but = new EButtonSlider(-7, -70, 20, EWindow::SCR_HEIGHT - 80.0f, Enums::ButtonType::BUTTON_FILTER_BLOCK_SCROLL);
		//but->master_block = this;
		but->master_window = this;
		button_list.push_back(but);
		link_to_slider = but;
	}

	EWindowFilterBlock::~EWindowFilterBlock()
	{
	}

	int EWindowFilterBlock::get_id_of_filter_block(FilterBlock* _fb)
	{
		for (int i = 0; i < filter_block_list.size(); i++)
		{
			if (filter_block_list.at(i) == _fb)
			{
				return i;
			}
		}

		return 0;
	}
	
	void EWindowFilterBlock::draw(Batcher* _batch, float _delta)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		//std::cout << "<>" << std::endl;
		int block_index = 0;

		float yy = 90;
		int blocks_count = 0;
		int blocks_order = 0;

		int additional_scroll = 0;

		bool remove_action = false;
		for (int i = 0; i < filter_block_list.size(); i++)
		{
			if (filter_block_list.at(i)->need_remove)
			{
				int sep_id = 0;


				filter_block_list.erase(filter_block_list.begin() + i);

				i--;
				remove_action = true;

				if (filter_block_list.size() <= 0)
				{
					filter_block_list.push_back(new FilterBlock());
				}
			}
		}


		if (remove_action)
		{
			for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
			{
				StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;
			}

			remove_action = false;


		}

		//int real_top_window_id = EButton::top_window_id;

		//if (moved_filter_block != NULL)
		//{EControl::button_pressed = true;}


		for (int i = 0; i < filter_block_list.size(); i++)
		{
			bool first_separator = false;

			block_index = i;

			if
			(
				(i < filter_block_list.size())
				&&
				(!filter_block_list.at(block_index)->is_deactivated)
				&&
				(blocks_order >= EControl::block_scroll)
				&&
				(blocks_count<50)
				&&
				(yy < EWindow::SCR_HEIGHT)
				//this^ line raise FPS from 15 to 60
			)
				/*
							  .-'---`-.
							,'          `.
							|             \
							|              \
							\           _  \
							,\  _    ,'-,/-)\
							( * \ \,' ,' ,'-)
							 `._,)     -',-')
							   \/         ''/
								)        / /
							   /       ,'-'
				*/
			{
				FilterBlock* f = filter_block_list.at(block_index);
				


						FilterBlockSeparator* sep = NULL;

						for (FilterBlockSeparator* sep_list : separator_list)
						{
							//std::cout << "Separator_start: " << sep_list->separator_start << " f: " << f->order_id << std::endl;
							if (sep_list->separator_start == f->order_id)
							{
								sep = sep_list;
								sep_list->link_to_collapse->is_active = true;
								sep_list->link_to_remove->is_active = true;
								sep_list->link_to_caption_text->is_active = true;
								sep_list->link_to_caption_text->is_active = true;
							}
						}



					
					
					if (f->link_to_header_separator->is_active)
					{
							yy += 35.0f;
					}

					f->x = 5;
					f->y = EWindow::SCR_HEIGHT - f->size_y - yy;

					f->size_x = SCR_WIDTH - 40;

					if ((!f->hided_by_separator) || (f->force_enabled)) { f->update(_delta); }

					for (EButton* b : f->header_button_list)
					{
						if (b->is_active)
						{
							b->update(0.015f);
							b->update_additional(0.015f);

							b->default_draw(_batch);
							b->additional_draw(_batch);
						}
					}

					//if (!f->hided_by_separator)
					{
						if ((f->hided_by_separator) && (!f->force_enabled))
						{
							f->size_y = 20.0f;
							if (f->disabled)
							{_batch->setcolor_alpha(EColorCollection::RED, 0.5f);}
							else
							{_batch->setcolor_alpha(EColorCollection::DARK_GRAY, 0.5f);}
							_batch->draw_rect_with_uv(f->x, f->y,  f->size_x, 20, DefaultGabarite::gabarite_wood_button_bg);

							float px = 5.0f;
							for (EButton* b : f->filter_block_items_button_list)
							{
								b->button_x = px;
								b->button_y = 0.0f;

								b->button_size_x = 20.0f;
								b->button_size_y = 20.0f;

								

								b->update(0.015f);
								b->update_additional(0.015f);

								b->default_draw(_batch);
								b->additional_draw(_batch);

								px += 23.0f;
								if (px > SCR_WIDTH - 240) { break; }
							}

						}

						if ((f->hided_by_separator) && (!f->force_enabled))
						{
							_batch->setcolor_255(f->bg_red, f->bg_green, f->bg_blue, f->bg_alpha);
							_batch->draw_rect_with_uv(f->x + f->size_x - 140, f->y, 100, 20, DefaultGabarite::gabarite_white);
							
							_batch->setcolor_255(f->text_color_red, f->text_color_green, f->text_color_blue, f->text_color_alpha);
							EFont::active_font->align_x = Enums::PositionMode::MID;
							EFont::active_font->draw(_batch, "TEXT", f->x + f->size_x - 140 + 13 + EFont::get_width(EFont::active_font, "TEXT"), f->y + 3.0f);

							_batch->setcolor_255(f->rama_red, f->rama_green, f->rama_blue, f->rama_alpha);
							_batch->draw_rama(f->x + f->size_x - 140, f->y, 100, 20, 2, DefaultGabarite::gabarite_white);

							EFont::active_font->align_x = Enums::PositionMode::LEFT;
							


						}

						

						if ((f->hided_by_separator) && (!f->force_enabled))
						{
							yy += f->size_y + 5;
						}
						else
						{
							yy += f->size_y + 15;
						}

						
						
						if ((!f->hided_by_separator) || (f->force_enabled)) { f->draw(_batch); }

						blocks_count++;
					}



					

						//std::cout << "this window id: " << id << " top window id: " << EWindow::top_layer_id << std::endl;
					

					if
					(
						(moved_filter_block != NULL)
						&&
						(EControl::mouse_y >= f->y - 30.0f)
						&&
						(EControl::mouse_y <= f->y + f->size_y)
						//&&
						//(!f->hided_by_separator)
					)
					{
						_batch->setcolor_alpha(EColorCollection::GREEN, 0.9f);
						_batch->draw_simple_rect(f->x, f->y - 15.0f - 15.0f, moved_filter_block->size_x, 15.0f);

						yy += 15.0f + 15.0f;

						if ((EControl::mouse_pressed)&&(!EControl::button_pressed))
						{
							if (f->order_id + 1 >= filter_block_list.size())
							{filter_block_list.push_back(moved_filter_block);}
							else
							{filter_block_list.emplace(filter_block_list.begin() + f->order_id + 1, moved_filter_block);}
							
							/*
							if (f->order_id > moved_filter_block->order_id)
							{filter_block_list.erase(filter_block_list.begin() + moved_filter_block->order_id);}
							else
							{filter_block_list.erase(filter_block_list.begin() + moved_filter_block->order_id + 1);}
							*/

							for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
							{StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;}


							moved_filter_block = NULL;

						}


					}
			}

			if
			(
				(i < filter_block_list.size())
				&&
				(!filter_block_list.at(block_index)->is_deactivated)
			)
			{blocks_order++;}

		}


	}

	void EWindowFilterBlock::text_pass(Batcher* _batch)
	{
		int block_index = 0;

		float yy = 90;
		int blocks_count = 0;
		int blocks_order = 0;

		int additional_scroll = 0;

		for (int i = 0; i < filter_block_list.size(); i++)
		{
			block_index = i;




			if
			(
				(i < filter_block_list.size())
				&&
				(!filter_block_list.at(block_index)->is_deactivated)
				&&
				(blocks_order >= EControl::block_scroll)
				&&
				(blocks_count < 50)
				&&
				(yy < EWindow::SCR_HEIGHT)
			)
			{

				if ((filter_block_list.at(i)->hided_by_separator) && (!filter_block_list.at(i)->force_enabled))
				{
					for (EButton* b : filter_block_list.at(i)->filter_block_items_button_list)
					{

						b->text_pass(_batch);
					}

					for (EButton* b : filter_block_list.at(i)->header_button_list)
					{
						if (b->is_active)
						{
							b->text_pass(_batch);
						}
					}
				}

				blocks_count++;


				if ((!filter_block_list.at(i)->hided_by_separator) || (filter_block_list.at(i)->force_enabled))
				{
					filter_block_list.at(block_index)->text_pass(_batch);
				}
			}

			if
				(
					(i < filter_block_list.size())
					&&
					(!filter_block_list.at(block_index)->is_deactivated)
				)
			{
				blocks_order++;
			}

		}
	}

	void EWindowFilterBlock::update_localisation()
	{
		//std::cout << "try update localisation in window. blocks count: " << filter_block_list.size() << std::endl;
		for (FilterBlock* fb: filter_block_list)
		{
			//std::cout << "buttons count: " << fb->button_list.size() << std::endl;
			fb->update_localisation();

			for (EButton* b : fb->button_list)
			{
				//std::cout << "button: " << b->text << std::endl;
				b->update_localisation();
			}

			/*for (EButton* b : fb->influences_button_list)
			{
				b->update_localisation();
			}

			for (EButton* b : fb->special_status_button_list)
			{
				b->update_localisation();
			}*/

			for (FilterBlock::base_data_button_collection_struct* bdbcs : fb->base_data_button_collection_list)
			{
				if (bdbcs->condition_button != NULL)	{ bdbcs->condition_button->update_localisation(); }
				if (bdbcs->main_button != NULL) { bdbcs->main_button->update_localisation(); }
			}
		}
	}

	void EWindowFilterBlock::recalculate_filter_block_separator()
	{
		for (FilterBlock* fb : filter_block_list)
		{
			fb->have_separator = false;

			fb->contain_start_separator = false;
			fb->contain_end_separator = false;
		}

		for (FilterBlockSeparator* sep_list : separator_list)
		{
			for (int i = sep_list->separator_start; i <= sep_list->separator_end; i++)
			{
				filter_block_list.at(i)->have_separator = true;
				filter_block_list.at(i)->hided_by_separator = sep_list->is_collapsed;

			}

			filter_block_list.at(sep_list->separator_start)->contain_start_separator = true;
			filter_block_list.at(sep_list->separator_end)->contain_end_separator = true;

		}
	}

