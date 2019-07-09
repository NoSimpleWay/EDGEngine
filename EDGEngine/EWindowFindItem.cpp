#pragma once
#include "EControl.h"
#include "EWindow.h"
#include "DADItem.h"
#include "EButtonItemSearch.h"
#include "EButtonInputSearchItem.h"
#include "ItemList.h"



#include <algorithm>
#include <cctype>

class EWindowFindItem : public EWindow
{
public:
	std::vector<EButton*> button_list;
	EButtonInputSearchItem* input_button;
	string upper_charset = "QWERTYUIOPASDFGHJKLZXCVBNM¨ÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏÐÎËÄÆÝß×ÑÌÈÒÜÁÞ";
	string lower_charset = "qwertyuiopasdfghjklzxcvbnm¸éöóêåíãøùçõúôûâàïðîëäæýÿ÷ñìèòüáþ";
	EButton* target_button=NULL;

	EWindowFindItem() :EWindow()
	{
		is_active = false;
		window_size_x = 1000;
		window_size_y = 500;
		bg_color->set(0.3f, 0.4f, 0.5f, 0.9f);

		EButtonItemSearch* but;
		but= new EButtonItemSearch(0, 0, 40, 40);
		but->master_window = this;
		but->gabarite = DefaultGabarite::gabarite_undefined;
		but->is_active = true;

		button_list.push_back(but);
		

		for (int i = 0; i < 100; i++)
		{
			but = new EButtonItemSearch(0, 0, 40, 40);
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
				b->draw(_batch);

				bx += 43;
				

				if (bx > 800)
				{
					bx = 5;
					by -= 43;

					x_offset = 0;
					y_offset++;
				}

				if ((x_offset == 0) && (y_offset == 0)){bx += 43;}
				if ((x_offset == 0) && (y_offset == 1)){ bx += 43*2;}

				//string s = "x: "+ std::to_string(x_offset)+" y:"+ std::to_string(y_offset);
	
				//b->description_text = s;


			}

			x_offset++;
		}

		input_button->update(_delta);
		input_button->draw(_batch);
	}

	virtual void text_pass(EFont* _font, Batcher* _batch)
	{
		
	}

	string to_lower(string _s, bool _b)
	{
		string result = "";

		for (int zz = 0; zz < _s.length(); zz++)
		{
			for (int yy = 0; yy < upper_charset.length(); yy++)
			{
				if (_b) { std::cout << upper_charset.at(yy) << "(" << _s.at(zz) << ") "; }

				if (upper_charset.at(yy) == _s.at(zz))
				{
					result += lower_charset.at(yy);
					break;
				}
				else
				{
					if (yy+1 >= upper_charset.length())
					{
						result += _s.at(zz);
					}
				}
			}
		}

		return result;
	}

	void fill_search_array(EButton* _b)
	{
		if (input_button->text!="")
		{
			button_list.at(0)->description_text = input_button->text;
			button_list.at(0)->is_active = true;
		}
		else
		{
			button_list.at(0)->is_active = false;
		}

		for (int i=1; i<button_list.size(); i++)
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
						(to_lower(item->item_name,false).find(to_lower(_b->text,false)) != std::string::npos)
						||
						(to_lower(item->item_name_ru,false).find(to_lower(_b->text,false)) != std::string::npos)
					)
					&&
					(order>0)
				)
			{
				if (search_count < 90)
				{
					button_list.at(search_count)->is_active = true;
					button_list.at(search_count)->gabarite = item->gabarite;
					button_list.at(search_count)->description_text = item->item_name + "|" + item->item_name_ru;

					search_count++;
				}
				
			}

			order++;

			
		}


	}


	virtual void button_event(EButton* _b)
	{
		
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