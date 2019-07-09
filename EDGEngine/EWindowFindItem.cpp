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
	string upper_charset = "QWERTYUIOPASDFGHJKLZXCVBNM¨ÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏĞÎËÄÆİß×ÑÌÈÒÜÁŞ";
	string lower_charset = "qwertyuiopasdfghjklzxcvbnm¸éöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáş";

	EWindowFindItem() :EWindow()
	{
		is_active = false;
		size_x = 1000;
		size_y = 500;

		for (int i = 0; i < 100; i++)
		{
			button_list.push_back(new EButtonItemSearch(0,0,40,40));

		}

		input_button = new EButtonInputSearchItem(0, 0, 300, 30);
		input_button->master_window = this;
	}

	void update()
	{

	}


	virtual void draw(Batcher* _batch, float _delta)
	{
		float bx = 0;
		float by = 0;

		for (EButton* b : button_list)
		{
			if (b->is_active)
			{
				b->button_x = bx;
				b->button_y = by;

				b->update(_delta);
				b->draw(_batch);

				bx += 43;
				if (bx > 400)
				{
					bx = 0;
					by += 43;
				}
			}
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
		for (EButton* b : button_list)
		{
			b->is_active = false;
		}

		int search_count = 0;
		
		for (DADItem* item : ItemList::item_list)
		{
			//std::cout << "item_list_name |" << item->item_name << "| button description |" <<  _b->text << "|" << std::endl;

			
			if
				(
				(to_lower(item->item_name,false).find(_b->text) != std::string::npos)
				||
				(item->item_name_ru.find(_b->text) != std::string::npos)
				||
				(item->item_name==_b->text)
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

			
		}


	}

	virtual void button_event(EButton* _b)
	{
		
	}

	virtual void input_event(EButton* _b)
	{
		std::cout << "to lower: " << to_lower(_b->text,true)<<" normal:"<<_b->text << std::endl;
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