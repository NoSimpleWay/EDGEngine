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
#include <filesystem>

#include <list>   
#include <vector>
#include "EInit.h"
#include "EFont.h"

#include <ctime>
#include "Helper.h";

#include "FilterBlock.h"

#include "EButtonFilterItem.h"
#include "EButtonExplicit.h"
#include "ExplicitGroup.h"

#include "EWindow.h"
#include "StaticData.h"







#include "ETexture.h"
#include "EControl.h"

//#include "DADItem.h"
#include "EGabarite.h"
#include "ItemList.h"
using namespace std;
using namespace Helper;
//Helper helper_object;



static int im_static = 0;
int EControl::WTF = 0;

int EControl::mouse_x = 0;
int EControl::mouse_y = 0;

bool EControl::button_pressed = false;
bool EControl::button_right_pressed = false;

bool EControl ::mouse_pressed = false;
bool EControl ::mouse_right_pressed = false;

bool EControl ::button_backspace_released = false;
char EControl::last_inputed_char=NULL;

float EControl::delete_button_hold_time = 0.0f;

EFont* EFont::font_arial = NULL;

int EControl::block_scroll = 0;

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
void put_texture_to_atlas(char const* _path, EGabarite* _g);

// settings
int EWindow::SCR_WIDTH = 1700;
int EWindow::SCR_HEIGHT = 900;
int EWindow::top_layer_id = 0;
GLFWwindow* EWindow::main_window = NULL;



int width, height, nrChannels;
unsigned char* data1;
unsigned char* data2;

glm::mat4 matrix_transform;

Shader* ourShader;

Batcher * batch;



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
//std::vector<FilterBlock*> filter_block_list;



unsigned int ETexture::texture[32];

string username;
//string path_to_poe_folder;

static GLFWwindow* window;




#include <windows.h>
#include <Lmcons.h>
#include <shlobj.h>

#include "ConsoleColor.h"

#include <irr/irrKlang.h>

#include "EUtils.h"


#include <experimental/filesystem>






unsigned int FBO;
unsigned int FBO_texture;

unsigned int rbo;
unsigned int framebuffer;
unsigned int texColorBuffer;

unsigned int last_texture_w;
unsigned int last_texture_h;


bool collision_matrix[4096][4096][10];

EGabarite* just_created_gabarite = NULL;

std::vector<EWindow*> EControl::window_list;

EWindowFilterBlock* StaticData::window_filter_block = NULL;
EWindowFindItem* StaticData::window_find_item = NULL;
EWindowAddNewBaseData* StaticData::window_add_new_base_data = NULL;
EWindowSocketGroup* StaticData::window_socket_group = NULL;
EWindowFilterVisualEditor* StaticData::window_filter_visual_editor = NULL;
EWindowMain* StaticData::window_main=NULL;
EWindowFilterBlockSearch* StaticData::window_filter_block_search=NULL;
EWindowLoadingScreen* StaticData::window_loading_screen=NULL;
EWindowCreateNewLootFilter* StaticData::window_new_loot_filter=NULL;
EWindowSelectLocalisation* StaticData::window_select_localisation =NULL;
EWindowLootSimulator* StaticData::window_loot_simulator =NULL;


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

#include <codecvt>
void load_prophecy_list()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/ProphecyList.txt");
	string line;

	string subdata;
	string subdata_array[100];

	int line_id = 0;
	int data_order;

	ProphecyList* just_created_prophecy = NULL;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 1000))
	{
		just_created_prophecy = new ProphecyList();

		data_order = 0;
		subdata = "";

		for (int i = 0; i < line.length(); i++)
		{


			if (line.at(i) != '\t')
			{
				subdata += line.at(i);
			}

			if ((line.at(i) == '\t') || (i + 1 >= line.length()))
			{
				subdata_array[data_order] = subdata;
				subdata = "";
				data_order++;
			}

		}

		for (int i = 0; i < 40; i++)
		{

			if (subdata_array[i * 2] == "name")
			{
				just_created_prophecy->base_name = subdata_array[i * 2 + 1];
			}

			if (subdata_array[i * 2] == "RU name")
			{
				char sInvalid[1024];
				strcpy_s(sInvalid, subdata_array[i * 2 + 1].c_str());
				//комментарии

				int size = strlen(sInvalid) + 1;
				wchar_t* wsValid = new wchar_t[size];
				char* sValid = new char[size];

				MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
				WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);

				//cout << "A: " << wsValid << " B: " << sValid << endl;

				just_created_prophecy->ru_name = sValid;
			}

			if (subdata_array[i * 2] == "tier")
			{
				if (subdata_array[i * 2 + 1]=="TRASH")
				{ just_created_prophecy->cost=Enums::CostList::TRASH; }

				if (subdata_array[i * 2 + 1]=="LOW COST")
				{ just_created_prophecy->cost=Enums::CostList::LOW_COST; }

				if (subdata_array[i * 2 + 1]=="MID COST")
				{ just_created_prophecy->cost=Enums::CostList::MID_COST; }

				if (subdata_array[i * 2 + 1]=="HIGH COST")
				{ just_created_prophecy->cost=Enums::CostList::HIGH_COST; }

				if (subdata_array[i * 2 + 1]=="TOP COST")
				{ just_created_prophecy->cost=Enums::CostList::TOP_COST; }
			}


		}

		EString::prophecy_list.push_back(just_created_prophecy);

	}

	int wtf = 0;
	for (BaseClass* b : EString::base_class_list)
	{
		cout << "[" << wtf << "] base class name: " << b->base_name << " ru name: " << b->ru_name << endl;
		wtf++;
	}
}

void load_base_class()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/ItemClass.txt");
	string line;

	string subdata;
	string subdata_array[100];

	int line_id = 0;
	int data_order;

	BaseClass* just_created_base_class = NULL;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 1000))
	{
		just_created_base_class = new BaseClass();

		data_order = 0;
		subdata = "";

		for (int i = 0; i < line.length(); i++)
		{


			if (line.at(i) != '\t')
			{
				subdata += line.at(i);
			}

			if ((line.at(i) == '\t') || (i + 1 >= line.length()))
			{
				subdata_array[data_order] = subdata;
				subdata = "";
				data_order++;
			}

		}

		for (int i = 0; i < 40; i++)
		{

			if (subdata_array[i * 2] == "Base name")
			{
				just_created_base_class->base_name = subdata_array[i * 2 + 1];
			}

			if (subdata_array[i * 2] == "RU name")
			{
				char sInvalid[1024];
				strcpy_s(sInvalid, subdata_array[i * 2 + 1].c_str());
				//комментарии

				int size = strlen(sInvalid) + 1;
				wchar_t* wsValid = new wchar_t[size];
				char* sValid = new char[size];

				MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
				WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);

				//cout << "A: " << wsValid << " B: " << sValid << endl;

				just_created_base_class->ru_name = sValid;
			}

			
		}

		EString::base_class_list.push_back(just_created_base_class);

	}

	int wtf = 0;
	for (BaseClass* b : EString::base_class_list)
	{
		cout << "["<<wtf<< "] base class name: " << b->base_name << " ru name: " << b->ru_name << endl;
		wtf++;
	}
}



void parse_item_data()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/ItemList.txt");
	string line;

	string subdata;
	string subdata_array[100];

	int line_id=0;
	int data_order;

	DADItem* just_created_item=NULL;

	//cout << EMath::rgb::r << endl;
	

	while ((getline(myfile, line)) && (line_id < 10000))
	{
		if (line.length()>=4)
		{
			just_created_item = new DADItem();

			data_order = 0;
			subdata = "";
			for (int i = 0; i < line.length(); i++)
			{


				if (line.at(i) != '\t')
				{
					subdata += line.at(i);
				}

				if ((line.at(i) == '\t') || (i + 1 >= line.length()))
				{
					subdata_array[data_order] = subdata;
					subdata = "";
					data_order++;
				}

			}

			for (int i = 0; i < 40; i++)
			{

				if (subdata_array[i * 2] == "item EN name")
				{
					just_created_item->item_name = subdata_array[i * 2 + 1];
				}

				if (subdata_array[i * 2] == "icon path") { just_created_item->icon_path = subdata_array[i * 2 + 1]; }

				if (subdata_array[i * 2] == "item RU name")
				{
					char sInvalid[1024];
					strcpy_s(sInvalid, subdata_array[i * 2 + 1].c_str());
					//комментарии

					int size = strlen(sInvalid) + 1;
					wchar_t* wsValid = new wchar_t[size];
					char* sValid = new char[size];

					MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
					WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);

					//cout << "A: " << wsValid << " B: " << sValid << endl;

					just_created_item->item_name_ru = sValid;
				}

				if (subdata_array[i * 2] == "base class") { just_created_item->base_class = subdata_array[i * 2 + 1]; }
				if (subdata_array[i * 2] == "folder") { just_created_item->folder = subdata_array[i * 2 + 1]; }

				if (subdata_array[i * 2] == "item category") { just_created_item->category = subdata_array[i * 2 + 1]; }
				if (subdata_array[i * 2] == "item sub category") { just_created_item->subcategory = subdata_array[i * 2 + 1]; }

				if (subdata_array[i * 2] == "width") { just_created_item->width = std::stoi(subdata_array[i * 2 + 1]); }
				if (subdata_array[i * 2] == "height") { just_created_item->height = std::stoi(subdata_array[i * 2 + 1]); }

				if (subdata_array[i * 2] == "COST_GROUP") { just_created_item->cost_group = subdata_array[i * 2 + 1]; }
			}

			ItemList::item_list.push_back(just_created_item);

			line_id++;

		}
	}

	
	myfile.close();
	//myfile_open.close();
}

int find_item_by_full_name(string _name)
{
	
	for (int i = 0; i < ItemList::item_list.size(); i++)
	{
		if (ItemList::item_list.at(i)->item_name == _name) { return i; }
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

	int explicit_group_id = -1;

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
							/*for (EButtonDropCondition* b : base_filter_condition_list)
							{
								b->incoming_data(this);
							}*/

							if (subdata == "Show")
							{
								just_created_block = new FilterBlock();
								StaticData::window_filter_block->filter_block_list.push_back(just_created_block);
								parser_mode = Enums::ParserMode::SHOW;
								if (show_info_to_console) { cout << "And new block is created! And block is SHOWED!" << endl; }

								just_created_block->is_show = true;

								explicit_group_id = -1;
							}

							if (subdata == "Hide")
							{
								just_created_block = new FilterBlock();
								StaticData::window_filter_block->filter_block_list.push_back(just_created_block);
								parser_mode = Enums::ParserMode::HIDE;
								if (show_info_to_console) { cout << "And new block is created! And block is HIDED!" << endl; }

								just_created_block->is_show = false;

								explicit_group_id = -1;
							}

							if (subdata == "Corrupted") { parser_mode = Enums::ParserMode::IS_CORRUPTED; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_CORRUPTED) = true; }
							if (subdata == "LinkedSockets") { parser_mode = Enums::ParserMode::LINKED_SOCKETS; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_LINKS) = true; }
							if (subdata == "Rarity") { parser_mode = Enums::ParserMode::RARITY; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_RARITY) = true; }
							if (subdata == "Class")
							{
								std::cout << "Try get acess to remove button" << std::endl;

								parser_mode = Enums::ParserMode::CLASS;
								just_created_block->is_base_class_active = true;
								just_created_block->plus_class_button_link->is_active = true;
								just_created_block->remove_base_class_button->is_active = true;
							}
							

							if (subdata == "SetFontSize") { parser_mode = Enums::ParserMode::FONT_SIZE; just_created_block->is_font_size_active = true;}
							if (subdata == "SetTextColor") { parser_mode = Enums::ParserMode::TEXT_COLOR; just_created_block->is_text_color_active = true;}
							if (subdata == "SetBorderColor") { parser_mode = Enums::ParserMode::BORDER_COLOR; just_created_block->is_rama_color_active = true;}
							if (subdata == "SetBackgroundColor") { parser_mode = Enums::ParserMode::BACKGROUND_COLOR; just_created_block->is_bg_color_active = true;}

							if (subdata == "PlayAlertSound") { parser_mode = Enums::ParserMode::ALERT_SOUND; just_created_block->is_alert_sound = true;}
							if (subdata == "CustomAlertSound") { parser_mode = Enums::ParserMode::CUSTOM_ALERT_SOUND; just_created_block->is_custom_alert_sound = true;}
							if (subdata == "PlayEffect") { parser_mode = Enums::ParserMode::RAY; just_created_block->is_ray = true;}
							if (subdata == "MinimapIcon") { parser_mode = Enums::ParserMode::MINIMAP_ICON; just_created_block->is_minimap_icon = true;}

							if (subdata == "BaseType") { parser_mode = Enums::ParserMode::BASETYPE; }

							if (subdata == "ShaperItem") { parser_mode = Enums::ParserMode::IS_SHAPER_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM) = true;}
							if (subdata == "ItemLevel") { parser_mode = Enums::ParserMode::ITEM_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ITEM_LEVEL) = true; }
							if (subdata == "HasExplicitMod") { parser_mode = Enums::ParserMode::EXPLICIT_MOD; explicit_group_id++; }
							if (subdata == "Identified") { parser_mode = Enums::ParserMode::IDENTIFIED; just_created_block->is_identified_active = true;}
							if (subdata == "ElderItem") { parser_mode = Enums::ParserMode::IS_ELDER_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM) = true; }
							if (subdata == "Sockets") { parser_mode = Enums::ParserMode::SOCKETS; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS) = true; }
							if (subdata == "FracturedItem") { parser_mode = Enums::ParserMode::IS_FRACTURED_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED) = true; }
							if (subdata == "DropLevel") { parser_mode = Enums::ParserMode::DROP_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_REQUIRED_LEVEL) = true; }

							if (subdata == "Width") { parser_mode = Enums::ParserMode::WIDTH; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_WIDTH) = true; }
							if (subdata == "Height") { parser_mode = Enums::ParserMode::HEIGHT; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_HEIGHT) = true; }

							if (subdata == "SynthesisedItem") { parser_mode = Enums::ParserMode::IS_SYNTHESISED_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED) = true; }
							if (subdata == "AnyEnchantment") { parser_mode = Enums::ParserMode::IS_ANY_ENCHANTMENT; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ENCHANTMENT) = true; }

							if (subdata == "Quality") { parser_mode = Enums::ParserMode::QUALITY; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_QUALITY) = true; }
							if (subdata == "SocketGroup") { parser_mode = Enums::ParserMode::SOCKET_GROUP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP) = true; }
							if (subdata == "StackSize") { parser_mode = Enums::ParserMode::STACK_SIZE; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_STACK_SIZE) = true; }
							if (subdata == "GemLevel") { parser_mode = Enums::ParserMode::GEM_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_GEM_LEVEL) = true; }

							if (subdata == "ElderMap") { parser_mode = Enums::ParserMode::IS_ELDER_MAP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP) = true; }
							if (subdata == "ShapedMap") { parser_mode = Enums::ParserMode::IS_SHAPER_MAP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP) = true; }
							if (subdata == "MapTier") { parser_mode = Enums::ParserMode::MAP_TIER; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MAP_TIER) = true; }

							if (subdata == "DisableDropSound") { parser_mode = Enums::ParserMode::DISABLE_DROP_SOUND; just_created_block->disable_drop_sound = true; }
							if (subdata == "Prophecy")
							{
								parser_mode = Enums::ParserMode::PROPHECY;
								just_created_block->is_prophecy_active = true;

								just_created_block->plus_prophecy_button_link->is_active = true;
								just_created_block->remove_prophecy_button->is_active = true;
							}
							
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
								//just_created_block->class_list.push_back(new string(subdata));

								EButtonExplicit* class_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
								class_button->text = subdata;
								class_button->master_block = just_created_block;
								class_button->master_window = StaticData::window_filter_block;
								class_button->button_size_x = EFont::get_width(EFont::font_arial, subdata) + 5.0f;
								
								just_created_block->button_list.push_back(class_button);
								just_created_block->base_class_list.push_back(class_button);

								

								
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
							if (data_order == 1)
							{ 
								if (show_info_to_console){cout << "set alert sound name <" << subdata << ">" << endl;}
								
								just_created_block->alert_sound_name = subdata;

								if (subdata == "1") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_01;}
								if (subdata == "2") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_02;}
								if (subdata == "3") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_03;}
								if (subdata == "4") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_04;}
								if (subdata == "5") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_05;}
								if (subdata == "6") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_06;}
								if (subdata == "7") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_07;}
								if (subdata == "8") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_08;}
								if (subdata == "9") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_09;}
								if (subdata == "10") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_10;}
								if (subdata == "11") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_11;}
								if (subdata == "12") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_12;}
								if (subdata == "13") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_13;}
								if (subdata == "14") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_14;}
								if (subdata == "15") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_15;}
								if (subdata == "16") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_16;}

								if (subdata == "SHAlchemy") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_ALCHEMY;}
								if (subdata == "SHBlessed") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_BLESSED;}
								if (subdata == "SHChaos") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_CHAOS;}
								if (subdata == "SHDivine") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_DIVINE;}
								if (subdata == "SHExalted") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_EXALTED;}
								if (subdata == "SHFusing") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_FUSING;}
								if (subdata == "SHGeneral") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_GENERAL;}
								if (subdata == "SHMirror") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_MIRROR;}
								if (subdata == "SHRegal") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_REGAL;}
								if (subdata == "SHVaal") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_VAAL;}
							}

								if (data_order == 2) { if (show_info_to_console) { cout << "set alert sound volume <" << subdata << ">" << endl; } just_created_block->alert_sound_volume = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::ALERT_SOUND)
						{
							if (data_order == 0) { if (show_info_to_console) { cout << "activate custom alert sound property" << endl; } }
							if (data_order == 1)
							{
								just_created_block->custom_alert_sound_name = subdata;
							}
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

								just_created_button=new EButtonFilterItem(0,0,45,45);

								just_created_button->master_block = just_created_block;
								just_created_button->master_window = StaticData::window_filter_block;
								
								just_created_button->description_text = subdata;

								int item_id = find_item_by_full_name(subdata);
							
								if (item_id >= 0)
								{
									just_created_button->have_icon = true;
									just_created_button->gabarite = ItemList::item_list.at(item_id)->gabarite;
									//just_created_button->button_size_x = ItemList::item_list.at(item_id)->gabarite->size_x / 2.0f;
									//just_created_button->button_size_y = ItemList::item_list.at(item_id)->gabarite->size_y / 2.0f;

									just_created_button->description_text = ItemList::item_list.at(item_id)->item_name+" ("+ ItemList::item_list.at(item_id)->item_name_ru+")";

									if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30; }
								}
								else
								{
									just_created_button->have_icon = true;
									just_created_button->gabarite = DefaultGabarite::gabarite_undefined;

									just_created_button->description_text = "Unknown item (" + subdata + ")";

									if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30;}
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
							if (data_order > 0)
							{
								if (show_info_to_console){cout << "add new explicit mod <" << subdata << ">" << endl;}
								just_created_block->explicit_mod_list.push_back(new string(subdata));

								cout << "try allocate explicit list at <" << explicit_group_id << ">" << endl;
								EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST);
								explicit_button->text = subdata;
								explicit_button->master_block = just_created_block;
								explicit_button->master_window = StaticData::window_filter_block;
								explicit_button->button_size_x = EFont::get_width(EFont::font_arial, subdata) + 5.0f;
								just_created_block->explicit_list.at(explicit_group_id)->button_list.push_back(explicit_button);
								just_created_block->button_list.push_back(explicit_button);
								just_created_block->explicit_list.at(explicit_group_id)->is_active = true;



								just_created_block->explicit_list.at(explicit_group_id)->button_close->is_active = true;
								just_created_block->explicit_list.at(explicit_group_id)->button_add->is_active = true;

								
							}
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
								if (show_info_to_console) { cout << "set stack size as <" << subdata << ">" << endl; }
								just_created_block->item_stack_size = std::stoi(subdata);
								just_created_block->item_stack_size_condition = "=";
							}

							if ((data_order == 1) && (check_is_condition_symbols(subdata)))
							{
								if (show_info_to_console) { cout << "set stack size condition as <" << subdata << ">" << endl; }
								just_created_block->item_stack_size_condition = subdata;
							}

							if (data_order == 2)
							{
								if (show_info_to_console) { cout << "set stack size as <" << subdata << ">" << endl; }
								just_created_block->item_stack_size = std::stoi(subdata);
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
							if (data_order > 0) {
								if (show_info_to_console)
								{
									cout << "add new prophecy mod <" << subdata << ">" << endl;
								}
								EButtonExplicit* prophecy_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST);
								prophecy_button->text = subdata;
								prophecy_button->master_block = just_created_block;
								prophecy_button->master_window = StaticData::window_filter_block;
								prophecy_button->button_size_x = EFont::get_width(EFont::font_arial, subdata) + 5.0f;

								prophecy_button->data_id = -1;

								for (int sr = 0; sr < EString::prophecy_list.size(); sr++)
								{
									if (EString::prophecy_list.at(sr)->base_name == subdata)
									{
										prophecy_button->data_id = sr;
									}
								}

								just_created_block->button_list.push_back(prophecy_button);
								just_created_block->prophecy_list.push_back(prophecy_button);
							}
							

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

	for (FilterBlock* f : StaticData::window_filter_block->filter_block_list)
	{
		f->data_change();
	}

	if (error_counts <= 0) { cout << green << "Error count:0" << endl;; }
	else
	{
		cout << red << "Error count:" << yellow << error_counts << white << endl;;
	}
	myfile.close();
}



//irrklang::ISoundEngine* engine= irrklang::createIrrKlangDevice();
//irrklang::ISoundSource* shootSound = engine->addSoundSourceFromFile("data/cool01.wav");

int main()
{
	//engine->play2D("data/cool01.wav");

	
	ESound::engine = irrklang::createIrrKlangDevice();

	ESound::default_drop_sound_name.push_back("NONE");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert01");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert02");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert03");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert04");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert05");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert06");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert07");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert08");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert09");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert10");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert11");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert12");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert13");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert14");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert15");
	ESound::default_drop_sound_name.push_back("ItemFilterAlert16");

	ESound::default_drop_sound_name.push_back("SHAlchemy");
	ESound::default_drop_sound_name.push_back("SHBlessed");
	ESound::default_drop_sound_name.push_back("SHChaos");
	ESound::default_drop_sound_name.push_back("SHDivine");
	ESound::default_drop_sound_name.push_back("SHExalted");
	ESound::default_drop_sound_name.push_back("SHFusing");
	ESound::default_drop_sound_name.push_back("SHGeneral");
	ESound::default_drop_sound_name.push_back("SHMirror");
	ESound::default_drop_sound_name.push_back("SHRegal");
	ESound::default_drop_sound_name.push_back("SHVaal");



	ESound::default_drop_sound_original_name.push_back("NONE");
	ESound::default_drop_sound_original_name.push_back("1");
	ESound::default_drop_sound_original_name.push_back("2");
	ESound::default_drop_sound_original_name.push_back("3");
	ESound::default_drop_sound_original_name.push_back("4");
	ESound::default_drop_sound_original_name.push_back("5");
	ESound::default_drop_sound_original_name.push_back("6");
	ESound::default_drop_sound_original_name.push_back("7");
	ESound::default_drop_sound_original_name.push_back("8");
	ESound::default_drop_sound_original_name.push_back("9");
	ESound::default_drop_sound_original_name.push_back("10");
	ESound::default_drop_sound_original_name.push_back("11");
	ESound::default_drop_sound_original_name.push_back("12");
	ESound::default_drop_sound_original_name.push_back("13");
	ESound::default_drop_sound_original_name.push_back("14");
	ESound::default_drop_sound_original_name.push_back("15");
	ESound::default_drop_sound_original_name.push_back("16");

	ESound::default_drop_sound_original_name.push_back("SHAlchemy");
	ESound::default_drop_sound_original_name.push_back("SHBlessed");
	ESound::default_drop_sound_original_name.push_back("SHChaos");
	ESound::default_drop_sound_original_name.push_back("SHDivine");
	ESound::default_drop_sound_original_name.push_back("SHExalted");
	ESound::default_drop_sound_original_name.push_back("SHFusing");
	ESound::default_drop_sound_original_name.push_back("SHGeneral");
	ESound::default_drop_sound_original_name.push_back("SHMirror");
	ESound::default_drop_sound_original_name.push_back("SHRegal");
	ESound::default_drop_sound_original_name.push_back("SHVaal");

	int sound_order = 0;
	for (string s : ESound::default_drop_sound_name)
	{
		if (sound_order > 0)
		{
			string sound_path = "data/sound/default_drop_sound/" + s + ".wav";
			ESound::default_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(sound_path.c_str()));
		}
		else
		{
			ESound::default_drop_sound.push_back(NULL);
		}
		sound_order++;
	}

	ESound::flip_sound = ESound::engine->addSoundSourceFromFile("data/sound/flippy.wav");




	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK)
	{
		std::cout << "Error: " << result << "\n";
	}
	else
	{
		EString::path_to_poe_folder = (string)my_documents + "\\My Games\\Path of Exile\\";
		std::cout << "Path: " << EString::path_to_poe_folder << "\n";

	}

	ESound::load_custom_sound();

	//ofstream writer;
	//writer.open("check.txt");

	

	//writer.close();
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
	//setlocale(LC_ALL, "UTF-8");
	//setlocale(LC_ALL, "");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//SetConsoleCP(65001);

	//cout << "Эх, вот бы жить в 2019..." << endl;
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








	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// glfw window creation
// --------------------
	window = glfwCreateWindow(EWindow::SCR_WIDTH, EWindow::SCR_HEIGHT, "DaD Editor", NULL, NULL);
	EWindow::main_window = window;


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


	camera = new ECamera();

	EFont::font_arial = new EFont();

	camera->x = 0.0f;
	camera->y = 0.0f;

	for (int i = 0; i < 100000; i++)
	{
		batch->fill_indices();

	}


	EFont::font_arial->load_font("!");



	batch->init();






	//##################################
	//##################################
	parse_item_data();
	load_base_class();
	load_prophecy_list();
	EString::load_localisation("EN");
	
	//##################################
	//##################################

	

	//--------------------------------texture atlas generator ------------------------------------------------
	//--------------------------------------------------------------------------------------------------------
	glViewport(0, 0, 4096, 4096);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);
	camera->update();
	matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	matrix_transform = glm::translate(matrix_transform, glm::vec3(camera->x - 1, camera->y - 1, 0.0f));
	matrix_transform = glm::scale(matrix_transform, glm::vec3(camera->zoom / 4096.0f*2.0f, camera->zoom/ 4096.0f*2.0f, 1));

	ourShader->use();
	unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix_transform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
	ourShader->setInt("texture1", 0);
	batch->setcolor(EColorCollection::WHITE);

	put_texture_to_atlas("data/font_arial.png", 0, 4096 - 128);

	put_texture_to_atlas("data/background.png");			DefaultGabarite::gabarite_background = just_created_gabarite;

	put_texture_to_atlas("data/shaper_bg.png");				DefaultGabarite::gabarite_shaper_bg = just_created_gabarite;

	put_texture_to_atlas("data/elder_bg.png");				DefaultGabarite::gabarite_elder_bg = just_created_gabarite;

	cout << "item list size=" << ItemList::item_list.size() << endl;
	

	put_texture_to_atlas("data/white_pixel.png");
	just_created_gabarite->x += 1 / 4096.0f;
	just_created_gabarite->y += 1 / 4096.0f;
	just_created_gabarite->x2 -= 1 / 4096.0f;
	just_created_gabarite->y2 -= 1 / 4096.0f;
	DefaultGabarite::gabarite_white = just_created_gabarite;
	


	put_texture_to_atlas("data/undefined.png");				DefaultGabarite::gabarite_undefined = just_created_gabarite;
	put_texture_to_atlas("data/plus.png");					DefaultGabarite::gabarite_plus = just_created_gabarite;

	
	put_texture_to_atlas("data/checked.png");				DefaultGabarite::gabarite_checked = just_created_gabarite;
	put_texture_to_atlas("data/unchecked.png");				DefaultGabarite::gabarite_unchecked = just_created_gabarite;
	put_texture_to_atlas("data/button_remove.png");			DefaultGabarite::gabarite_remove = just_created_gabarite;
	put_texture_to_atlas("data/button_plus_wide.png");		DefaultGabarite::gabarite_plus_wide = just_created_gabarite;

	put_texture_to_atlas("data/button_increase.png");		DefaultGabarite::gabarite_increase = just_created_gabarite;
	put_texture_to_atlas("data/button_decrease.png");		DefaultGabarite::gabarite_decrease = just_created_gabarite;

	put_texture_to_atlas("data/button_close.png");			DefaultGabarite::gabarite_close = just_created_gabarite;
	put_texture_to_atlas("data/button_color_mode.png");		DefaultGabarite::gabarite_visual_mode = just_created_gabarite;

	put_texture_to_atlas("data/slider_hue.png");			DefaultGabarite::gabarite_slider_hue = just_created_gabarite;
	put_texture_to_atlas("data/slider_saturation.png");		DefaultGabarite::gabarite_slider_saturation = just_created_gabarite;
	put_texture_to_atlas("data/slider_value.png");			DefaultGabarite::gabarite_slider_value = just_created_gabarite;
	put_texture_to_atlas("data/slider_alpha.png");			DefaultGabarite::gabarite_slider_alpha = just_created_gabarite;

	put_texture_to_atlas("data/visual_editor_bg.png");		DefaultGabarite::gabarite_visual_editor_bg = just_created_gabarite;

	put_texture_to_atlas("data/button_sound.png");			DefaultGabarite::gabarite_play_sound = just_created_gabarite;
	
	put_texture_to_atlas("data/icon_circle.png");			DefaultGabarite::gabarite_minimap_icon[0] = just_created_gabarite;
	put_texture_to_atlas("data/icon_diamond.png");			DefaultGabarite::gabarite_minimap_icon[1] = just_created_gabarite;
	put_texture_to_atlas("data/icon_hexagon.png");			DefaultGabarite::gabarite_minimap_icon[2] = just_created_gabarite;
	put_texture_to_atlas("data/icon_square.png");			DefaultGabarite::gabarite_minimap_icon[3] = just_created_gabarite;
	put_texture_to_atlas("data/icon_star.png");				DefaultGabarite::gabarite_minimap_icon[4] = just_created_gabarite;
	put_texture_to_atlas("data/icon_circle.png");			DefaultGabarite::gabarite_minimap_icon[5] = just_created_gabarite;


	put_texture_to_atlas("data/button_load.png");			DefaultGabarite::gabarite_button_load = just_created_gabarite;
	put_texture_to_atlas("data/button_save.png");			DefaultGabarite::gabarite_button_save = just_created_gabarite;

	put_texture_to_atlas("data/bg_noise.png");				DefaultGabarite::gabarite_bg_noise = just_created_gabarite;
	put_texture_to_atlas("data/ray_icon.png");				DefaultGabarite::gabarite_ray_icon = just_created_gabarite;

	put_texture_to_atlas("data/plus_gray.png");				DefaultGabarite::gabarite_plus_gray = just_created_gabarite;
	put_texture_to_atlas("data/up_gray.png");				DefaultGabarite::gabarite_up_gray = just_created_gabarite;
	put_texture_to_atlas("data/down_gray.png");				DefaultGabarite::gabarite_down_gray = just_created_gabarite;

	put_texture_to_atlas("data/remove_block.png");			DefaultGabarite::gabarite_remove_block = just_created_gabarite;

	put_texture_to_atlas("data/gray_eye.png");				DefaultGabarite::gabarite_gray_eye = just_created_gabarite;

	put_texture_to_atlas("data/ray_icon_remove.png");		DefaultGabarite::gabarite_ray_icon_remove = just_created_gabarite;

	put_texture_to_atlas("data/button_new.png");			DefaultGabarite::gabarite_button_new = just_created_gabarite;

	put_texture_to_atlas("data/plus_circle.png");			DefaultGabarite::gabarite_plus_circle = just_created_gabarite;
	put_texture_to_atlas("data/remove_circle.png");			DefaultGabarite::gabarite_remove_circle = just_created_gabarite;

	put_texture_to_atlas("data/flag_EN.png");				DefaultGabarite::gabarite_flag_EN = just_created_gabarite;
	put_texture_to_atlas("data/flag_RU.png");				DefaultGabarite::gabarite_flag_RU = just_created_gabarite;

	put_texture_to_atlas("data/button_simulator.png");		DefaultGabarite::gabarite_open_simulator = just_created_gabarite;











	

	StaticData::window_filter_block = new EWindowFilterBlock(0, false);
	StaticData::window_filter_block->name = "Filter block";
	EControl::window_list.push_back(StaticData::window_filter_block);

	
	EString::load_loot_filter_list();
	//std::string path = "/path/to/directory";


	StaticData::window_add_new_base_data = new EWindowAddNewBaseData(1, true);
	StaticData::window_add_new_base_data->name = "Add new base data to filter block";
	EControl::window_list.push_back(StaticData::window_add_new_base_data);

	StaticData::window_socket_group = new EWindowSocketGroup(2, true);
	StaticData::window_socket_group->name = "Change socket colors";
	EControl::window_list.push_back(StaticData::window_socket_group);




	StaticData::window_loot_simulator = new EWindowLootSimulator(3, true);
	StaticData::window_loot_simulator->name = "Loot simulator";
	EControl::window_list.push_back(StaticData::window_loot_simulator);


	StaticData::window_filter_visual_editor = new EWindowFilterVisualEditor(4, true);
	StaticData::window_filter_visual_editor->name = "Change colors and sounds";
	EControl::window_list.push_back(StaticData::window_filter_visual_editor);





	StaticData::window_find_item = new EWindowFindItem(5, true);
	StaticData::window_find_item->name = "Search item";
	EControl::window_list.push_back(StaticData::window_find_item);

	StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::OPEN_LOOT_FILTER_SEARCH_LIST;
	StaticData::window_find_item->is_active = true;
	StaticData::window_find_item->manual_event();

	StaticData::window_filter_block_search = new EWindowFilterBlockSearch(6, false);
	StaticData::window_filter_block_search->name = "Search filter blocks";
	EControl::window_list.push_back(StaticData::window_filter_block_search);

	StaticData::window_main = new EWindowMain(7, false);
	StaticData::window_main->name = "Main window";
	EControl::window_list.push_back(StaticData::window_main);

	StaticData::window_loading_screen = new EWindowLoadingScreen(8, false);
	StaticData::window_loading_screen->name = "Loading screen";
	StaticData::window_loading_screen->item_count = ItemList::item_list.size();
	EControl::window_list.push_back(StaticData::window_loading_screen);

	StaticData::window_new_loot_filter = new EWindowCreateNewLootFilter(9, true);
	StaticData::window_new_loot_filter->name = "New loot-filter";
	EControl::window_list.push_back(StaticData::window_new_loot_filter);


	StaticData::window_select_localisation = new EWindowSelectLocalisation(10, false);
	StaticData::window_select_localisation->name = "Select language";
	EControl::window_list.push_back(StaticData::window_select_localisation);


	for (EWindow* w:EControl::window_list)
	{
		w->update_localisation();
	}

	EString::load_loot_pattern("important items");

	batch->reset();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);
	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------

	//cout << (int)01.35f << endl;
	glViewport(0, 0, EWindow::SCR_WIDTH, EWindow::SCR_HEIGHT);
	recalculate_correction();
	

	//load_texture("data/background.png", 1);
	while (!glfwWindowShouldClose(window))
	{
		///////////////////////////////////////////////////////////////////////////////
			glViewport(0, 0, 4096, 4096);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendEquation(GL_MAX);

			matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

			matrix_transform = glm::translate(matrix_transform, glm::vec3(camera->x - 1, camera->y - 1, 0.0f));
			matrix_transform = glm::scale(matrix_transform, glm::vec3(camera->zoom / 4096.0f * 2.0f, camera->zoom / 4096.0f * 2.0f, 1));

			ourShader->use();
			unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix_transform));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
			ourShader->setInt("texture1", 0);
			batch->setcolor(EColorCollection::WHITE);

			int last_index = StaticData::window_loading_screen->load_progress + 20;
			if (last_index > ItemList::item_list.size()) { last_index = ItemList::item_list.size(); }

			if (true)
			for (int z = StaticData::window_loading_screen->load_progress; z < last_index; z++)
			{

				//std::cout << "ITEM NAME: " << ItemList::item_list.at(z)->item_name << std::endl;
				//int select = rand() % 3;

				bool duplicate_detected = false;

				for (int f = 0; f < z; f++)
				{
					if
						(
						(f != z)
							&&
							(ItemList::item_list.at(z)->folder == ItemList::item_list.at(f)->folder)
							&&
							(ItemList::item_list.at(z)->icon_path == ItemList::item_list.at(f)->icon_path)
							)
					{
						duplicate_detected = true;

						ItemList::item_list.at(z)->gabarite = ItemList::item_list.at(f)->gabarite;
					//std:cout << "Duplicate detected! Name: " << ItemList::item_list.at(z)->folder << "/" << ItemList::item_list.at(z)->icon_path << std::endl;

						break;
					}

					if (duplicate_detected) { break; }
				}


				if (!duplicate_detected)
				{
					string aaa = "data/icon/" + (ItemList::item_list.at(z)->folder) + "/" + ItemList::item_list.at(z)->icon_path + ".png";
					put_texture_to_atlas(aaa.c_str());
					ItemList::item_list.at(z)->gabarite = just_created_gabarite;
				}

				//if (z % 5 == 0) { cout << "Collision pass:" << green << z << white << endl; }
			}

			StaticData::window_loading_screen->load_progress += 20;

			if (StaticData::window_loading_screen->load_progress >= ItemList::item_list.size())
			{
				StaticData::window_loading_screen->is_active = false;
			}
		///////////////////////////////////////////////////////////////////////////////
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glBlendEquation(GL_FUNC_ADD);
			//--------------------------------------------------------------------------------------------------------
			//--------------------------------------------------------------------------------------------------------

			//cout << (int)01.35f << endl;
			glViewport(0, 0, EWindow::SCR_WIDTH, EWindow::SCR_HEIGHT);
			//recalculate_correction();
		///////////////////////////////////////////////////////////////////////////////


		EButton::top_window_id = -1;

		for (int i = 0; i < EControl::window_list.size(); i++)
		{
			if (
				(EControl::window_list.at(i)->is_overlap())
				&&
				(EControl::window_list.at(i)->is_active)
				)
			{
				EButton::top_window_id = i;
			}
		}

		
		glDisable(GL_DEPTH_TEST);
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.8f, 0.81f, 0.82f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!EControl::button_backspace_released)
		{
			EControl::delete_button_hold_time += delta_time;
		}

		if 
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_RELEASE)
		)
		{
			EControl::button_backspace_released = true;

			EControl::delete_button_hold_time = 0;

		}

		if (0 == GLFW_PRESS)
		{
			EControl::button_pressed = false;
		}

		clock_t time = clock();
		delta_time = (time - saved_time_for_delta) / 1000.0;
		saved_time_for_delta = time;

		camera->update();


		glClear(GL_COLOR_BUFFER_BIT);


		matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		matrix_transform = glm::translate(matrix_transform, glm::vec3(camera->x - 1, camera->y - 1, 0.0f));
		matrix_transform = glm::scale(matrix_transform, glm::vec3(camera->zoom * correction_x, camera->zoom * correction_y, 1));


		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// get matrix's uniform location and set matrix
		ourShader->use();
		transformLoc = glGetUniformLocation(ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix_transform));

		glActiveTexture(GL_TEXTURE0);
		ourShader->setInt("texture1", 0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

		batch->reset();
		batch->draw_rect_with_uv(0, 0, EWindow::SCR_WIDTH, EWindow::SCR_HEIGHT, DefaultGabarite::gabarite_background);

		int block_index = 0;

		for (EWindow* w : EControl::window_list)
		{
			if (w->is_active)
			{

				w->default_update(delta_time);
				w->update(delta_time);
				w->defaul_draw(batch);
				w->draw(batch, delta_time);
			}

			if (w->is_active)
			{
				w->default_text_pass(batch);
				w->text_pass(batch);
			}
		}

		if (glfwGetKey(EWindow::main_window, GLFW_KEY_END) == GLFW_PRESS)
		{
			batch->setcolor(EColorCollection::WHITE);
			batch->draw_rect_with_uv(0.0f, 0.0f, 1000.0f, 1000.0f, DefaultGabarite::gabarite_white);
			batch->draw_rect_with_uv(0.0f, 0.0f, 1000.0f, 1000.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		}

		batch->reinit();
		batch->draw_call();


		if (false)
		{
			glBindVertexArray(0);
			// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
			// clear all relevant buffers
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
			glClear(GL_COLOR_BUFFER_BIT);

			glActiveTexture(GL_TEXTURE0);
			ourShader->setInt("texture1", 0);

			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane



			batch->setcolor(1.0f, 1.0f, 1.0f, 0.9f);
			batch->reset();

			batch->draw_rect_with_uv(0, 4096.0f/4.0f, 4096.0f/4.0f, 4096/1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			//batch->draw_rect_with_uv(500, 500, 100, 100, ItemList::item_list.at(0)->gabarite);

			batch->reinit();
			batch->draw_call();


			
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		processInput(window);

		if (StaticData::window_filter_block->need_remove_last_element)
		{
			StaticData::window_filter_block->filter_block_list.erase
			(
				StaticData::window_filter_block->filter_block_list.end() - 1
			);

			StaticData::window_filter_block->need_remove_last_element = false;
		}
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
void put_texture_to_atlas(char const* _path, EGabarite* _g)
{
	put_texture_to_atlas("data/button_sound.png");
	
	_g = just_created_gabarite;
}

void put_texture_to_atlas(char const* _path)
{
	load_texture(_path, 0);

	for (int j = 0; j < 4000; j+= last_texture_w / 2 + 2)
	for (int i = 0; i < 4000; i+= last_texture_h / 2 + 2)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
		cout << red << "Failed to load texture " <<yellow << "(" << _path << ")" << green << endl;
	}

	stbi_image_free(data1);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	/*
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	*/

	/*
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			ESound::engine->play2D(ESound::default_drop_sound.at(rand() % 26));
		}
	*/

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
	glfwGetWindowSize(window, &EWindow::SCR_WIDTH, &EWindow::SCR_HEIGHT);

	std::cout << "Resize event width:" << width << " height: " << height << std::endl;

	recalculate_correction();
}

void recalculate_correction()
{
	correction_x = 1.0 / EWindow::SCR_WIDTH * 2.0;
	correction_y = 1.0 / EWindow::SCR_HEIGHT * 2.0;

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

	EControl::block_scroll -= yoffset;
	if (EControl::block_scroll < 0) { EControl::block_scroll = 0; }
	cout << "scroll (" << yoffset << ")" << endl;

	int active_block_count = 0;
	for (FilterBlock* fb : StaticData::window_filter_block->filter_block_list)
	{
		if (!fb->is_deactivated) { active_block_count++; }
	}

	if (active_block_count > 0)
	{
		StaticData::window_filter_block->link_to_slider->slider_value = EControl::block_scroll / (active_block_count * 1.0f);
	}
	else
	{
		StaticData::window_filter_block->link_to_slider->slider_value = 0.0f;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		EControl::mouse_pressed = true;
		//cout << "Cursor Position at (" << xpos << " : " << ypos << " button:" << button<<" action:" << action << endl;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		EControl::mouse_right_pressed = true;
		//cout << "Cursor Position at (" << xpos << " : " << ypos << " button:" << button << " action:" << action << endl;
	}

	if ((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE))
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		EControl::button_pressed = false;
		EControl::mouse_pressed = false;

		//cout << "Cursor released at (" << xpos << " : " << ypos << " button:" << button << " action:" << action << endl;
	}

	if ((button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE))
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		EControl::button_right_pressed = false;
		EControl::mouse_right_pressed = false;

		//cout << "Cursor released at (" << xpos << " : " << ypos << " button:" << button << " action:" << action << endl;
	}



	//cout <<" mouse callback. Button=" <<button<<". Action="<<action<<"." << endl;
}

void mouse_position_callback(GLFWwindow* window, double _x, double _y)
{
	//cout << "Mouse move (" << _x << " : " << _y << endl;
	EControl::mouse_x = _x;
	EControl::mouse_y = EWindow::SCR_HEIGHT-_y;

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
	EControl::last_inputed_char = (char)inputed_c;
	//work_text += (char)inputed_c;
}


static bool is_button_pressed(int _key)
{
	if (glfwGetKey(window, _key) == GLFW_PRESS) { return true; } else { return false; }
}

