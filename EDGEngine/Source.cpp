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
int EControl::last_inputed_char_id = 0;

float EControl::delete_button_hold_time = 0.0f;

EFont* EFont::active_font = NULL;

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

//void put_texture_to_atlas(char const* _path,float _x, float _y);
void put_texture_to_atlas(char const* _path);
void put_texture_to_atlas(char const* _path, float _x, float _y);
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
Shader* anisShader;

Shader* currentShader;

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
#include "EUtils.h"
#include <irr/irrKlang.h>



#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>







unsigned int FBO;
unsigned int FBO_texture;

unsigned int rbo;
unsigned int framebuffer;
unsigned int texColorBuffer;

unsigned int last_texture_w;
unsigned int last_texture_h;


bool ***collision_matrix = new bool**[4096];

EGabarite* just_created_gabarite = NULL;

bool texture_error = false;

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
EWindowSelectFont* StaticData::window_select_font =NULL;
EWindowAC* StaticData::window_accept_cancel;
EWindowOil* StaticData::window_oil;
EWindowSelectLootPattern* StaticData::window_select_loot_pattern; 
EWindowManualLoot* StaticData::window_manual_loot; 
//EWindowAcceptCancel* StaticData::window_accept_cancel =NULL;

EWindowFilterBlock* StaticData::default_filter_block =NULL;

std::vector<EWindowFilterBlock*> StaticData::filter_block_tab;
int StaticData::active_tab = 0;
bool StaticData::need_exit = false;

bool loading_finish = false;

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
		//cout << "collision at dim:" << _dim << " x:" << _x << " y:" << _y << endl;

		if ((put_j >= 4096) || (put_i >= 4096)) { return false; }

		if (collision_matrix[put_j][put_i][_dim])
		{
			
			
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
	//if (!check_can_put_here(_x, _y, _size_x, _size_y, 256, 8)) { return false; }
	//if (!check_can_put_here(_x, _y, _size_x, _size_y, 128, 7)) { return false;  }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,64,2)) { return false; }
	//if (!check_can_put_here(_x,_y,_size_x,_size_y,32,5)) { return false; }
	//if (!check_can_put_here(_x,_y,_size_x,_size_y,16,4)) { return false; }
	if (!check_can_put_here(_x,_y,_size_x,_size_y,8,1)) { return false; }
	//if (!check_can_put_here(_x,_y,_size_x,_size_y,4,2)) { return false; }
	//if (!check_can_put_here(_x,_y,_size_x,_size_y,2,1)) { return false; }
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


}

void load_notable_passives()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/NotablePassivesList.txt");
	string line;

	string subdata;
	string subdata_array[6];

	int line_id = 0;
	int data_order;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 1000))
	{

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

		for (int i = 0; i < 2; i++)
		{

			if (subdata_array[i * 2] == "name")
			{
				EString::notable_passives_name.push_back(subdata_array[i * 2 + 1]);
			}

			if (subdata_array[i * 2] == "description")
			{
				EString::notable_passives_description.push_back(subdata_array[i * 2 + 1]);
			}
		}

		line_id++;
	}


}

void load_notable_passives_ru()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/NotablePassivesListRU.txt");
	string line;

	string subdata;
	string subdata_array[6];

	int line_id = 0;
	int data_order;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 1000))
	{

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

		for (int i = 0; i < 2; i++)
		{

			if (subdata_array[i * 2] == "name")
			{


				EString::notable_passives_ru_name.push_back(EString::to_cyrillic(subdata_array[i * 2 + 1]));
			}

			if (subdata_array[i * 2] == "description")
			{EString::notable_passives_ru_description.push_back(EString::to_cyrillic(subdata_array[i * 2 + 1]));}
		}

		line_id++;
	}


}


void load_anointing()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/AnointingList.txt");
	string line;

	string subdata;
	string subdata_array[20];

	int line_id = 0;
	int data_order;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 1000))
	{
		NotablePassive* just_created_passive = new NotablePassive();

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

		for (int i = 0; i < 9; i++)
		{

			if (subdata_array[i * 2] == "oil")
			{
				if (subdata_array[i * 2 + 1] == "Verdant Oil")		{ just_created_passive->need_oil.at(Enums::OilId::VERDANT)++; }
				if (subdata_array[i * 2 + 1] == "Sepia Oil")		{ just_created_passive->need_oil.at(Enums::OilId::SEPIA)++; }
				if (subdata_array[i * 2 + 1] == "Clear Oil")		{ just_created_passive->need_oil.at(Enums::OilId::CLEAR)++; }
				if (subdata_array[i * 2 + 1] == "Amber Oil")		{ just_created_passive->need_oil.at(Enums::OilId::AMBER)++; }
				if (subdata_array[i * 2 + 1] == "Teal Oil")			{ just_created_passive->need_oil.at(Enums::OilId::TEAL)++; }
				if (subdata_array[i * 2 + 1] == "Azure Oil")		{ just_created_passive->need_oil.at(Enums::OilId::AZURE)++; }
				if (subdata_array[i * 2 + 1] == "Violet Oil")		{ just_created_passive->need_oil.at(Enums::OilId::VIOLET)++; }
				if (subdata_array[i * 2 + 1] == "Crimson Oil")		{ just_created_passive->need_oil.at(Enums::OilId::CRIMSON)++; }
				if (subdata_array[i * 2 + 1] == "Black Oil")		{ just_created_passive->need_oil.at(Enums::OilId::BLACK)++; }
				if (subdata_array[i * 2 + 1] == "Opalescent Oil")	{ just_created_passive->need_oil.at(Enums::OilId::OPALESCENT)++; }
				if (subdata_array[i * 2 + 1] == "Silver Oil")		{ just_created_passive->need_oil.at(Enums::OilId::SILVER)++; }
				if (subdata_array[i * 2 + 1] == "Golden Oil")		{ just_created_passive->need_oil.at(Enums::OilId::GOLDEN)++; }
			}

			if (subdata_array[i * 2] == "name")
			{
				just_created_passive->passive_name = subdata_array[i * 2 + 1];
				//name
				for (int j = 0; j < EString::notable_passives_name.size(); j++)
				{
					if (EString::notable_passives_name.at(j) == subdata_array[i * 2 + 1])
					{
						just_created_passive->passive_description = EString::notable_passives_description.at(j);
					}
				}
			}

			if (subdata_array[i * 2] == "name ru")
			{
				just_created_passive->passive_ru_name = EString::to_cyrillic(subdata_array[i * 2 + 1]);
				//name
				for (int j = 0; j < EString::notable_passives_ru_name.size(); j++)
				{
					if (EString::notable_passives_ru_name.at(j) == EString::to_cyrillic(subdata_array[i * 2 + 1]))
					{
						just_created_passive->passive_ru_description = EString::notable_passives_ru_description.at(j);
					}
				}
			}

			if (subdata_array[i * 2] == "icon")
			{
				string aaa = "data/icon/passives/" + subdata_array[i * 2 + 1] + ".png";
				put_texture_to_atlas(aaa.c_str(), 32, 32);

				just_created_passive->gabarite = just_created_gabarite;
			}

			if (subdata_array[i * 2] == "description")
			{
				just_created_passive->passive_description = subdata_array[i * 2 + 1];
			}

			if (subdata_array[i * 2] == "description_ru")
			{
				just_created_passive->passive_ru_description = EString::to_cyrillic(subdata_array[i * 2 + 1]);
			}


		}

		EString::notable_list.push_back(just_created_passive);
		line_id++;
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

	//Enchantment* just_created_enchantment = new Enchantment();
	//just_created_enchantment = ;
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
		//cout << "["<<wtf<< "] base class name: " << b->base_name << " ru name: " << b->ru_name << endl;
		wtf++;
	}
}

void load_enchantment()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/Enchantement.txt");
	string line;

	string subdata;
	string subdata_array[100];

	int line_id = 0;
	int data_order;

	LabEnchantment* just_created_enchantment = NULL;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 2000))
	{
		just_created_enchantment = new LabEnchantment();

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
				just_created_enchantment->base_name = subdata_array[i * 2 + 1];
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

				just_created_enchantment->ru_name = sValid;
			}


		}

		EString::enchantment_list.push_back(just_created_enchantment);

	}

	/*cout << "Enchantement count: " << EString::enchantment_list.size() << endl;
	int wtf = 0;
	for (Enchantment * b : EString::enchantment_list)
	{
		cout << "["<<wtf<< "] enchantement name: " << b->base_name << " ru name: " << b->ru_name << endl;
		wtf++;
	}*/
}

void load_cluster_enchantment()
{
	//ofstream myfile_open;
	//myfile_open.open("gemor.txt");

	ifstream myfile;
	myfile.open("data/ClusterEnchantment.txt");
	string line;

	string subdata;
	string subdata_array[100];

	int line_id = 0;
	int data_order;

	EString::cluster_enchantment_struct* just_created_struct = NULL;

	//cout << EMath::rgb::r << endl;


	while ((getline(myfile, line)) && (line_id < 2000))
	{
		just_created_struct = new EString::cluster_enchantment_struct;

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
				just_created_struct->name = subdata_array[i * 2 + 1];
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

				just_created_struct->ru_name = sValid;
			}


		}

		EString::cluster_enchantment_list.push_back(just_created_struct);

	}

	/*cout << "Enchantement count: " << EString::enchantment_list.size() << endl;
	int wtf = 0;
	for (Enchantment * b : EString::enchantment_list)
	{
		cout << "["<<wtf<< "] enchantement name: " << b->base_name << " ru name: " << b->ru_name << endl;
		wtf++;
	}*/
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
			for (int i = 0; i < 100; i++)
			{
				subdata_array[i] = "";
			}

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

			for (int i = 0; i < 49; i++)
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





//irrklang::ISoundEngine* engine= irrklang::createIrrKlangDevice();
//irrklang::ISoundSource* shootSound = engine->addSoundSourceFromFile("data/cool01.wav");

std::vector<FilterBlock::filter_block_data_attribute_struct*> filter_block_data_attribute_registerer;
int main()
{
	FilterBlock::filter_block_data_attribute_struct* just_created_bdas;
	
	/*
	//corrupted
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Corrupted";
	*just_created_bdas->id = Enums::ParserMode::IS_CORRUPTED;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);*/

	//AlternateQuality
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->id = Enums::ParserMode::ALTERNATIVE_QUALITY;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	/*
	//Replica
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Replica";
	*just_created_bdas->id = Enums::ParserMode::IS_REPLICA;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);*/

	//CorruptedMods
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "CorruptedMods";
	*just_created_bdas->id = Enums::ParserMode::CORRUPTED_MODS;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_INPUT_FIELD;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	//Rarity
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Rarity";
	*just_created_bdas->id = Enums::ParserMode::RARITY;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_DROP_LIST_RARITY;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	/*
	//HasEnchantment
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "HasEnchantment";
	*just_created_bdas->id = Enums::ParserMode::HAS_ENCHANTMENT;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);*/

	/*
	//ShaperItem
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "ShaperItem";
	*just_created_bdas->id = Enums::ParserMode::IS_SHAPER_ITEM;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);
	*/

	//ItemLevel
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "ItemLevel";
	*just_created_bdas->id = Enums::ParserMode::ITEM_LEVEL;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_INPUT_FIELD;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	/*
	//Identified
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Identified";
	*just_created_bdas->id = Enums::ParserMode::IDENTIFIED;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);*/

	/*
	//ElderItem
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "ElderItem";
	*just_created_bdas->id = Enums::ParserMode::IS_ELDER_ITEM;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);*/

	/*
	//FracturedItem
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "FracturedItem";
	*just_created_bdas->id = Enums::ParserMode::IS_FRACTURED_ITEM;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);*/

	//DropLevel
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "DropLevel";
	*just_created_bdas->id = Enums::ParserMode::DROP_LEVEL;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_CHECKBOX;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	//Width
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Width";
	*just_created_bdas->id = Enums::ParserMode::WIDTH;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_INPUT_FIELD;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	//Height
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Height";
	*just_created_bdas->id = Enums::ParserMode::HEIGHT;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_INPUT_FIELD;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);

	/*
	//SynthesisedItem
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "SynthesisedItem";
	*just_created_bdas->id = Enums::ParserMode::IS_SYNTHESISED_ITEM;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_INPUT_FIELD;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);
	*/

	//Quality
	just_created_bdas = new FilterBlock::filter_block_data_attribute_struct;
	*just_created_bdas->name = "Quality";
	*just_created_bdas->id = Enums::ParserMode::QUALITY;
	*just_created_bdas->button_type = Enums::FilterBlockButtonType::FBBT_INPUT_FIELD;
	FilterBlock::filter_block_data_attribute_registerer.push_back(just_created_bdas);



	//engine->play2D("data/cool01.wav");
	for (int i = 0; i < 4096; ++i) {
		collision_matrix[i] = new bool* [4096];
		for (int j = 0; j < 4096; ++j)
			collision_matrix[i][j] = new bool[3];
	}

	for (int i=0; i<4096; i++)
	for (int j=0; j<4096; j++)
	for (int z = 0; z < 3; z++)
	{
		collision_matrix[j][i][z] = false;
	}
	
	//ESound::engine = irrklang::createIrrKlangDevice();
	ESound::engine = irrklang::createIrrKlangDevice(irrklang::E_SOUND_OUTPUT_DRIVER::ESOD_WIN_MM);

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

	ESound::default_drop_sound_name.push_back("ShAlchemy");
	ESound::default_drop_sound_name.push_back("ShBlessed");
	ESound::default_drop_sound_name.push_back("ShChaos");
	ESound::default_drop_sound_name.push_back("ShDivine");
	ESound::default_drop_sound_name.push_back("ShExalted");
	ESound::default_drop_sound_name.push_back("ShFusing");
	ESound::default_drop_sound_name.push_back("ShGeneral");
	ESound::default_drop_sound_name.push_back("ShMirror");
	ESound::default_drop_sound_name.push_back("ShRegal");
	ESound::default_drop_sound_name.push_back("ShVaal");



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

	ESound::default_drop_sound_original_name.push_back("ShAlchemy");
	ESound::default_drop_sound_original_name.push_back("ShBlessed");
	ESound::default_drop_sound_original_name.push_back("ShChaos");
	ESound::default_drop_sound_original_name.push_back("ShDivine");
	ESound::default_drop_sound_original_name.push_back("ShExalted");
	ESound::default_drop_sound_original_name.push_back("ShFusing");
	ESound::default_drop_sound_original_name.push_back("ShGeneral");
	ESound::default_drop_sound_original_name.push_back("ShMirror");
	ESound::default_drop_sound_original_name.push_back("ShRegal");
	ESound::default_drop_sound_original_name.push_back("ShVaal");

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
		/*
		for (int i = 0; i < MAX_PATH; i++)
		{
			cout << "symbol at " << i << "is= " << my_documents[i] << endl;
		}
		*/

		EString::path_to_poe_folder = (string)my_documents + "\\My Games\\Path of Exile\\";
		std::cout << "Path: " << EString::path_to_poe_folder << "\n";

	}

	ESound::load_custom_sound();

	//ofstream writer;
	//writer.open("check.txt");

	

	//writer.close();
	//button_list.push_back(new EButton());

	//filter_block_list.push_back(new FilterBlock());
	//cout << "vector [2]=" << v.at(2) << endl;

	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;





	if (GetUserName(name, &size))
	{
		username = EString::to_cyrillic(name);
		cout << "Hello, " << username << "!\n";
	}
	else
	{
		cout << "Hello, unnamed person!\n";
	}




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
	anisShader = new Shader("data/5.1.transform.vs", "data/AF.fs");

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

	EFont::active_font = new EFont();

	camera->x = 0.0f;
	camera->y = 0.0f;

	for (int i = 0; i < 15000; i++)
	{
		batch->fill_indices();

	}


	



	batch->init();






	//##################################
	//##################################
	parse_item_data();
	load_base_class();
	load_enchantment();
	load_cluster_enchantment();
	load_prophecy_list();
	load_notable_passives();
	load_notable_passives_ru();
	EString::load_loot_pattern_list("!pattern_list");

	EString::load_localisation("EN");

	EBaseData::base_data_registerer* just_create_base_data = NULL;

	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "Corrupted";
		just_create_base_data->have_checkbox = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "AlternateQuality";
		just_create_base_data->have_checkbox = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "Replica";
		just_create_base_data->have_checkbox = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "CorruptedMods";
		just_create_base_data->have_operator = true;
		just_create_base_data->have_number_input = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "LinkedSockets";
		just_create_base_data->have_operator = true;
		just_create_base_data->have_number_input = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "Rarity";
		just_create_base_data->have_operator = true;
		just_create_base_data->drop_list = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "ShaperItem";
		just_create_base_data->have_checkbox = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);


	just_create_base_data = new EBaseData::base_data_registerer;
		just_create_base_data->data_name = "ShaperItem";
		just_create_base_data->have_checkbox = true;
		EBaseData::base_data_registerer_list.push_back(just_create_base_data);



	EBaseData::base_data_registerer_list.push_back(NULL);
	
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

	anisShader->use();
	unsigned int transformLoc = glGetUniformLocation(anisShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix_transform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
	anisShader->setInt("texture1", 0);
	batch->setcolor(EColorCollection::WHITE);

	EFont* new_font=NULL;

	put_texture_to_atlas("data/white_pixel.png");
	just_created_gabarite->x += 1 / 4096.0f;
	just_created_gabarite->y += 1 / 4096.0f;
	just_created_gabarite->x2 -= 1 / 4096.0f;
	just_created_gabarite->y2 -= 1 / 4096.0f;
	DefaultGabarite::gabarite_white = just_created_gabarite;

	put_texture_to_atlas("data/error.png");									DefaultGabarite::gabarite_error = just_created_gabarite;

	put_texture_to_atlas("data/font/littera/fontin_0.png");					new_font = new EFont("fontin", just_created_gabarite, true); 					EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/georgia_0.png");				new_font = new EFont("georgia", just_created_gabarite, false);					EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/verdana_0.png");				new_font = new EFont("verdana", just_created_gabarite, false); 					EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/franklin_0.png");				new_font = new EFont("franklin", just_created_gabarite, false);					EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/arial_0.png");					new_font = new EFont("arial", just_created_gabarite, false); 					EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/trebuchet_0.png");				new_font = new EFont("trebuchet", just_created_gabarite, false); 				EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/times_new_roman_0.png");		new_font = new EFont("times_new_roman", just_created_gabarite, false); 			EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/courier_0.png");				new_font = new EFont("courier", just_created_gabarite, false); 					EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/palatino_0.png");				new_font = new EFont("palatino", just_created_gabarite, false); 				EFont::font_list.push_back(new_font);
	put_texture_to_atlas("data/font/littera/impact_0.png");					new_font = new EFont("impact", just_created_gabarite, false); 					EFont::font_list.push_back(new_font);

	EFont::active_font = EFont::font_list.at(rand() % EFont::font_list.size());

	


	put_texture_to_atlas("data/background.png");			DefaultGabarite::gabarite_background = just_created_gabarite;
	put_texture_to_atlas("data/shaper_bg.png");				DefaultGabarite::gabarite_shaper_bg = just_created_gabarite;
	put_texture_to_atlas("data/elder_bg.png");				DefaultGabarite::gabarite_elder_bg = just_created_gabarite;

	put_texture_to_atlas("data/shaper_bg_small.png");			DefaultGabarite::gabarite_shaper_small = just_created_gabarite;
	put_texture_to_atlas("data/elder_bg_small.png");			DefaultGabarite::gabarite_elder_small = just_created_gabarite;
	put_texture_to_atlas("data/blighted_bg_small.png");			DefaultGabarite::gabarite_blighted_small = just_created_gabarite;

	put_texture_to_atlas("data/cap_rama.png");				DefaultGabarite::gabarite_cap_rama = just_created_gabarite;
	put_texture_to_atlas("data/wood_bg.png");				DefaultGabarite::gabarite_wood_bg = just_created_gabarite;
	put_texture_to_atlas("data/wood_button_bg.png");				DefaultGabarite::gabarite_wood_button_bg = just_created_gabarite;

	cout << "item list size=" << ItemList::item_list.size() << endl;
	


	


	put_texture_to_atlas("data/undefined.png");				DefaultGabarite::gabarite_undefined = just_created_gabarite;
	put_texture_to_atlas("data/plus.png");					DefaultGabarite::gabarite_plus = just_created_gabarite;

	
	put_texture_to_atlas("data/checked.png");					DefaultGabarite::gabarite_checked = just_created_gabarite;
	put_texture_to_atlas("data/unchecked.png");					DefaultGabarite::gabarite_unchecked = just_created_gabarite;
	put_texture_to_atlas("data/button_remove.png");				DefaultGabarite::gabarite_remove = just_created_gabarite;
	put_texture_to_atlas("data/button_plus_wide.png");			DefaultGabarite::gabarite_plus_wide = just_created_gabarite;

	put_texture_to_atlas("data/button_increase.png");			DefaultGabarite::gabarite_increase = just_created_gabarite;
	put_texture_to_atlas("data/button_decrease.png");			DefaultGabarite::gabarite_decrease = just_created_gabarite;

	put_texture_to_atlas("data/button_close.png");				DefaultGabarite::gabarite_close = just_created_gabarite;
	put_texture_to_atlas("data/button_color_mode.png");			DefaultGabarite::gabarite_visual_mode = just_created_gabarite;

	put_texture_to_atlas("data/slider_hue.png");				DefaultGabarite::gabarite_slider_hue = just_created_gabarite;
	put_texture_to_atlas("data/slider_saturation.png");			DefaultGabarite::gabarite_slider_saturation = just_created_gabarite;
	put_texture_to_atlas("data/slider_value.png");				DefaultGabarite::gabarite_slider_value = just_created_gabarite;
	put_texture_to_atlas("data/slider_alpha.png");				DefaultGabarite::gabarite_slider_alpha = just_created_gabarite;

	put_texture_to_atlas("data/visual_editor_bg.png");			DefaultGabarite::gabarite_visual_editor_bg = just_created_gabarite;

	put_texture_to_atlas("data/button_sound.png");				DefaultGabarite::gabarite_play_sound = just_created_gabarite;
	
	put_texture_to_atlas("data/icon_circle.png");				DefaultGabarite::gabarite_minimap_icon[0] = just_created_gabarite;
	put_texture_to_atlas("data/icon_diamond.png");				DefaultGabarite::gabarite_minimap_icon[1] = just_created_gabarite;
	put_texture_to_atlas("data/icon_hexagon.png");				DefaultGabarite::gabarite_minimap_icon[2] = just_created_gabarite;
	put_texture_to_atlas("data/icon_square.png");				DefaultGabarite::gabarite_minimap_icon[3] = just_created_gabarite;
	put_texture_to_atlas("data/icon_star.png");					DefaultGabarite::gabarite_minimap_icon[4] = just_created_gabarite;
	put_texture_to_atlas("data/icon_triangle.png");				DefaultGabarite::gabarite_minimap_icon[5] = just_created_gabarite;

	put_texture_to_atlas("data/icon_cross.png");				DefaultGabarite::gabarite_minimap_icon[6] = just_created_gabarite;
	put_texture_to_atlas("data/icon_moon.png");					DefaultGabarite::gabarite_minimap_icon[7] = just_created_gabarite;
	put_texture_to_atlas("data/icon_raindrop.png");				DefaultGabarite::gabarite_minimap_icon[8] = just_created_gabarite;
	put_texture_to_atlas("data/icon_kite.png");					DefaultGabarite::gabarite_minimap_icon[9] = just_created_gabarite;
	put_texture_to_atlas("data/icon_pentagon.png");				DefaultGabarite::gabarite_minimap_icon[10] = just_created_gabarite;
	put_texture_to_atlas("data/icon_upsidedownhouse.png");		DefaultGabarite::gabarite_minimap_icon[11] = just_created_gabarite;



	put_texture_to_atlas("data/button_load.png");				DefaultGabarite::gabarite_button_load = just_created_gabarite;
	put_texture_to_atlas("data/button_save.png");				DefaultGabarite::gabarite_button_save = just_created_gabarite;

	put_texture_to_atlas("data/bg_noise.png");					DefaultGabarite::gabarite_bg_noise = just_created_gabarite;
	put_texture_to_atlas("data/ray_icon.png");					DefaultGabarite::gabarite_ray_icon = just_created_gabarite;

	put_texture_to_atlas("data/plus_gray.png");					DefaultGabarite::gabarite_plus_gray = just_created_gabarite;
	put_texture_to_atlas("data/up_gray.png");					DefaultGabarite::gabarite_up_gray = just_created_gabarite;
	put_texture_to_atlas("data/down_gray.png");					DefaultGabarite::gabarite_down_gray = just_created_gabarite;

	put_texture_to_atlas("data/remove_block.png");				DefaultGabarite::gabarite_remove_block = just_created_gabarite;

	put_texture_to_atlas("data/gray_eye.png");					DefaultGabarite::gabarite_gray_eye = just_created_gabarite;

	put_texture_to_atlas("data/ray_icon_remove.png");			DefaultGabarite::gabarite_ray_icon_remove = just_created_gabarite;

	put_texture_to_atlas("data/button_new.png");				DefaultGabarite::gabarite_button_new = just_created_gabarite;

	put_texture_to_atlas("data/plus_circle.png");				DefaultGabarite::gabarite_plus_circle = just_created_gabarite;
	put_texture_to_atlas("data/remove_circle.png");				DefaultGabarite::gabarite_remove_circle = just_created_gabarite;

	put_texture_to_atlas("data/flag_EN.png");					DefaultGabarite::gabarite_flag_EN = just_created_gabarite;
	put_texture_to_atlas("data/flag_RU.png");					DefaultGabarite::gabarite_flag_RU = just_created_gabarite;

	put_texture_to_atlas("data/button_simulator.png");			DefaultGabarite::gabarite_open_simulator = just_created_gabarite;
	put_texture_to_atlas("data/button_configue_font.png");		DefaultGabarite::gabarite_configue_font = just_created_gabarite;
	put_texture_to_atlas("data/button_configue_language.png");	DefaultGabarite::gabarite_configue_language = just_created_gabarite;

	put_texture_to_atlas("data/cut_gray.png");					DefaultGabarite::gabarite_cut_gray = just_created_gabarite;

	put_texture_to_atlas("data/bg_bright.png");					DefaultGabarite::gabarite_bg_bright = just_created_gabarite;
	put_texture_to_atlas("data/bg_dark.png");					DefaultGabarite::gabarite_bg_dark = just_created_gabarite;

	put_texture_to_atlas("data/button_refresh.png");			DefaultGabarite::gabarite_button_refresh = just_created_gabarite;

	put_texture_to_atlas("data/button_bright_bg.png");			DefaultGabarite::gabarite_button_bright_bg = just_created_gabarite;
	put_texture_to_atlas("data/button_dark_bg.png");			DefaultGabarite::gabarite_button_dark_bg = just_created_gabarite;

	put_texture_to_atlas("data/button_clone.png");				DefaultGabarite::gabarite_button_clone = just_created_gabarite;
	put_texture_to_atlas("data/gray_separator.png");			DefaultGabarite::gabarite_button_separator = just_created_gabarite;
	put_texture_to_atlas("data/gray_collapse.png");				DefaultGabarite::gabarite_button_collapse = just_created_gabarite;                        

	put_texture_to_atlas("data/icon/currency/Clear_Oil.png");		DefaultGabarite::gabarite_oil[0] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Sepia_Oil.png");		DefaultGabarite::gabarite_oil[1] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Amber_Oil.png");		DefaultGabarite::gabarite_oil[2] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Verdant_Oil.png");		DefaultGabarite::gabarite_oil[3] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Teal_Oil.png");		DefaultGabarite::gabarite_oil[4] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Azure_Oil.png");		DefaultGabarite::gabarite_oil[5] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Violet_Oil.png");		DefaultGabarite::gabarite_oil[6] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Crimson_Oil.png");		DefaultGabarite::gabarite_oil[7] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Black_Oil.png");		DefaultGabarite::gabarite_oil[8] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Opalescent_Oil.png");	DefaultGabarite::gabarite_oil[9] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Silver_Oil.png");		DefaultGabarite::gabarite_oil[10] = just_created_gabarite;
	put_texture_to_atlas("data/icon/currency/Golden_Oil.png");		DefaultGabarite::gabarite_oil[11] = just_created_gabarite;

	put_texture_to_atlas("data/cap.png");							DefaultGabarite::gabarite_cap = just_created_gabarite;
	put_texture_to_atlas("data/socket.png");						DefaultGabarite::gabarite_socket = just_created_gabarite;

	put_texture_to_atlas("data/link_horizontal.png");				DefaultGabarite::gabarite_link_horizontal = just_created_gabarite;
	put_texture_to_atlas("data/link_vertical.png");					DefaultGabarite::gabarite_link_vertical = just_created_gabarite;

	put_texture_to_atlas("data/button_save_autogen.png");			DefaultGabarite::gabarite_save_autogen = just_created_gabarite;
	put_texture_to_atlas("data/plus_equal.png");					DefaultGabarite::gabarite_plus_equal = just_created_gabarite;
 
	put_texture_to_atlas("data/button_continue_on.png");			DefaultGabarite::gabarite_button_continue_on = just_created_gabarite;
	put_texture_to_atlas("data/button_continue_off.png");			DefaultGabarite::gabarite_button_continue_off = just_created_gabarite;

	put_texture_to_atlas("data/disable_block.png");					DefaultGabarite::gabarite_button_disable_block = just_created_gabarite;
	put_texture_to_atlas("data/enable_block.png");					DefaultGabarite::gabarite_button_enable_block = just_created_gabarite;

	put_texture_to_atlas("data/shaper_slider_bg.png");				DefaultGabarite::gabarite_shaper_slider_bg = just_created_gabarite;
	put_texture_to_atlas("data/shaper_slider_head.png");			DefaultGabarite::gabarite_shaper_slider_head = just_created_gabarite;
	put_texture_to_atlas("data/shaper_slider_trail.png");			DefaultGabarite::gabarite_shaper_slider_trail = just_created_gabarite;

	put_texture_to_atlas("data/button_oil.png");					DefaultGabarite::gabarite_button_oil = just_created_gabarite; 
	 


	load_anointing();

	StaticData::window_filter_block = new EWindowFilterBlock(0, false);
	StaticData::window_filter_block->name = "Filter block";
	EControl::window_list.push_back(StaticData::window_filter_block);
	StaticData::window_filter_block->is_active = false;

	for (int i = 0; i < 7; i++)
	{
		StaticData::filter_block_tab.push_back(new EWindowFilterBlock(0, false));
		EString::path_list.push_back("");
	}

	StaticData::default_filter_block = new EWindowFilterBlock(0, false);
	StaticData::default_filter_block->name = "Default filter block";
	StaticData::default_filter_block->is_active = false;

	StaticData::window_filter_block = StaticData::default_filter_block;

	EFile::parse_loot_filter_data("data/default.filter");

	StaticData::window_filter_block = StaticData::filter_block_tab.at(0);
	EControl::window_list.at(0) = StaticData::filter_block_tab.at(0);
	
	EString::load_loot_filter_list();
	//std::string path = "/path/to/directory";


	StaticData::window_add_new_base_data = new EWindowAddNewBaseData(1, true);
	StaticData::window_add_new_base_data->name = "Add new base data to filter block";
	EControl::window_list.push_back(StaticData::window_add_new_base_data);
	StaticData::window_add_new_base_data->is_active = false;

	StaticData::window_socket_group = new EWindowSocketGroup(2, true);
	StaticData::window_socket_group->name = "Change socket colors";
	EControl::window_list.push_back(StaticData::window_socket_group);
	StaticData::window_socket_group->is_active = false;









	StaticData::window_filter_block_search = new EWindowFilterBlockSearch(3, false);
	StaticData::window_filter_block_search->name = "Search filter blocks";
	EControl::window_list.push_back(StaticData::window_filter_block_search);
	StaticData::window_filter_block_search->is_active = true;

	StaticData::window_oil = new EWindowOil(4, true);
	StaticData::window_oil->name = "Oils";
	EControl::window_list.push_back(StaticData::window_oil);
	StaticData::window_oil->is_active = false;


	StaticData::window_main = new EWindowMain(5, false);
	StaticData::window_main->name = "Main window";
	EControl::window_list.push_back(StaticData::window_main);
	StaticData::window_main->is_active = true;

	StaticData::window_loot_simulator = new EWindowLootSimulator(6, true);
	StaticData::window_loot_simulator->name = "Loot simulator";
	EControl::window_list.push_back(StaticData::window_loot_simulator);
	StaticData::window_loot_simulator->is_active = false;

	StaticData::window_select_loot_pattern = new EWindowSelectLootPattern(7, true);
	StaticData::window_select_loot_pattern->name = "Select loot pattern";
	EControl::window_list.push_back(StaticData::window_select_loot_pattern);
	StaticData::window_select_loot_pattern->is_active = false;

	StaticData::window_filter_visual_editor = new EWindowFilterVisualEditor(8, true);
	StaticData::window_filter_visual_editor->name = "Change colors and sounds";
	EControl::window_list.push_back(StaticData::window_filter_visual_editor);
	StaticData::window_filter_visual_editor->is_active = false;

	StaticData::window_manual_loot = new EWindowManualLoot(9, true);
	StaticData::window_manual_loot->name = "Manual loot";
	EControl::window_list.push_back(StaticData::window_manual_loot);
	//StaticData::window_manual_loot->window_searchs_mode = Enums::WindowSearchMode::OPEN_LOOT_FILTER_SEARCH_LIST;
	//StaticData::window_manual_loot->manual_event();
	StaticData::window_manual_loot->is_active = false;

	StaticData::window_find_item = new EWindowFindItem(10, true);
	StaticData::window_find_item->name = "Search item";
	EControl::window_list.push_back(StaticData::window_find_item);
	StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::OPEN_LOOT_FILTER_SEARCH_LIST;
	StaticData::window_find_item->manual_event();
	StaticData::window_find_item->is_active = false;



	StaticData::window_loading_screen = new EWindowLoadingScreen(11, false);
	StaticData::window_loading_screen->name = "Loading screen";
	StaticData::window_loading_screen->item_count = ItemList::item_list.size();
	EControl::window_list.push_back(StaticData::window_loading_screen);
	StaticData::window_loading_screen->is_active = true;


	StaticData::window_new_loot_filter = new EWindowCreateNewLootFilter(12, true);
	StaticData::window_new_loot_filter->name = "New loot-filter";
	EControl::window_list.push_back(StaticData::window_new_loot_filter);
	StaticData::window_new_loot_filter->is_active = false;

	StaticData::window_select_localisation = new EWindowSelectLocalisation(13, false);
	StaticData::window_select_localisation->name = "Select language";
	EControl::window_list.push_back(StaticData::window_select_localisation);
	StaticData::window_select_localisation->is_active = false;


	StaticData::window_select_font = new EWindowSelectFont(14, true);
	StaticData::window_select_font->name = "Select font";
	EControl::window_list.push_back(StaticData::window_select_font);
	StaticData::window_select_font->is_active = false;

	StaticData::window_accept_cancel = new EWindowAC(15, true);
	StaticData::window_accept_cancel->name = "Accept/cancel";
	EControl::window_list.push_back(StaticData::window_accept_cancel);
	StaticData::window_accept_cancel->is_active = false;



	/*
	for (EWindow* w:EControl::window_list)
	{
		w->update_localisation();
	}*/



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

	EString::load_config();

	for (EWindow* w : EControl::window_list)
	{
		w->update_localisation();
	}

	while (!StaticData::need_exit)
	{
		///////////////////////////////////////////////////////////////////////////////

		int last_index = StaticData::window_loading_screen->load_progress + 50;
		if (last_index > ItemList::item_list.size()) { last_index = ItemList::item_list.size(); }

		if (!loading_finish)
		{
			glViewport(0, 0, 4096, 4096);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendEquation(GL_MAX);

			matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

			matrix_transform = glm::translate(matrix_transform, glm::vec3(camera->x - 1, camera->y - 1, 0.0f));
			matrix_transform = glm::scale(matrix_transform, glm::vec3(camera->zoom / 4096.0f * 2.0f, camera->zoom / 4096.0f * 2.0f, 1));

			anisShader->use();
			unsigned int transformLoc = glGetUniformLocation(anisShader->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix_transform));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
			anisShader->setInt("texture1", 0);
			batch->setcolor(EColorCollection::WHITE);
		}
			

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

			

			/*
			if (StaticData::window_loading_screen->load_progress >= ItemList::item_list.size())
			{
				StaticData::window_loading_screen->is_active = false;




			}*/
			///////////////////////////////////////////////////////////////////////////////
			if (!loading_finish)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glDisable(GL_DEPTH_TEST);
				glBlendEquation(GL_FUNC_ADD);
				//--------------------------------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------------------------------

				//cout << (int)01.35f << endl;
				glViewport(0, 0, EWindow::SCR_WIDTH, EWindow::SCR_HEIGHT);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);
				anisShader->setInt("texture1", 0);
				batch->setcolor(EColorCollection::WHITE);
			}
			
			StaticData::window_loading_screen->load_progress += 50;
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
		if ((glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)) { currentShader = anisShader; } else { currentShader = ourShader; } 

		currentShader->use();
		transformLoc = glGetUniformLocation(currentShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix_transform));

		glActiveTexture(GL_TEXTURE0);
		currentShader->setInt("texture1", 0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

		batch->reset();
		batch->setcolor(EColorCollection::WHITE);
		batch->draw_rect_with_uv(0, 0, EWindow::SCR_WIDTH, EWindow::SCR_HEIGHT, DefaultGabarite::gabarite_background);

		int block_index = 0;

		

		if (glfwWindowShouldClose(window))
		{

			bool have_unsaved = false;

			for (EWindowFilterBlock* wfb : StaticData::filter_block_tab)
			{
				if (wfb->unsave_change) { have_unsaved = true; }
			}

			if (have_unsaved)
			{
				glfwSetWindowShouldClose(window, 0);

				StaticData::window_accept_cancel->is_active = true;
				StaticData::window_accept_cancel->window_mode = Enums::WindowAcceptCancelMode::AC_exit_program;

				StaticData::window_accept_cancel->update_localisation();
			}
			else
			{StaticData::need_exit = true; }
			//StaticData::window_accept_cancel->manual_event();

			cout << "try close" << endl;
		}

		for (EWindow* w : EControl::window_list)
		{
			if (w->is_active)
			{

				w->default_update(delta_time);
				w->update(delta_time);
				w->pre_draw(batch, delta_time);
				w->defaul_draw(batch); 
				w->draw(batch, delta_time);
			} 

			if (w->is_active)
			{
				w->default_text_pass(batch);
				w->text_pass(batch);
			} 
		}


		if ((StaticData::window_loading_screen->load_progress >= ItemList::item_list.size()) && (StaticData::window_loading_screen->is_active))
		{

			for (int i = 0; i < 4096; i++)
			{
				for (int j = 0; j < 4096; j++)
				{
					delete[] collision_matrix[i][j];
				}

				delete[] collision_matrix[i];
			}

			delete[] collision_matrix;

			StaticData::window_loading_screen->is_active = false;

			if (!EString::localisation_is_configued)
			{
				StaticData::window_select_localisation->is_active = true;
			}
			else
			{
				if (!EString::font_is_configued)
				{
					StaticData::window_select_font->is_active = true;
				}
				else
				{
					StaticData::window_find_item->is_active = true;
				}
			}

			loading_finish = true;

		}

		/*if (glfwGetKey(EWindow::main_window, GLFW_KEY_END) == GLFW_PRESS)
		{
			for (int i = 0; i < 4096; i++)
			{
				for (int j = 0; j < 4096; j++)
				{
					delete[] collision_matrix[i][j];
				}

				delete[] collision_matrix[i];
			}

			delete[] collision_matrix;
		}*/

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
			currentShader->setInt("texture1", 0);

			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane



			batch->setcolor(1.0f, 1.0f, 1.0f, 0.9f);
			batch->reset();

			batch->draw_rect_with_uv(0, 4096.0f/4.0f, 4096.0f/4.0f, 4096/1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			//batch->draw_rect_with_uv(500, 500, 100, 100, ItemList::item_list.at(0)->gabarite);

			batch->reinit();
			batch->draw_call();


			
		}

		EControl::last_inputed_char = NULL;
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
	for (int xx = (int)(_x / _siz); xx <= (int)((_x + _size_x) / _siz); xx++)
	for (int yy = (int)(_y / _siz); yy <= (int)((_y + _size_y) / _siz); yy++)
	{
		if ((xx >= 0)&&(yy >=0)&&(xx < 4096)&&(yy < 4096))
		collision_matrix[xx][yy][_dim] = true;
	}
}

void put_resized_texture_to_atlas(char const* _path, float _x, float _y)
{

}

void put_texture_to_atlas(char const* _path, EGabarite* _g)
{
	put_texture_to_atlas("data/button_sound.png", 0, 0);
	
	_g = just_created_gabarite;
}

void put_texture_to_atlas(char const* _path)
{
	put_texture_to_atlas(_path, 0, 0);
}

void put_texture_to_atlas(char const* _path, float _x, float _y)
{
	load_texture(_path, 0);

	if (_x > 0) { last_texture_w = _x; }
	if (_y > 0) { last_texture_h = _y; }

	for (int j = 0; j < 4096; j+= last_texture_w / 8 + 1)
	for (int i = 0; i < 4096; i+= last_texture_h / 8 + 1)
		{
			if (is_no_collision(j, i, last_texture_w, last_texture_h))
			{
				//cout << "Find place (" << _path << ")" << endl;

				fill_collision(j - 1,i - 1,last_texture_w + 1,last_texture_h + 1,1,0);
				//fill_collision(j,i,last_texture_w,last_texture_h,2,1);
				//fill_collision(j,i,last_texture_w,last_texture_h,4,2);
				fill_collision(j,i,last_texture_w,last_texture_h,8,1);
				//fill_collision(j,i,last_texture_w,last_texture_h,16,4);
				//fill_collision(j,i,last_texture_w,last_texture_h,32,5);
				fill_collision(j,i,last_texture_w,last_texture_h,64,2);
				//fill_collision(j,i,last_texture_w,last_texture_h,128,7);
				//fill_collision(j,i,last_texture_w,last_texture_h,256,8);

				batch->reset();
				batch->draw_rect(j, i, last_texture_w, last_texture_h);
				batch->reinit();
				batch->draw_call();

				if (texture_error)
				{just_created_gabarite = DefaultGabarite::gabarite_error;}
				else
				{just_created_gabarite = new EGabarite(_path, j / 4096.0f, i / 4096.0f, last_texture_w / 4096.0f, last_texture_h / 4096.0f); }
				
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

		texture_error = false;
		/*texture_w[_id] = width;
		texture_h[_id] = height;*/
	}
	else
	{
		cout << red << "Failed to load texture " <<yellow << "(" << _path << ")" << green << endl;

		last_texture_h = 21;
		last_texture_w = 21;

		texture_error = true;

		just_created_gabarite = DefaultGabarite::gabarite_error;
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
	if ((EWindow::SCR_WIDTH > 100) && (EWindow::SCR_HEIGHT > 100))
	{
	
		correction_x = 1.0 / EWindow::SCR_WIDTH * 2.0;
		correction_y = 1.0 / EWindow::SCR_HEIGHT * 2.0;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}
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
	if (EControl::block_scroll >= StaticData::window_filter_block->filter_block_list.size()) { EControl::block_scroll = StaticData::window_filter_block->filter_block_list.size()-1; }
	
	if (StaticData::window_filter_block->filter_block_list.at(EControl::block_scroll)->hided_by_separator) { EControl::block_scroll -= yoffset * 2; }

	if (EControl::block_scroll < 0) { EControl::block_scroll = 0; }
	if (EControl::block_scroll > StaticData::window_filter_block->filter_block_list.size()) { EControl::block_scroll = StaticData::window_filter_block->filter_block_list.size(); }
	//cout << "scroll (" << yoffset << ")" << endl;

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

	//cout << "input character: " << inputed_c <<"|"<<(int)_char << "[  " << (char)inputed_c << " ]" << " ("<<work_text<<")" <<endl;

	EControl::last_inputed_char = (char)inputed_c;

	//work_text += (char)inputed_c;
}


static bool is_button_pressed(int _key)
{
	if (glfwGetKey(window, _key) == GLFW_PRESS) { return true; } else { return false; }
}

