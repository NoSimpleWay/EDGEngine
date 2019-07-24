#pragma once
#include "EControl.h"
#include "EWindow.h"
#include "DADItem.h"
#include "EButtonItemSearch.h"
#include "EButtonInputSearchItem.h"
#include "ItemList.h"



#include <algorithm>
#include <cctype>

#include "EUtils.h"

class EWindowFindItem : public EWindow
{
public:
	std::vector<EButton*> button_list;
	EButtonInputSearchItem* input_button;

	Enums::TextSearchMode window_searchs_mode = Enums::TextSearchMode::ITEM;

	EButton* target_button=NULL;
	FilterBlock* master_block=NULL;

	bool have_undefined_input = true;

	EWindowFindItem(int _id) :EWindow(_id)
	{
		is_active = false;
		window_size_x = 1000;
		window_size_y = 500;
		bg_color->set(0.2f, 0.36f, 0.3f, 0.95f);

		EButtonItemSearch* but;
		but= new EButtonItemSearch(0, 0, 40, 40, Enums::ButtonType::BUTTON_SEARCH_ITEM);
		but->master_window = this;
		but->gabarite = DefaultGabarite::gabarite_undefined;
		but->is_active = true;

		button_list.push_back(but);
		

		for (int i = 0; i < 150; i++)
		{
			but = new EButtonItemSearch(0, 0, 40, 40, Enums::ButtonType::BUTTON_SEARCH_ITEM);
			but->master_window = this;

			button_list.push_back(but);
		}

		input_button = new EButtonInputSearchItem(0, -70, 300, 30);
		input_button->master_window = this;
	}

	void update()
	{

	}


	virtual void draw(Batcher* _batch, float _delta)
	{
		float bx = 5;
		float by = -120;

		int x_offset = 0;
		int y_offset = 0;

		bool undefined_button = true;

		for (EButton* b : button_list)
		{
			if (b->is_active)
			{
				b->button_x = bx;
				b->button_y = by;

				b->update(_delta);
				b->default_draw(_batch);

				bx += b->button_size_x + 7.0f;
				

				if (bx+b->button_size_x > 930)
				{
					bx = 5;
					by -= b->button_size_y + 7.0f;

					x_offset = 0;
					y_offset++;
				}

				if (button_list.at(0)->is_active)
				{
					if ((x_offset == 0) && (y_offset == 0)) { bx = button_list.at(0)->button_size_x + 40.0f + 7.0f; }
					if ((x_offset == 0) && (y_offset == 1)) { bx = button_list.at(0)->button_size_x + 40.0f + 7.0f; }
				}



				//string s = "x: "+ std::to_string(x_offset)+" y:"+ std::to_string(y_offset);
	
				//b->description_text = s;


			}

			x_offset++;
		}

		input_button->update(_delta);
		input_button->default_draw(_batch);
	}

	virtual void text_pass(EFont* _font, Batcher* _batch)
	{
		
	}


	void fill_search_array(EButton* _b)
	{
		if (window_searchs_mode == Enums::TextSearchMode::ITEM)
		{
			if (input_button->text != "")
			{
				button_list.at(0)->description_text = input_button->text;
				button_list.at(0)->is_active = true;
			}
			else
			{
				button_list.at(0)->is_active = false;
			}

			for (int i = 1; i < button_list.size(); i++)
			{
				button_list.at(i)->is_active = false;
			}

			int search_count = 1;
			int order = 0;
			for (DADItem* item : ItemList::item_list)
			{
				//std::cout << "item_list_name |" << item->item_name << "| button description |" <<  _b->text << "|" << std::endl;


				if
					(
					(
						(EString::to_lower(item->item_name, false).find(EString::to_lower(_b->text, false)) != std::string::npos)
						||
						(EString::to_lower(item->item_name_ru, false).find(EString::to_lower(_b->text, false)) != std::string::npos)
						)
						&&
						(order > 0)
						)
				{
					if (search_count < 150)
					{
						button_list.at(search_count)->is_active = true;
						button_list.at(search_count)->gabarite = item->gabarite;
						button_list.at(search_count)->description_text = item->item_name + " (" + item->item_name_ru + ")";

						search_count++;
					}

				}

				order++;


			}
		}

		if (window_searchs_mode == Enums::TextSearchMode::DEFAULT_DROP_SOUND)
		{
			button_list.at(0)->is_active = true;

			for (int i = 1; i < button_list.size(); i++)
			{
				button_list.at(i)->is_active = false;
			}

			int search_count = 1;
			int order = 0;
			for (EButton* b: button_list)
			{
				//std::cout << "item_list_name |" << item->item_name << "| button description |" <<  _b->text << "|" << std::endl;


				if
					(
					(
						(EString::to_lower(b->text, false).find(EString::to_lower(_b->text, false)) != std::string::npos)
						)
						&&
						(order > 0)
						)
				{
					if (search_count < ESound::default_drop_sound_name.size())
					{
						b->is_active = true;
						
						search_count++;
					}

				}



				order++;
			}
		}

		if (window_searchs_mode == Enums::TextSearchMode::CUSTOM_DROP_SOUND)
		{
			button_list.at(0)->is_active = true;

			for (int i = 1; i < button_list.size(); i++)
			{
				button_list.at(i)->is_active = false;
			}

			int search_count = 1;
			int order = 0;
			for (EButton* b : button_list)
			{
				if
					(
					(
						(EString::to_lower(b->text, false).find(EString::to_lower(_b->text, false)) != std::string::npos)
						)
						&&
						(order > 0)
						)
				{
					if (search_count < ESound::custom_drop_sound_name.size())
					{
						b->is_active = true;


						search_count++;
					}

				}

				order++;
			}
		}
	}


	virtual void button_event(EButton* _b)
	{
		int data_index=0;
		master_block = _b->master_block;

		for (EButton* b : button_list)
		{
			b->master_block = master_block;
		}

		if (window_searchs_mode == Enums::TextSearchMode::ITEM)
		{
			have_undefined_input = true;

			for (EButton* b : button_list)
			{
				b->button_size_x	= 40;
				b->button_size_y	= 40;
				b->have_text		= false;
				b->have_icon		= true;

				//b->gabarite = DefaultGabarite::gabarite_undefined;
				b->button_type = Enums::ButtonType::BUTTON_SEARCH_ITEM;

				
			}
		}

		if (window_searchs_mode == Enums::TextSearchMode::DEFAULT_DROP_SOUND)
		{
			have_undefined_input = false;

			for (EButton* b : button_list)
			{
				if (data_index < ESound::default_drop_sound_name.size())
				{
					b->button_size_y = 21;

					b->have_text = true;
					b->have_icon = false;

					if (data_index>=0)
					{b->text = ESound::default_drop_sound_name.at(data_index);}
					else
					{b->text="?";}

					b->button_size_x = EFont::get_width(EFont::font_arial, b->text) + 5.0f;
					b->is_active = true;
					b->button_type = Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND;
					b->data_id = data_index;

					if (data_index != master_block->alert_sound_id)
					{
						b->bg_color->set(0.8f, 0.7f, 0.6f, 0.5f);
					}
					else
					{
						b->bg_color->set(1.0f, 0.8f, 0.5f, 0.6f);
					}

					data_index++;
				}
				else
				{
					b->is_active = false;
				}
			}
		}

		if (window_searchs_mode == Enums::TextSearchMode::CUSTOM_DROP_SOUND)
		{
			have_undefined_input = false;

			for (EButton* b : button_list)
			{
				if (data_index < ESound::custom_drop_sound_name.size())
				{
					b->button_size_y = 21;

					b->have_text = true;
					b->have_icon = false;

					if (data_index >= 0)
					{
						b->text = ESound::custom_drop_sound_name.at(data_index);
					}
					else
					{
						b->text = "?";
					}

					b->button_size_x = EFont::get_width(EFont::font_arial, b->text) + 5.0f;
					b->is_active = true;
					b->button_type = Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND;
					b->data_id = data_index;

					b->bg_color->set(0.8f, 0.7f, 0.6f, 0.5f);

					data_index++;
				}
				else
				{
					b->is_active = false;
				}
			}
		}
	}

	virtual void text_pass(Batcher* _batch)
	{
		for (EButton* b : button_list)
		{
			if (b->is_active)
			{
				b->text_pass(_batch);
			}
		}
	}

	virtual void input_event(EButton* _b)
	{
		//std::cout << "to lower: " << to_lower(_b->text,true)<<" normal:"<<_b->text << std::endl;
		fill_search_array(_b);


		if (_b->master_window != NULL)
		{
			std::cout << "Button name: " + _b->text << std::endl;
		}
		else
		{
			std::cout << "windows of button is NULL" << endl;
		}
	}

};