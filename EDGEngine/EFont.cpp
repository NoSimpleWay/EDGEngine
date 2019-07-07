#include "EFont.h"
#include <string>

#include <iostream>
#include "Batcher.h"
#include <fstream>

using namespace std;

float x[512];
float y[512];

float size_x[512];
float size_y[512];

float real_size_x[512];
float real_size_y[512];

float offset_x[512];
float offset_y[512];

float advance[512];
string name[512];

bool comma_is_open = true;
int font_array_id = 32;

float x_addind = 0;

bool show_console_info = false;

EFont::EFont()
{
}



EFont::~EFont()
{
}

/*
int get_size()
{

}
*/
float EFont::get_data_from_sub_data(string _s)
{
	string get_data = "";

	comma_is_open = false;

	//cout << "parse sub_data:" << _s << endl;

	for (int j = 0; j < _s.length(); j++)
	{
		
		if (_s.at(j) == '"')
		{
			if (!comma_is_open)
			{ comma_is_open = true; }
			else
			{
				//cout << "try return:" << get_data << endl;
				return std::stof(get_data);
			}
		}
		else
		{
			if (comma_is_open) { get_data += _s.at(j); }
		}
	}
}

bool compare_with_key(string _data, string _key)
{
	if (_data.substr(0, _key.length()) == _key)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EFont::final_draw(Batcher* _batcher, string _s, float _x, float _y)
{
	

	for (int sym = 0; sym < _s.length(); sym++)
	{
		float a = 0.5f;
		int target_symbol = (int)_s.at(sym);

		if (target_symbol < 0) { target_symbol += 256; }



		_batcher->draw_rect_with_uv
		(
			_x + x_adding - offset_x[target_symbol],
			_y - offset_y[target_symbol],

			real_size_x[target_symbol],
			real_size_y[target_symbol],

			x[target_symbol],
			y[target_symbol] - size_y[target_symbol],

			x[target_symbol] + size_x[target_symbol],
			y[target_symbol]
		);

		x_adding += real_size_x[target_symbol] - offset_x[target_symbol];
	}
}
void EFont::draw(Batcher* _batcher, string _s, float _x, float _y)
{
	x_adding = 0;
	final_draw(_batcher, _s, _x, _y);
}

void EFont::add_draw(Batcher* _batcher, string _s, float _x, float _y)
{
	final_draw(_batcher, _s, _x, _y);
}

void EFont::load_font(string _path)
{
	string line;
	string sub_data;
	int data_order;

	ifstream myfilez("data/font_arial.txt");

	for (int i = 0; i < 300; i++)
	{
		x[i] = 0;
		y[i] = 0;
		size_x[i] = 0;
		size_y[i] = 0;
		offset_x[i] = 0;
		offset_y[i] = 0;
	}
	
	if (myfilez.is_open())
	{
		font_array_id = 31;

		while ((getline(myfilez, line))&&(font_array_id<300))
		{
			comma_is_open = true;
			data_order = 0;
			//cout << line << '\n';

			//cout << "line #" << font_array_id;

			if (font_array_id>31)
			for (int i = 0; i < line.length(); i++)
			{
				
				
				if ((line.at(i) == ' ')||(i+1>= line.length()))
				{
					
					//if (show_console_info)cout << "subdata | " << sub_data << " |" << endl;
					if (compare_with_key (sub_data,"text="))
					{
						if (show_console_info) cout << "name | " << sub_data << " | id:" <<font_array_id << endl;
						name[font_array_id] =sub_data;
					}
					if (compare_with_key (sub_data,"x="))
					{
						if (show_console_info) cout << "x pos | " << get_data_from_sub_data(sub_data) << " |" << endl;
						x[font_array_id] = get_data_from_sub_data(sub_data);
					}
					
					if (compare_with_key(sub_data, "y="))
					{ 
						if (show_console_info) cout << "y pos | " << get_data_from_sub_data(sub_data) << " |" << endl;
						y[font_array_id] = get_data_from_sub_data(sub_data);
					}
					
					if (compare_with_key(sub_data, "width="))
					{
						if (show_console_info) cout << "x size | " << get_data_from_sub_data(sub_data) << " |" << endl;
						real_size_x[font_array_id] = size_x[font_array_id] = get_data_from_sub_data(sub_data);
					}

					if (compare_with_key(sub_data, "height="))
					{
						real_size_y[font_array_id] = size_y[font_array_id] = get_data_from_sub_data(sub_data);
						if (show_console_info) cout << "y size | " << size_y[font_array_id] << " |" << endl;
					}

					if (compare_with_key(sub_data, "origin-x="))
					{
						if (show_console_info) cout << "x offset | " << get_data_from_sub_data(sub_data) << " |" << endl;
						offset_x[font_array_id] = get_data_from_sub_data(sub_data);
					}

					if (compare_with_key(sub_data, "origin-y="))
					{
						
						offset_y[font_array_id] = size_y[font_array_id]-get_data_from_sub_data(sub_data);
						if (show_console_info) cout << "y offset | size_y=" << size_y[font_array_id] <<" offset=" << get_data_from_sub_data(sub_data) << " result=" << offset_y[font_array_id] << " |" << endl;

	
					}

					if (compare_with_key(sub_data, "advance="))
					{
						if (show_console_info) cout << "advance | " << get_data_from_sub_data(sub_data) << " |" << endl;
						advance[font_array_id] = get_data_from_sub_data(sub_data);

						
						size_x[font_array_id]= size_x[font_array_id]/4096.0f;
						size_y[font_array_id]= size_y[font_array_id]/4096.0f;

						x[font_array_id]= x[font_array_id]/4096.0f;
						y[font_array_id]= 1-y[font_array_id]/4096.0f;
					}

					


					/*
					if (data_order == 1) { cout << "y pos | " << sub_data << " |" << endl; y[font_array_id] = std::stof(sub_data)/128.0;}

					if (data_order == 2) { cout << "x size | " << sub_data << " |" << endl; size_x[font_array_id] = std::stof(sub_data)/512.0;}
					if (data_order == 3) { cout << "y size | " << sub_data << " |" << endl; size_y[font_array_id] = std::stof(sub_data)/128.0;}
					
					if (data_order == 4) { cout << "x offset | " << sub_data << " |" << endl; offset_x[font_array_id] = std::stof(sub_data);}
					if (data_order == 5) { cout << "y offset | " << sub_data << " |" << endl; offset_y[font_array_id] = std::stof(sub_data); }*/
					//

					//if (data_order == 6) { cout << "advance | " << sub_data << " |" << endl; }
					sub_data = "";

					




					data_order++;
				}
				else
				{
					sub_data += line.at(i);
				}
			}
			if (show_console_info) { cout << endl; }

			font_array_id++;
		}

		myfilez.close();
	}
	else
	{
		cout << "Unable to open file";
		
	}
}

void EFont::draw(string _s, Batcher _batch)
{
	
}
