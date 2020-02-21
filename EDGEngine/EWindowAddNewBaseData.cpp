#pragma once
#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonAddNewBaseData.h"
#include "ExplicitGroup.h"
#include "EButtonText.h"

class EWindowAddNewBaseData : public EWindow
{
public:
	//std::vector<FilterBlock*> filter_block_list;
	Enums::WindowSearchMode window_searchs_mode = Enums::WindowSearchMode::ITEM;

	EWindowAddNewBaseData(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = 300;
		window_size_y = 100;

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::MID;

		have_bg = true;

		is_active = false;


		//StaticData::window_add_new_base_data->is_active = true;
	}



	virtual void update(float _d)
	{
		/*float pos_y=-25;
		for (EButton* b : button_list)
		{
			if (b->master_block->base_filter_separator.at(b->data_id))
			{
				pos_y -= 10;
			}

			b->button_y = pos_y;
			

			pos_y -= 23;

		}*/
	}



	virtual void button_event(EButton* _b)
	{
		window_size_y = 100;
		is_active = true;
		button_list.clear();
		int data_id = 0;

		if (window_searchs_mode == Enums::WindowSearchMode::BASE_DATA_VERTICAL_LIST)
		{
			window_size_x = 1024;
			window_size_y = 500;
			
			float bpos_x = 0.0f;
			float bpos_y = 0.0f;

			float bpos_min_y = 0.0f;
			float bpos_max_y = 0.0f;

			float max_size_x = 0.0f;
			for (bool b : _b->master_block->base_filter_data_active)
			{
				//if (!b)
				{
					EButtonAddNewBaseData* but = new EButtonAddNewBaseData(0, 0, 200.0f, 21.0f);

					but->position_mode_x = Enums::PositionMode::LEFT;
					but->master_window = this;
					but->text = _b->master_block->base_filter_data_name.at(data_id);
					but->data_id = data_id;
					but->button_x = 0;

					if (b)
					{
						but->bg_color->set_alpha(EColorCollection::DARK_GRAY, 0.5f);
						but->text_color->set(EColorCollection::GRAY);
						but->have_rama = false;
					}
					else
					{
						but->bg_color->set(EColorCollection::LIGHT_GRAY);
						but->text_color->set(EColorCollection::BLACK);
						but->rama_color->set(EColorCollection::DARK_GRAY);
						but->have_rama = true;
					}

					but->master_window = this;
					but->master_block = _b->master_block;

					if (but->master_block->base_filter_separator.at(but->data_id))
					{
						bpos_x += but->button_size_x + 10.0f;



						if (bpos_x + but->button_size_x + 10.0f >= window_size_x)
						{
							

							bpos_min_y = bpos_max_y - 20.0f;
							bpos_y = bpos_min_y;
							bpos_x = 0.0f;
						}
						else
						{
							if (bpos_x + but->button_size_x + 10.0f > max_size_x)
							{
								max_size_x = bpos_x + but->button_size_x + 10.0f;
							}
						}

						bpos_y = bpos_min_y;
					}

					but->button_y = bpos_y - 10.0f;
					bpos_y -= but->button_size_y + 5.0f;
					if (bpos_y < bpos_max_y)
					{
						bpos_max_y = bpos_y;
					}

					but->button_x = bpos_x + 10.0f;
					

					

					if (abs(bpos_y - but->button_size_y - 5.0f) >= window_size_y)
					{
						window_size_y += abs(but->button_size_y + 5.0f);
					}


					if (bpos_x + but->button_size_x + 10.0f >= window_size_x)
					{


						bpos_min_y = bpos_max_y - 20.0f;
						bpos_y = bpos_min_y;
						bpos_x = 0.0f;
					}
					else
					{
						if (bpos_x + but->button_size_x + 10.0f > max_size_x)
						{
							max_size_x = bpos_x + but->button_size_x + 10.0f;
						}
					}


					button_list.push_back(but);


					//window_size_y += 23;
				}

				data_id++;
			}

			window_size_x = max_size_x + 10.0f;
		}

		if (window_searchs_mode == Enums::WindowSearchMode::EXPLICIT_PROPHECY_CLASS_VERTICAL_LIST)
		{
			bool free_space_detected = false;

			window_size_x = 400;
			window_size_y = 50;

			for (ExplicitGroup* ex : _b->master_block->explicit_list)
			{
				if (!free_space_detected)
				{
					if (ex->is_active == false)
					{ free_space_detected = true; }
					else
					{ data_id++; }
				}


				
			}

			if (!_b->master_block->is_base_class_active)
			{
				EButton* but = new EButtonText(0, 0, 300, 20, Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST);

				but->master_window = this;
				but->button_x = 0;

				but->master_window = this;
				but->master_block = _b->master_block;

				button_list.push_back(but);

				window_size_y += 40;
			}





			if (!_b->master_block->is_prophecy_active)
			{
				EButton* but = new EButtonText(0, 0, 300, 20, Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST);

				but->master_window = this;
				but->button_x = 0;

				but->master_window = this;
				but->master_block = _b->master_block;

				button_list.push_back(but);

				window_size_y += 30;
			}

			if (!_b->master_block->is_enchantment_active)
			{
				EButton* but = new EButtonText(0, 0, 300, 20, Enums::ButtonType::BUTTON_ACTIVE_ENCHANTEMENT_LIST);

				but->master_window = this;
				but->button_x = 0;

				but->master_window = this;
				but->master_block = _b->master_block;

				button_list.push_back(but);

				window_size_y += 30;
			}

			if (free_space_detected)
			{
				EButton* but = new EButtonText(0, 0, 300, 20, Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP);

				but->master_window = this;
				//but->text = "Add new explicit list";
				but->data_id = data_id;
				but->button_x = 0;

				but->master_window = this;
				but->master_block = _b->master_block;

				but->data_id = data_id;


				button_list.push_back(but);

				window_size_y += 30;
			}

			float by = -25.0f;

			for (EButton* b : button_list)
			{
				b->button_y = by;
				by -= 35.0f;
			}
		}
		
		/*
		if (window_searchs_mode == Enums::WindowSearchMode::BASE_CLASS_SEARCH_LIST)
		{

			if (!_b->master_block->is_base_class_active)
			{
				EButton* but = new EButtonText(0, 0, 200, 17, Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST);

				but->master_window = this;
				but->button_x = 0;

				but->master_window = this;
				but->master_block = _b->master_block;

				button_list.push_back(but);

				window_size_y += 23;
			}
		}*/

		update_localisation();
	}

	virtual void update_localisation()
	{
		std::cout << "try update localisation (ECP button)!" << std::endl;
		for (EButton* b : button_list)
		{
			b->update_localisation();
		}
	}
};