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
				filter_block_list.erase(filter_block_list.begin() + i);

				for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
				{
					if (sep->separator_start > filter_block_list.at(i)->order_id)
					{
						sep->separator_start--;
					}

					if (sep->separator_end >= filter_block_list.at(i)->order_id)
					{
						sep->separator_end--;
					}
				}

				StaticData::window_filter_block->recalculate_filter_block_separator();

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

		for (FilterBlockSeparator* sep_list : separator_list)
		{
			sep_list->link_to_collapse->is_active = false;
			sep_list->link_to_remove->is_active = false;
			sep_list->link_to_caption_text->is_active = false;
		}

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
				(blocks_count<10)
			)
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


						

						if (sep != NULL)
						{
							sep->x = f->x;
							sep->y = EWindow::SCR_HEIGHT - yy - 20.0f;

							sep->size_x = f->size_x;
							sep->size_y = 16.0f;

							_batch->setcolor_alpha(EColorCollection::CYAN, 0.5f);
							_batch->draw_simple_rect(f->x+635.0f, EWindow::SCR_HEIGHT - yy - 20.0f, f->size_x-635.0f, 16.0f);

							yy += 27.0f;
						}
					

					f->x = 5;
					f->y = EWindow::SCR_HEIGHT - f->size_y - yy;

					f->size_x = SCR_WIDTH - 40;

					if (!f->hided_by_separator)
					{
						yy += f->size_y + 15;

						f->update(_delta);
						f->draw(_batch);

						blocks_count++;
					}

					

						//std::cout << "this window id: " << id << " top window id: " << EWindow::top_layer_id << std::endl;
						sep = NULL;

						for (FilterBlockSeparator* sep_list : separator_list)
						{
							if (sep_list->separator_end == f->order_id) { sep = sep_list; }
						}

						if (sep != NULL)
						{
							_batch->setcolor_alpha(EColorCollection::DARK_GRAY, 0.9f);
							_batch->draw_simple_rect(f->x, EWindow::SCR_HEIGHT - yy - 15.0f, f->size_x, 20.0f);
							_batch->setcolor(EColorCollection::WHITE);
							EFont::active_font->draw(_batch, "End of '" + sep->name + "' separator   (you can drag me!)", f->x + 16.0f, EWindow::SCR_HEIGHT - yy - 9.0f);

							yy += 23.0f;
						}

						if
						(
							(EControl::mouse_pressed)
							&&
							(!EControl::button_pressed)
							&&
							(drag_end_separator == NULL)
							&&
							(EControl::mouse_y >= f->y - 50.0f)
							&&
							(EControl::mouse_y <= f->y + f->size_y)
							&&
							(!f->hided_by_separator)
							&&
							(EButton::top_window_id == id)
							&&
							(f->have_separator)
							&&
							(moved_filter_block == NULL)
						)
						{
							drag_end_separator = sep;
							EControl::button_pressed = true;
						}

					



					if
					(
						(drag_end_separator != NULL)
						&&
						(EControl::mouse_y >= f->y - 50.0f)
						&&
						(EControl::mouse_y <= f->y + f->size_y)
						&&
						(f->order_id >= drag_end_separator->separator_start)
					)
					{
						_batch->setcolor_alpha(EColorCollection::GREEN, 0.9f);
						_batch->draw_simple_rect(f->x, f->y - 15.0f - 15.0f, f->size_x, 15.0f);
						yy += 15.0f + 15.0f;

						if (!EControl::mouse_pressed)
						{
							//for (int i = drag_end_separator->separator_start; i <= drag_end_separator->separator_end; i++)
							//{filter_block_list.at(i)->have_separator = false;}

							drag_end_separator->separator_end = f->order_id;

							//for (int i = drag_end_separator->separator_start; i <= drag_end_separator->separator_end; i++)
							//{filter_block_list.at(i)->have_separator = true;}

							drag_end_separator = NULL;

							recalculate_filter_block_separator();
						}
					}

					

					if
					(
						(moved_filter_block != NULL)
						&&
						(EControl::mouse_y >= f->y - 30.0f)
						&&
						(EControl::mouse_y <= f->y + f->size_y)
						&&
						(!f->hided_by_separator)
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

							

							for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
							{
								if (sep->separator_start >= moved_filter_block->order_id)
								{
									sep->separator_start++;
								}

								if (sep->separator_end >= moved_filter_block->order_id)
								{
									sep->separator_end++;
								}
							}

							moved_filter_block = NULL;

							recalculate_filter_block_separator();
						}


					}
			}

			if
			(
				(i < filter_block_list.size())
				&&
				(!filter_block_list.at(block_index)->is_deactivated)
				&&
				(!filter_block_list.at(block_index)->hided_by_separator)
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
				(blocks_count < 10)
				&&
				(!filter_block_list.at(block_index)->hided_by_separator)
			)
			{
				blocks_count++;

				filter_block_list.at(block_index)->text_pass(_batch);
			}

			if
				(
					(i < filter_block_list.size())
					&&
					(!filter_block_list.at(block_index)->is_deactivated)
					&&
					(!filter_block_list.at(block_index)->hided_by_separator)
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
		}
	}

	void EWindowFilterBlock::recalculate_filter_block_separator()
	{
		for (FilterBlock* fb : filter_block_list)
		{
			fb->have_separator = false;
		}
		for (FilterBlockSeparator* sep_list : separator_list)
		{
			for (int i = sep_list->separator_start; i <= sep_list->separator_end; i++)
			{
				filter_block_list.at(i)->have_separator = true;
			}
		}
	}

