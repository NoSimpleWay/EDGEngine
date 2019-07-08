#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_s.h>
#include "Batcher.h"
#include "ECamera.h"

#include <fstream>
#include <iostream>

#include <list>   
#include <vector>
#include "EInit.h"
#include "EFont.h"

#include <ctime>
#include "Helper.h";
#include <vector>
#include "EButton.h"
#include "EButtonFilterItem.cpp"

#include "FilterBlock.h"



#include "ETexture.h"
#include "EControl.h"

#include "DADItem.h"
#include "EGabarite.h"

using namespace std;
using namespace Helper;
//Helper helper_object;



static int im_static = 0;
int EControl::WTF = 0;

int EControl::mouse_x = 0;
int EControl::mouse_y = 0;

bool EControl::button_pressed = false;
bool EControl ::mouse_pressed = false;
bool EControl ::button_backspace_released = false;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void recalculate_correction();
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double _x, double _y);
void char_input_callback(GLFWwindow* window, unsigned int _char);

//void load_texture();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void load_texture(const char* _path, int _id);

void put_texture_to_atlas(char const* _path,float _x, float _y);
void put_texture_to_atlas(char const* _path);

// settings
int SCR_WIDTH = 1700;
int SCR_HEIGHT = 900;



int width, height, nrChannels;
unsigned char* data1;
unsigned char* data2;

glm::mat4 transform;

Shader* ourShader;

Batcher * batch;
Batcher* batch2;
Batcher* font_batch;

EFont* font;

ECamera* camera;

short tilemap[100][100];
int available_tile[20];
int final_available_tile[20];
int tile_array_index = 0;

bool draw_tile_info = false;

float delta_time;
float saved_time_for_delta;

string work_text="";
std::vector<int> v = { 7, 5, 16, 8 };

std::vector<EButton*> button_list;
std::vector<FilterBlock*> filter_block_list;

std::vector<DADItem*> item_list;


unsigned int ETexture::texture[32];

string username;
string path_to_poe_folder;

static GLFWwindow* window;




#include <windows.h>
#include <Lmcons.h>
#include <shlobj.h>
#include "Enums.h"

#include "ConsoleColor.h"

int block_scroll=0;

unsigned int FBO;
unsigned int FBO_texture;

unsigned int rbo;
unsigned int framebuffer;
unsigned int texColorBuffer;

unsigned int last_texture_w;
unsigned int last_texture_h;


bool collision_matrix[4096][4096][10];

EGabarite* just_created_gabarite = NULL;


//0		-	1
//1		-	2
//2		-	4
//3		-	8
//4		-	16
//5		-	32
//6		-	64
//7		-	128
//8		-	256
//9		-	512
//10	-	1024

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	0.0f,	500.0f,  0.0f, 1.0f,
	0.0f,	0.0f,	0.0f, 0.0f,
	500.0f,	0.0f,	1.0f, 0.0f,

	0.0f,	500.0f,  0.0f, 1.0f,
	500.0f,	0.0f,	 1.0f, 0.0f,
	500.0f,	500.0f,  1.0f, 1.0f
};

bool check_can_put_here(int _x, int _y, int _size_x, int _size_y, int _value, int _dim)
{
	//cout << endl;
	//cout << "#######" << endl;
	//cout << "start collision search at dim: " << _dim << endl << endl;

	for (int put_j = (int)(_x / _value) + 1; put_j < (int)((_x + _size_x) / _value); put_j++)
	for (int put_i = (int)(_y / _value) + 1; put_i < (int)((_y + _size_y) / _value); put_i++)
	{
		if (collision_matrix[put_j][put_i][_dim])
		{
			//cout << "collision at dim:" << _dim << " x:" << _x << " y:" << _y << endl;
			
			put_j = 99999;
			put_i = 99999;

			return false;
		}
	}

	return true;
}
//0		-	1
//1		-	2
//2		-	4
//3		-	8
//4		-	16
//5		-	32
//6		-	64
//7		-	128
//8		-	256
//9		-	512
//10	-	1024
bool check_size_overlap(int _sx, int _sy, int _value)
{
	if ((_sx>_value)&&(_sy>_value))
	{
		return true;
	}

	return false;
}

bool is_no_collision(int _x, int _y, int _size_x, int _size_y)
{
	//return true;
	//bool can_put=true;
	if (!check_can_put_here(_x, _y, _size_x, _size_y, 256, 8)) { return false; }
	if (!check_can_put_here(_x, _y, _size_x, _size_y, 128, 7)) { return false;  }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,64,6)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,32,5)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,16,4)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,8,3)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,4,2)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,2,1)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,1,0)) { return false; }

	return true;
}

string tchar_to_string(TCHAR* _t)
{
	for (int i=0; i<UNLEN; i++)
	{cout << "char at [" << i << "] | "<< _t[i] <<" |" << endl;}

	return "!";
}

bool convert_text_to_bool(string _text)
{
	if (_text == "True")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void parse_item_data()
{
	ofstream myfile_open;
	myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/ItemList.txt");
	string line;

	string subdata;
	string subdata_array[50];

	int line_id=0;
	int data_order;

	DADItem* just_created_item=NULL;

	while ((getline(myfile, line))&&(line_id<1000))
	{
		just_created_item = new DADItem();

		data_order = 0;
		subdata = "";
		for (int i = 0; i < line.length(); i++)
		{
			

			if (line.at(i) != '\t')
			{ subdata += line.at(i); }

			if ((line.at(i)=='\t')||(i+1>=line.length()))
			{
				subdata_array[data_order] = subdata;
				subdata = "";
				data_order++;
			}

		}

		for (int i = 0; i < 25; i++)
		{
			if (subdata_array[i * 2] == "item EN name")			{just_created_item->item_name = subdata_array[i * 2 + 1];}
			if (subdata_array[i * 2] == "icon path")			{just_created_item->icon_path = subdata_array[i * 2 + 1];}
			if (subdata_array[i * 2] == "item RU name")			{just_created_item->item_name_ru = subdata_array[i * 2 + 1];}
			if (subdata_array[i * 2] == "base class")			{just_created_item->base_class = subdata_array[i * 2 + 1];}
			if (subdata_array[i * 2] == "folder")				{just_created_item->folder = subdata_array[i * 2 + 1];}
			
			if (subdata_array[i * 2] == "item category")		{}
			if (subdata_array[i * 2] == "item sub category")	{}
		}

		item_list.push_back(just_created_item);
		//cout << "item data: " << line << endl << endl;

		//cout << "item data [1]" << subdata_array[1] << endl;

		line_id++;
		
		//myfile_open << line<<endl;
	}

	myfile.close();
	myfile_open.close();
}

int find_item_by_full_name(string _name)
{
	for (int i = 0; i < item_list.size(); i++)
	{
		if (item_list.at(i)->item_name == _name) { return i; }
	}

	return -1;
}

void parse_loot_filter_data(string _path)
{
	ifstream myfile;
	myfile.open(_path);

	string line;
	int line_number = 0;
	int data_order = 0;
	
	Enums::ParserMode parser_mode = Enums::ParserMode::NOTHING;

	cout << endl << endl << endl;

	FilterBlock* just_created_block = new FilterBlock();

	int error_counts = 0;
	bool show_info_to_console = false;

	EButton* just_created_button=NULL;



	while ((getline(myfile, line))&&(line_number<10000))
	{

		//std::cout << "array is " << sizeof(condition_names)  << " length" << std::endl;

		bool comment_mode = false;
		string subdata = "";
		data_order = 0;
		parser_mode = Enums::ParserMode::NOTHING;

		bool space_is_not_separator = false;

		
		if (show_info_to_console)
		{
			cout << "#################" << endl;
			cout << green << "___what readed: '" << blue << line << "'" << white << endl;
			cout << "#################" << endl << endl;
		}

		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) == '"') { space_is_not_separator = !space_is_not_separator; }
			if (line.at(i) == '#')
			{
				comment_mode = true; 
				if (show_info_to_console) cout << "comment mode activate, now i dont parse data by normal way" << endl;
				parser_mode = Enums::ParserMode::NOTHING;
			}

			if (	((line.at(i) != ' ')||(space_is_not_separator)) && (line.at(i) != '\t') && (line.at(i) != '"'))
			{
				subdata += line.at(i);
			}
			
			if
			(
				(				
					((line.at(i) == ' ')&&(!space_is_not_separator)) || (line.at(i) == '\t')||(i+1>=line.length())
				)
			)
			{
				
				if (subdata.length() > 0)
				{
					//if ((i >= line.length())&&(line.at(i)!=' ')) { subdata += line.at(i); }

					if (show_info_to_console) cout << "--- subdata:'" << subdata <<"'" << endl;
					

					if (parser_mode == Enums::ParserMode::NOTHING)
					{
						if (!comment_mode)
						{
							if (subdata == "Show")
							{
								just_created_block = new FilterBlock();
								filter_block_list.push_back(just_created_block);
								parser_mode = Enums::ParserMode::SHOW;
								if (show_info_to_console) { cout << "And new block is created! And block is SHOWED!" << endl; }

								just_created_block->is_show = true;
							}

							if (subdata == "Hide")
							{
								just_created_block = new FilterBlock();
								filter_block_list.push_back(just_created_block);
								parser_mode = Enums::ParserMode::HIDE;
								if (show_info_to_console) { cout << "And new block is created! And block is HIDED!" << endl; }

								just_created_block->is_show = false;
							}

							if (subdata == "Corrupted") { parser_mode = Enums::ParserMode::IS_CORRUPTED; just_created_block->is_corrupted_active = true; }
							if (subdata == "LinkedSockets") { parser_mode = Enums::ParserMode::LINKED_SOCKETS; just_created_block->is_links_active = true; }
							if (subdata == "Rarity") { parser_mode = Enums::ParserMode::RARITY; just_created_block->is_item_rarity_active = true; }
							if (subdata == "Class") { parser_mode = Enums::ParserMode::CLASS; }

							if (subdata == "SetFontSize") { parser_mode = Enums::ParserMode::FONT_SIZE; just_created_block->is_font_size_active = true;}
							if (subdata == "SetTextColor") { parser_mode = Enums::ParserMode::TEXT_COLOR; just_created_block->is_text_color_active = true;}
							if (subdata == "SetBorderColor") { parser_mode = Enums::ParserMode::BORDER_COLOR; just_created_block->is_rama_color_active = true;}
							if (subdata == "SetBackgroundColor") { parser_mode = Enums::ParserMode::BACKGROUND_COLOR; just_created_block->is_bg_color_active = true;}

							if (subdata == "PlayAlertSound") { parser_mode = Enums::ParserMode::ALERT_SOUND; just_created_block->is_alert_sound = true;}
							if (subdata == "PlayEffect") { parser_mode = Enums::ParserMode::RAY; just_created_block->is_ray = true;}
							if (subdata == "MinimapIcon") { parser_mode = Enums::ParserMode::MINIMAP_ICON; just_created_block->is_minimap_icon = true;}

							if (subdata == "BaseType") { parser_mode = Enums::ParserMode::BASETYPE; }

							if (subdata == "ShaperItem") { parser_mode = Enums::ParserMode::IS_SHAPER_ITEM; just_created_block->is_shaper_item_active = true;}
							if (subdata == "ItemLevel") { parser_mode = Enums::ParserMode::ITEM_LEVEL; just_created_block->is_item_level_active = true; }
							if (subdata == "HasExplicitMod") { parser_mode = Enums::ParserMode::EXPLICIT_MOD; }
							if (subdata == "Identified") { parser_mode = Enums::ParserMode::IDENTIFIED; just_created_block->is_identified_active = true;}
							if (subdata == "ElderItem") { parser_mode = Enums::ParserMode::IS_ELDER_ITEM; just_created_block->is_elder_item_active = true; }
							if (subdata == "Sockets") { parser_mode = Enums::ParserMode::SOCKETS; just_created_block->is_socket_active = true; }
							if (subdata == "FracturedItem") { parser_mode = Enums::ParserMode::IS_FRACTURED_ITEM; just_created_block->is_fractured_item_active = true; }
							if (subdata == "DropLevel") { parser_mode = Enums::ParserMode::DROP_LEVEL; just_created_block->is_required_level_active = true; }

							if (subdata == "Width") { parser_mode = Enums::ParserMode::WIDTH; just_created_block->is_item_width_active = true; }
							if (subdata == "Height") { parser_mode = Enums::ParserMode::HEIGHT; just_created_block->is_item_height_active = true; }

							if (subdata == "SynthesisedItem") { parser_mode = Enums::ParserMode::IS_SYNTHESISED_ITEM; just_created_block->is_synthesised_item_active = true; }
							if (subdata == "AnyEnchantment") { parser_mode = Enums::ParserMode::IS_ANY_ENCHANTMENT; just_created_block->is_enchantment_item_active = true; }

							if (subdata == "Quality") { parser_mode = Enums::ParserMode::QUALITY; just_created_block->is_item_qualityt_active = true; }
							if (subdata == "SocketGroup") { parser_mode = Enums::ParserMode::SOCKET_GROUP; just_created_block->is_socket_group_active = true; }
							if (subdata == "StackSize") { parser_mode = Enums::ParserMode::STACK_SIZE; just_created_block->is_stack_size_active = true; }
							if (subdata == "GemLevel") { parser_mode = Enums::ParserMode::GEM_LEVEL; just_created_block->is_gem_level_active = true; }

							if (subdata == "ElderMap") { parser_mode = Enums::ParserMode::IS_ELDER_MAP; just_created_block->is_elder_map_active = true; }
							if (subdata == "ShapedMap") { parser_mode = Enums::ParserMode::IS_SHAPER_MAP; just_created_block->is_shaper_map_active = true; }
							if (subdata == "MapTier") { parser_mode = Enums::ParserMode::MAP_TIER; just_created_block->is_map_tier_active = true; }

							if (subdata == "DisableDropSound") { parser_mode = Enums::ParserMode::DISABLE_DROP_SOUND; just_created_block->disable_drop_sound = true; }
							if (subdata == "Prophecy") { parser_mode = Enums::ParserMode::PROPHECY; just_created_block->is_prophecy_active = true; }
							
						}
					}
					else
					{
						if (parser_mode == Enums::ParserMode::IS_CORRUPTED)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate corrupted property" << endl; }
							}

							if (data_order == 1)
							{
								if (show_info_to_console) { cout << "set corruption as <" << subdata << ">" << endl; }
								just_created_block->is_corrupted = convert_text_to_bool(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::LINKED_SOCKETS)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate links property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set links as <" << subdata << ">" << endl; }
								just_created_block->links_count = std::stoi(subdata);
								just_created_block->links_condition = "="; 
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set links condition as <" << subdata << ">" << endl; }
								just_created_block->links_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set links as <" << subdata << ">" << endl; }
								just_created_block->links_count = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::RARITY)
						{
							if (data_order == 0) 
							{
								if (show_info_to_console) { cout << "activate rarity property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set rarity as <" << subdata << ">" << endl; }
								just_created_block->item_rarity = subdata;
								just_created_block->rarity_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set rarity condition as <" << subdata << ">" << endl; }
								just_created_block->rarity_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set rarity as <" << subdata << ">" << endl; }
								just_created_block->item_rarity = subdata;
							}
						}


						if (parser_mode == Enums::ParserMode::CLASS)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0)
							{
								if (show_info_to_console) { cout << "add new base class <" << subdata << ">" << endl; }
								just_created_block->class_list.push_back(new string(subdata));
							}
						}

						if (parser_mode == Enums::ParserMode::FONT_SIZE)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0)
							{
								if (show_info_to_console) { cout << "set font size <" << subdata << ">" << endl; }
								just_created_block->font_size=std::stoi(subdata);
							}
						}
						
						if (parser_mode == Enums::ParserMode::TEXT_COLOR)
						{
							if (data_order == 0){if (show_info_to_console) { cout << "activate text color property" << endl; }}

							if (data_order == 1) { if (show_info_to_console) { cout << "set font color (red) <" << subdata << ">" << endl; } just_created_block->text_color_red = std::stoi(subdata); }
							if (data_order == 2) { if (show_info_to_console) { cout << "set font color (green) <" << subdata << ">" << endl; } just_created_block->text_color_green = std::stoi(subdata); }
							if (data_order == 3) { if (show_info_to_console) { cout << "set font color (blue) <" << subdata << ">" << endl; } just_created_block->text_color_blue = std::stoi(subdata); }
							if (data_order == 4) { if (show_info_to_console) { cout << "set font color (alpha) <" << subdata << ">" << endl; } just_created_block->text_color_alpha = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::BORDER_COLOR)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate border color property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set border color (red) <" << subdata << ">" << endl; } just_created_block->rama_red = std::stoi(subdata); }
							if (data_order == 2) { if (show_info_to_console) { cout << "set border color (green) <" << subdata << ">" << endl; } just_created_block->rama_green = std::stoi(subdata); }
							if (data_order == 3) { if (show_info_to_console) { cout << "set border color (blue) <" << subdata << ">" << endl; } just_created_block->rama_blue = std::stoi(subdata); }
							if (data_order == 4) { if (show_info_to_console) { cout << "set border color (alpha) <" << subdata << ">" << endl; } just_created_block->rama_alpha = std::stoi(subdata); }
						}						
						
						if (parser_mode == Enums::ParserMode::BACKGROUND_COLOR)
						{
							if (data_order == 0) { if (show_info_to_console){cout << "activate background color property" << endl;}  }
							if (data_order == 1) { if (show_info_to_console) { cout << "set background color (red) <" << subdata << ">" << endl; } just_created_block->bg_red = std::stoi(subdata); }
							if (data_order == 2) { if (show_info_to_console) { cout << "set background color (green) <" << subdata << ">" << endl; } just_created_block->bg_green = std::stoi(subdata); }
							if (data_order == 3) { if (show_info_to_console) { cout << "set background color (blue) <" << subdata << ">" << endl; } just_created_block->bg_blue = std::stoi(subdata); }
							if (data_order == 4) { if (show_info_to_console) { cout << "set background color (alpha) <" << subdata << ">" << endl; } just_created_block->bg_alpha = std::stoi(subdata); }
						}
						
						if (parser_mode == Enums::ParserMode::ALERT_SOUND)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate alert sound property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set alert sound name <" << subdata << ">" << endl; } just_created_block->alert_sound_name = subdata; }
							if (data_order == 2) { if (show_info_to_console) { cout << "set alert sound volume <" << subdata << ">" << endl; } just_created_block->alert_sound_volume = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::RAY)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate ray property" << endl; } }

							if (data_order == 1) { if (show_info_to_console) { cout << "set ray color <" << subdata << ">" << endl; } just_created_block->ray_color = Enums::GameColors(get_id_from_game_color_text(subdata)); }
							//if (data_order == 2) { cout << "set alert sound volume <" << subdata << ">" << endl; just_created_block->alert_sound_volume = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::BASETYPE)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0)
							{
								if (show_info_to_console){ cout << "add new base type <" << subdata << ">" << endl; }

								just_created_button=new EButtonFilterItem(0,0,30,30);

								just_created_button->master_block = just_created_block;
								
								just_created_button->description_text = subdata;

								int item_id = find_item_by_full_name(subdata);
								if (item_id < 0) { item_id = 0;  }

								if (item_id >= 0)
								{
									just_created_button->have_icon = true;
									just_created_button->gabarite = item_list.at(item_id)->gabarite;
									just_created_button->button_size_x = item_list.at(item_id)->gabarite->size_x / 2.0f;
									just_created_button->button_size_y = item_list.at(item_id)->gabarite->size_y / 2.0f;
									if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30; }
								}

								//just_created_button->
								just_created_block->filter_block_items_button_list.push_back(just_created_button);
							}
						}

						if (parser_mode == Enums::ParserMode::IS_SHAPER_ITEM)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate shaper item property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set shaper item as <" << subdata << ">" << endl; } just_created_block->is_shaper_item = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::ITEM_LEVEL)
						{
							if (data_order == 0) { if (show_info_to_console){cout << "activate item level" << endl; }}


							if ((data_order == 1) && (!check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set item level as <" << subdata << "> condition autogenerated" << endl; } just_created_block->item_level = std::stoi(subdata); just_created_block->item_level_condition = "="; }
							if ((data_order == 1) && (check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set item level condition as <" << subdata << "> id of symbol=" << get_id_from_array(condition_names, "=") << endl; } just_created_block->item_level_condition = subdata; }

							if (data_order == 2) { if (show_info_to_console) { cout << "set item_level as <" << subdata << ">" << endl; } just_created_block->item_level = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::EXPLICIT_MOD)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0) { if (show_info_to_console){cout << "add new explicit mod <" << subdata << ">" << endl;} just_created_block->explicit_mod_list.push_back(new string(subdata)); }
						}

						if (parser_mode == Enums::ParserMode::IDENTIFIED)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate indetify property" << endl; } }
							if (data_order == 1) { if (show_info_to_console){cout << "set indetification as <" << subdata << ">" << endl;} just_created_block->is_identified = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::IS_ELDER_ITEM)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate elder item property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set elder item as <" << subdata << ">" << endl; } just_created_block->is_elder_item = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::DROP_LEVEL)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate required level" << endl; } }


							if ((data_order == 1) && (!check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set required level as <" << subdata << "> condition autogenerated" << endl; } just_created_block->required_level = std::stoi(subdata); just_created_block->required_level_condition = "="; }
							if ((data_order == 1) && (check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set required level condition as <" << subdata << "> id of symbol=" << get_id_from_array(condition_names, "=") << endl; } just_created_block->required_level_condition = subdata; }

							if (data_order == 2) { if (show_info_to_console) { cout << "set required level as <" << subdata << ">" << endl; } just_created_block->required_level = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::SOCKETS)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate sockets property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set sockets as <" << subdata << ">" << endl; }
								just_created_block->socket_count = std::stoi(subdata);
								just_created_block->socket_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set sockets condition as <" << subdata << ">" << endl; }
								just_created_block->socket_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set sockets as <" << subdata << ">" << endl; }
								just_created_block->socket_count = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::WIDTH)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate width property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set width as <" << subdata << ">" << endl; }
								just_created_block->item_width = std::stoi(subdata);
								just_created_block->item_width_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set width condition as <" << subdata << ">" << endl; }
								just_created_block->item_width_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set width as <" << subdata << ">" << endl; }
								just_created_block->item_width = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::HEIGHT)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate height property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set height as <" << subdata << ">" << endl; }
								just_created_block->item_height = std::stoi(subdata);
								just_created_block->item_height_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set height condition as <" << subdata << ">" << endl; }
								just_created_block->item_height_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set height as <" << subdata << ">" << endl; }
								just_created_block->item_height = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::IS_FRACTURED_ITEM)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate fractured item property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set fractured item as <" << subdata << ">" << endl; } just_created_block->is_fractured_item = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::IS_SYNTHESISED_ITEM)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate synthesised item property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set synthesised item as <" << subdata << ">" << endl; } just_created_block->is_synthesised_item = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::IS_ANY_ENCHANTMENT)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate enchantment item property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set enchantment item as <" << subdata << ">" << endl; } just_created_block->is_enchantment_item = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::QUALITY)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate quality property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
								just_created_block->item_quality = std::stoi(subdata);
								just_created_block->item_quality_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set hqualityeight condition as <" << subdata << ">" << endl; }
								just_created_block->item_quality_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
								just_created_block->item_quality = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::SOCKET_GROUP)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate socket group property" << endl; }
							}

							if (data_order == 1 )
							{
								just_created_block->red_sockets = 0;
								just_created_block->green_sockets = 0;
								just_created_block->blue_sockets = 0;
								just_created_block->white_sockets = 0;

								for (int socket = 0; socket < subdata.length(); socket++)
								{
									if (subdata.at(socket) == 'R') { just_created_block->red_sockets++;		}
									if (subdata.at(socket) == 'G') { just_created_block->green_sockets++;	}
									if (subdata.at(socket) == 'B') { just_created_block->blue_sockets++;	}
									if (subdata.at(socket) == 'W') { just_created_block->white_sockets++;	}
								}

								if (show_info_to_console) { cout << "set RED as <" << just_created_block->red_sockets << "> set GREEN as <" << just_created_block->green_sockets << "> set BLUE as <"  << just_created_block->blue_sockets << "> set WHITE as <" << just_created_block->white_sockets << ">" << endl; }
								//just_created_block->item_height = std::stoi(subdata);
								//just_created_block->item_height_condition = "=";
							}

							
						}

						if (parser_mode == Enums::ParserMode::STACK_SIZE)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate stack size property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
								just_created_block->item_quality = std::stoi(subdata);
								just_created_block->item_quality_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set hqualityeight condition as <" << subdata << ">" << endl; }
								just_created_block->item_quality_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
								just_created_block->item_quality = std::stoi(subdata);
							}
						}
						
						if (parser_mode == Enums::ParserMode::GEM_LEVEL)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate gem level property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
								just_created_block->gem_level = std::stoi(subdata);
								just_created_block->gem_level_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set gem level condition as <" << subdata << ">" << endl; }
								just_created_block->gem_level_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
								just_created_block->gem_level = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::IS_ELDER_MAP)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate elder map property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set elder map item as <" << subdata << ">" << endl; } just_created_block->is_elder_map = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::IS_SHAPER_MAP)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate shaper map property" << endl; } }
							if (data_order == 1) { if (show_info_to_console) { cout << "set shaper map item as <" << subdata << ">" << endl; } just_created_block->is_shaper_map = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::MAP_TIER)
						{
							if (data_order == 0)
							{
								if (show_info_to_console) { cout << "activate map tier property" << endl; }
							}

							if ((data_order == 1) && (!check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
								just_created_block->map_tier = std::stoi(subdata);
								just_created_block->map_tier_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set map tier condition as < " << subdata << " >" << endl; }
								just_created_block->map_tier_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
								just_created_block->map_tier = std::stoi(subdata);
							}
						}

						if (parser_mode == Enums::ParserMode::PROPHECY)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0) { if (show_info_to_console) { cout << "add new prophecy mod <" << subdata << ">" << endl; } just_created_block->prophecy_list.push_back(new string(subdata)); }
						}


					}

					data_order++;
					if ((data_order == 1) && (parser_mode == Enums::ParserMode::NOTHING) && (!comment_mode))
					{ 
						cout << red << "=================================================" << endl;
						cout << red << "ERROR: undefined property: " << yellow << "" << subdata << endl;
						cout << red << "=================================================" << endl<<white;

						error_counts++;
					}

					subdata = "";
				}
				else
				{
					if (show_info_to_console) { cout << "--EMPTY SUBDATA#" << endl; }
				}
			}
		}
		if (show_info_to_console) { cout << endl << endl; }
		
		line_number++;
	}

	if (error_counts <= 0) { cout << green << "Error count:0" << endl;; }
	else
	{
		cout << red << "Error count:" << yellow << error_counts << white << endl;;
	}
	myfile.close();
}

int main()
{
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK)
	{
		std::cout << "Error: " << result << "\n";
	}
	else
	{
		path_to_poe_folder = (string)my_documents + "\\My Games\\Path of Exile\\";
		std::cout << "Path: " << path_to_poe_folder << "\n";

	}

	button_list.push_back(new EButton());

	//filter_block_list.push_back(new FilterBlock());
	//cout << "vector [2]=" << v.at(2) << endl;

	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;





	if (GetUserName(name, &size))
	{
		username = name;
		cout << "Hello, " << username << "!\n";
	}
	else
	{
		cout << "Hello, unnamed person!\n";
	}



	ofstream myfile;
	myfile.open("example.txt");

	for (int i = 0; i < 256; i++)
	{
		myfile << (char)i;
	}
	myfile.close();

	recalculate_correction();
	//setlocale(LC_ALL, "Russian");
	setlocale(LC_ALL, "UTF-8");
	//setlocale(LC_ALL, "");

	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

	//SetConsoleCP(65001);

	cout << "Эх, вот бы жить в 2019..." << endl;
	//setlocale(LC_ALL, "ru-RU");
	//setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали


	string s;

	for (int i = 32; i < 300; i++)
	{
		char ch = i;  // Присвоили в ch число 1, символ, выводимый на экран будет иным
		s += ch;

		//cout <<'a' - 0 << endl;
	}
	//cout << "|" << s << "|\n";





	string line;
	char* ccc;
	ifstream myfilez("data/rus_text.txt", ios::binary);
	if (myfilez.is_open())
	{

		while (getline(myfilez, line))
		{
			//CharToOem("Ёпрст", ccc);

		}

		myfilez.close();
	}
	else cout << "Unable to open file";

	//cout << "QQQ: " << "" << endl;


	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
		{
			tilemap[j][i] = -1;
		}

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
		{
			if (tilemap[j][i] == -1)
			{
				//refill available tile
				for (int k = 0; k < 16; k++)
				{
					available_tile[k] = k;
				}


				//exclude potencial duplicate
				for (int b = -1; b <= 1; b++)
					for (int a = -1; a <= 1; a++)
						if (
							(
							(a != 0) || (b != 0)
								)
							&& (j >= 0)
							&& (j < 100)
							&& (i >= 0)
							&& (i < 100))
						{
							int target_tile = tilemap[j + b][i + a];

							//if (target_tile >= 0) { available_tile[target_tile] = -1; }
						}


				tile_array_index = 0;
				for (int k = 0; k < 16; k++)
					if (available_tile[k] >= 0)
					{
						final_available_tile[tile_array_index] = available_tile[k];
						tile_array_index++;
					}

				int selected_tile = final_available_tile[rand() % tile_array_index];

				//available_tile._Make_iter;

				//tilemap[j][i] = choosen_tile._Getcont;

				if (rand() % 25 != 0) { selected_tile += 4; }
				else { selected_tile = rand() % 4; }
				tilemap[j][i] = selected_tile;


				//std::cout << "tile: " << selected_tile << std::endl;
			}
		}


	// glfw: initialize and configure
	// ------------------------------

	//EInit::GL_init();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// glfw window creation
// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	main_window = window;
	//main_window = window;

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_position_callback);

	glfwSetCharCallback(window, char_input_callback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader zprogram
	// ------------------------------------
	ourShader = new Shader("data/5.1.transform.vs", "data/5.1.transform.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------


	// load and create a texture 
	// -------------------------
	// texture 1
	// ---------
	load_texture("data/white_pixel.png", 0);
	load_texture("data/tile_info.png", 1);
	load_texture("data/font_arial.png", 2);
	// texture 2
	// ---------


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->use();

	//ourShader->setInt("texture2", 1);
	glfwSwapInterval(1);


	// render loop
	// -----------

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//--------------------------------------------------------------------------------------------
	//--------------------------FBO SECTION-----------------------------------------------------
	//--------------------------------------------------------------------------------------------
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4096, 4096, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 4096, 4096); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	//--------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------

	batch = new Batcher();
	batch2 = new Batcher();
	font_batch = new Batcher();


	camera = new ECamera();

	font = new EFont();

	camera->x = 0.0f;
	camera->y = 0.0f;
	//camera->zoom = 1;


	/*
	for (int i = 0; i < 30; i++)
	for (int j = 0; j < 30; j++)
	{
		int tile_y = (int)(tilemap[j][i] / 4);
		int tile_x = tilemap[j][i] - tile_y * 4;


		batch->draw_rect(0.1f * j, 0.1f * i, 0.05f, 0.05f, tile_x, tile_y);
		batch2->draw_rect(0.1f* j, 0.1f* i, 0.05f, 0.05f, tile_x, tile_y);
	}*/

	for (int i = 0; i < 100000; i++)
	{
		batch->fill_indices();
		//batch2->fill_indices();

	}

	for (int i = 0; i < 100000; i++)
	{
		batch->fill_indices();
		//batch2->fill_indices();

	}


	font->load_font("!");



	/*
	string cyr = "АБВГДЕЁЗЖИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯабвгдеёжзийклмнопрстуфхцчшщьыъэюя";

	for (int c = 0; c < cyr.length(); c++)
	{
		cout << "why? " << cyr.at(c) << " " << (int)cyr.at(c)+256 << endl;
	}
	*/



	//string control_text = "Ну наконец-то эта ";


	batch->init();
	batch2->init();

	font_batch->reset();
	batch->setcolor_255(255, 255, 255, 100); font->draw(font_batch, "Ну наконец то эта ", 0, 0);
	batch->setcolor_255(255, 0, 0, 100); font->draw(font_batch, "срань ", 0, 0);
	batch->setcolor_255(0, 255, 0, 100); font->draw(font_batch, "заработала!", 0, 0);
	font_batch->init();

	//--------------------------------texture atlas generator ------------------------------------------------
	//--------------------------------------------------------------------------------------------------------
	glViewport(0, 0, 4096, 4096);
	cout << "Maxt texture size: " << GL_MAX_TEXTURE_SIZE << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	camera->update();
	transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	transform = glm::translate(transform, glm::vec3(camera->x - 1, camera->y - 1, 0.0f));
	transform = glm::scale(transform, glm::vec3(camera->zoom / 4096.0f*2.0f, camera->zoom/ 4096.0f*2.0f, 1));




	//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	// get matrix's uniform location and set matrix
	ourShader->use();
	unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	/////////////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
	ourShader->setInt("texture1", 0);
	batch->setcolor(EColor::WHITE);

	
	//##################################
//##################################
	parse_item_data();
	//##################################
	//##################################
	put_texture_to_atlas("data/font_arial.png", 0, 4096 - 128);

	for (int z = 0; z < item_list.size(); z++)
	{

		int select = rand() % 3;
		
		/*
		if (select == 0) { put_texture_to_atlas("data/button_remove.png"); }
		if (select == 1) { put_texture_to_atlas("data/Buckskin_Tunic_inventory_icon.png"); }
		if (select == 2) { put_texture_to_atlas("data/Bone_Circlet_inventory_icon.png"); }
		*/


		string aaa="data/icon/"+(item_list.at(z)->folder) + "/" + item_list.at(z)->icon_path + ".png";
		put_texture_to_atlas(aaa.c_str());
		item_list.at(z)->gabarite=just_created_gabarite;

		cout << "Collision pass:" << green<< z << white << endl;
	}

	put_texture_to_atlas("data/white_pixel.png");
	just_created_gabarite->x += 1 / 4096.0f;
	just_created_gabarite->y += 1 / 4096.0f;
	just_created_gabarite->x2 -= 1 / 4096.0f;
	just_created_gabarite->y2 -= 1 / 4096.0f;
	DefaultGabarite::gabarite_white = just_created_gabarite;
	

	parse_loot_filter_data(path_to_poe_folder + "NeverSink's filter.filter");

		load_texture("data/white_pixel.png", 0);
		batch->reset();

		/*
		for (int j = 0; j < 512; j++)
		{


			for (int i = 0; i < 512; i++)
			{
				if (collision_matrix[j][i][0])
				{
					batch->setcolor(1,0,0,0.25f);
				}
				else
				{
					batch->setcolor(1,1,1,0.8f);
				}

				batch->draw_rect(j, i, 2.0f, 2.0f);
			}


		}
		batch->reinit();
		batch->draw_call();
		*/

		/*
		batch->setcolor_alpha(EColor::GREEN,0.5f);
		batch->draw_rect(200, 150, 200, 300);

		batch->setcolor(EColor::BLUE);
		batch->draw_rect(300, 500, 200, 300);
		*/

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------

	//cout << (int)01.35f << endl;

	recalculate_correction();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	while (!glfwWindowShouldClose(window))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		if ((glfwGetKey(main_window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE))
		{
			EControl::button_backspace_released = true;
		}
		if (0 == GLFW_PRESS)
		{
			EControl::button_pressed = false;
		}

		clock_t time = clock();
		delta_time = (time - saved_time_for_delta) / 1000.0;
		saved_time_for_delta = time;

		camera->update();

		glClearColor(0.8f, 0.81f, 0.82f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		transform = glm::translate(transform, glm::vec3(camera->x - 1, camera->y - 1, 0.0f));
		transform = glm::scale(transform, glm::vec3(camera->zoom * correction_x, camera->zoom * correction_y, 1));


		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// get matrix's uniform location and set matrix
		ourShader->use();
		unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


		
		batch->reset();
		
		

		/*
		batch->setcolor(EColor::BLACK);
		for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
		{
			batch->draw_rect(j*32+1.0f, i*32+1.0f, 30.0f, 30.0f);
		}
		*/



		/*
		batch->setcolor_alpha(EColor::WHITE,0.5f);
		batch->draw_rect(EControl::mouse_x, EControl::mouse_y, 100, 100);

		batch->setcolor(EColor::BLUE);
		batch->draw_rect_position
		(
			(int)(EControl::mouse_x / 8) * 8 + 8,
			(int)(EControl::mouse_y / 8) * 8 + 8,
			(int)((EControl::mouse_x + 100.0f) / 8) * 8,
			(int)((EControl::mouse_y + 100.0f) / 8) * 8
		);

		batch->setcolor(EColor::GREEN);
		batch->draw_rect_position
		(
			(int)(EControl::mouse_x / 16.0f) * 16.0f + 16.0f,
			(int)(EControl::mouse_y / 16.0f) * 16.0f + 16.0f,
			(int)((EControl::mouse_x + 100.0f) / 16.0f) * 16.0f,
			(int)((EControl::mouse_y + 100.0f) / 16.0f) * 16.0f
		);

		batch->setcolor(EColor::RED);
		batch->draw_rect_position
		(
			(int)(EControl::mouse_x / 32.0f) * 32.0f + 32.0f,
			(int)(EControl::mouse_y / 32.0f) * 32.0f + 32.0f,
			(int)((EControl::mouse_x + 100.0f) / 32.0f) * 32.0f,
			(int)((EControl::mouse_y + 100.0f) / 32.0f) * 32.0f
		);
		*/


		button_list.at(0)->update(delta_time);
		button_list.at(0)->draw(batch);



		//batch->setcolor_255(0, 0, 0, 100);
		int block_index = 0;



		for (int i = 0; i < 9; i++)
		{
			block_index = i + block_scroll;

			if (block_index < filter_block_list.size())
			{
				filter_block_list.at(block_index)->x = 15;
				filter_block_list.at(block_index)->y = SCR_HEIGHT - filter_block_list.at(block_index)->size_y - 15 - i * 105;

				filter_block_list.at(block_index)->size_x = SCR_WIDTH - 30;

				filter_block_list.at(block_index)->update(delta_time);
				filter_block_list.at(block_index)->draw(batch);
			}
		}


		glActiveTexture(GL_TEXTURE0);
		ourShader->setInt("texture1", 0);

		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

		batch->reinit();
		batch->draw_call();

		/*
		//main draw call
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
		ourShader->setInt("texture1", 0);

		batch->reinit();
		batch->draw_call();

		//text draw call
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, ETexture::texture[2]);
		ourShader->setInt("texture1", 2);
		*/
		font_batch->reset();

		font_batch->setcolor_255(255, 255, 255, 100);
		for (int i = 0; i < 9; i++)
		{
			block_index = i + block_scroll;

			if (block_index < filter_block_list.size())
			{
				filter_block_list.at(block_index)->text_pass(font, font_batch);
			}
		}

		button_list.at(0)->text_pass(font, font_batch);




		//font->draw(font_batch, "01!02!03!04" + work_text, 0, 100);

		font_batch->reinit();
		font_batch->draw_call();



		//glBindVertexArray(0);

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
		// clear all relevant buffers





		if (false)
		{
			glBindVertexArray(0);
			// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
			// clear all relevant buffers
			glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
			glClear(GL_COLOR_BUFFER_BIT);

			glActiveTexture(GL_TEXTURE0);
			ourShader->setInt("texture1", 0);

			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane



			batch->setcolor(1.0f, 1.0f, 1.0f, 1.0f);
			batch->reset();

			batch->draw_rect_with_uv(0, 0, 4096/4.0f, 4096/4.0f, 0, 0, 1, 1);
			batch->draw_rect_with_uv(500, 500, 100, 100, item_list.at(0)->gabarite);

			batch->reinit();
			batch->draw_call();


			
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		processInput(window);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------


	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void fill_collision(int _x, int _y, int _size_x, int _size_y,int _siz, int _dim)
{
	for (int xx = (int)(_x / _siz); xx < (int)((_x + _size_x) / _siz); xx++)
	for (int yy = (int)(_y / _siz); yy < (int)((_y + _size_y) / _siz); yy++)
	{
		collision_matrix[xx][yy][_dim] = true;
	}
}

void put_texture_to_atlas(char const* _path, float _x, float _y)
{
	load_texture(_path, 0);

	fill_collision(_x, _y, last_texture_w, last_texture_h, 1, 0);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 2, 1);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 4, 2);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 8, 3);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 16, 4);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 32, 5);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 64, 6);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 128, 7);
	fill_collision(_x, _y, last_texture_w, last_texture_h, 256, 8);

	batch->reset();
	batch->draw_rect(_x, _y, last_texture_w, last_texture_h);
	batch->reinit();
	batch->draw_call();

	just_created_gabarite = new EGabarite(_path, _x / 4096.0f, _y / 4096.0f, last_texture_w / 4096.0f, last_texture_h / 4096.0f);
}

void put_texture_to_atlas(char const* _path)
{
	load_texture(_path, 0);

	for (int j = 0; j < 4000; j+= last_texture_w)
	for (int i = 0; i < 4000; i+= last_texture_h)
		{
			if (is_no_collision(j, i, last_texture_w, last_texture_h))
			{
				fill_collision(j,i,last_texture_w,last_texture_h,1,0);
				fill_collision(j,i,last_texture_w,last_texture_h,2,1);
				fill_collision(j,i,last_texture_w,last_texture_h,4,2);
				fill_collision(j,i,last_texture_w,last_texture_h,8,3);
				fill_collision(j,i,last_texture_w,last_texture_h,16,4);
				fill_collision(j,i,last_texture_w,last_texture_h,32,5);
				fill_collision(j,i,last_texture_w,last_texture_h,64,6);
				fill_collision(j,i,last_texture_w,last_texture_h,128,7);
				fill_collision(j,i,last_texture_w,last_texture_h,256,8);

				batch->reset();
				batch->draw_rect(j, i, last_texture_w, last_texture_h);
				batch->reinit();
				batch->draw_call();

				just_created_gabarite = new EGabarite(_path,j/4096.0f,i/4096.0f,last_texture_w/4096.0f,last_texture_h/4096.0f);

				//cout<<yellow << "end of search!"<<white << endl;

				j = 99999;
				i = 99999;
			}
			else
			{

			}
		}
}

void load_texture(char const *_path, int _id)
{
	glGenTextures(_id, &ETexture::texture[_id]);
	glBindTexture(GL_TEXTURE_2D, ETexture::texture[_id]);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	data1 = stbi_load(_path, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);

		//cout << "loaded texture W:" << width << " H:" << height << endl;

		last_texture_h = height;
		last_texture_w = width;

		/*texture_w[_id] = width;
		texture_h[_id] = height;*/
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	stbi_image_free(data1);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}	

	/*
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera->speed_x += 100.0f * delta_time * Helper::correction_x; }
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera->speed_x -= 100.0f * delta_time * Helper::correction_x; }

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera->speed_y -= 100.0f * delta_time * Helper::correction_y; }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera->speed_y += 100.0f * delta_time * Helper::correction_y; }
	*/
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) { camera->zoom = 1.0f; }

	draw_tile_info = false;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) { draw_tile_info = true; }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{//
	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);

	std::cout << "Resize event width:" << width << " height: " << height << std::endl;

	recalculate_correction();
}

void recalculate_correction()
{
	correction_x = 1.0 / SCR_WIDTH * 2.0;
	correction_y = 1.0 / SCR_HEIGHT * 2.0;

	std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*
	if (yoffset>0)
	{
		camera->zoom*=2.0f;

		camera->x *= 2.0f;
		camera->y *= 2.0f;
	}

	if (yoffset < 0)
	{
		camera->zoom *= 0.5f;

		camera->x *= 0.5f;
		camera->y *= 0.5f;
	}
	*/

	block_scroll -= yoffset;
	if (block_scroll < 0) { block_scroll = 0; }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		EControl::mouse_pressed = true;
		cout << "Cursor Position at (" << xpos << " : " << ypos << " button:" << button<<" action:" << action << endl;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		EControl::button_pressed = false;
		EControl::mouse_pressed = false;

		cout << "Cursor released at (" << xpos << " : " << ypos << " button:" << button << " action:" << action << endl;
	}

	//cout <<" mouse callback. Button=" <<button<<". Action="<<action<<"." << endl;
}

void mouse_position_callback(GLFWwindow* window, double _x, double _y)
{
	//cout << "Mouse move (" << _x << " : " << _y << endl;
	EControl::mouse_x = _x;
	EControl::mouse_y = SCR_HEIGHT-_y;

	EControl::WTF = _x;
}

void char_input_callback(GLFWwindow* window, unsigned int _char)
{
	int inputed_c = (int)_char;

	if (inputed_c == 1025) { inputed_c = 168; }
	else
	if (inputed_c == 1105) { inputed_c = 184; }
	else
	if (inputed_c > 255) { inputed_c -= 848; }

	cout << "input character: " << inputed_c <<"|"<<(int)_char << "[  " << (char)inputed_c << " ]" << " ("<<work_text<<")" <<endl;
	last_inputed_char = (char)inputed_c;
	//work_text += (char)inputed_c;
}


static bool is_button_pressed(int _key)
{
	if (glfwGetKey(window, _key) == GLFW_PRESS) { return true; } else { return false; }
}

