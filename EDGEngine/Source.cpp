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
#include "EButton.cpp"
#include "FilterBlock.cpp"



#include "ETexture.cpp"

using namespace std;
using namespace VectorMath;
//Helper helper_object;



static int im_static = 0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void recalculate_correction();
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double _x, double _y);
void char_input_callback(GLFWwindow* window, unsigned int _char);

//void load_texture();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void load_texture(const char* _path, int _id);

// settings
int SCR_WIDTH = 640;
int SCR_HEIGHT = 640;



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


unsigned int ETexture::texture[32];

string username;
string path_to_poe_folder;


#include <windows.h>
#include <Lmcons.h>
#include <shlobj.h>
#include "Enums.h"

#include "ConsoleColor.h"

int block_scroll=0;

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

	while ((getline(myfile, line))&&(line_number<100))
	{

		//std::cout << "array is " << sizeof(condition_names)  << " length" << std::endl;

		bool comment_mode = false;
		string subdata = "";
		data_order = 0;
		parser_mode = Enums::ParserMode::NOTHING;

		bool space_is_not_separator = false;

		

		cout << "#################" << endl;
		cout <<green<< "___what readed: '" << blue << line  <<"'" << white << endl;
		cout << "#################" << endl << endl;

		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) == '"') { space_is_not_separator = !space_is_not_separator; }
			if (line.at(i) == '#') { comment_mode = true; cout << "comment mode activate, now i dont parse data by normal way" << endl;  parser_mode = Enums::ParserMode::NOTHING; }

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

					cout << "--- subdata:'" << subdata <<"'" << endl;
					

					if (parser_mode == Enums::ParserMode::NOTHING)
					{
						if (!comment_mode)
						{
							if (subdata == "Show") { just_created_block = new FilterBlock(); filter_block_list.push_back(just_created_block); parser_mode = Enums::ParserMode::SHOW;  cout << "And new block is created!" << endl; }

							if (subdata == "Corrupted") { parser_mode = Enums::ParserMode::IS_CORRUPTED; just_created_block->is_corrupted_active = true; }
							if (subdata == "LinkedSockets") { parser_mode = Enums::ParserMode::LINKED_SOCKETS; just_created_block->is_links_active = true; }
							if (subdata == "Rarity") { parser_mode = Enums::ParserMode::RARITY; just_created_block->is_item_rarity_active = true; }
							if (subdata == "Class") { parser_mode = Enums::ParserMode::CLASS; }

							if (subdata == "SetFontSize") { parser_mode = Enums::ParserMode::FONT_SIZE; just_created_block->is_font_size_active = true;}
							if (subdata == "SetTextColor") { parser_mode = Enums::ParserMode::TEXT_COLOR; just_created_block->is_text_color_active = true;
							}
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
							
						}
					}
					else
					{
						if (parser_mode == Enums::ParserMode::IS_CORRUPTED)
						{
							if (data_order == 0) { cout << "activate corrupted property" << endl; }
							if (data_order == 1) { cout << "set corruption as <" << subdata << ">" << endl; just_created_block->is_corrupted = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::LINKED_SOCKETS)
						{
							if (data_order == 0) { cout << "activate links property" << endl; }

							if ((data_order == 1) && (!check_is_condition_symbols(subdata))) { cout << "set links as <" << subdata << ">" << endl; just_created_block->links_count = std::stoi(subdata); just_created_block->links_condition = Enums::ConditionSymbols::EQUAL; }
							if ((data_order == 1) && (check_is_condition_symbols(subdata))) { cout << "set links condition as <" << subdata << ">" << endl; just_created_block->links_condition = Enums::ConditionSymbols(get_id_from_array(condition_names,subdata)); }

							if (data_order == 2) { cout << "set links as <" << subdata << ">" << endl; just_created_block->links_count = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::RARITY)
						{
							if (data_order == 0) { cout << "activate rarity property" << endl; }

							if ((data_order == 1) && (!check_is_condition_symbols(subdata))) { cout << "set rarity as <" << subdata << ">" << endl; just_created_block->item_rarity = Enums::rarity(get_id_from_array(rarity_value,subdata)); just_created_block->rarity_condition = Enums::ConditionSymbols::EQUAL; }
							if ((data_order == 1) && (check_is_condition_symbols(subdata))) { cout << "set rarity condition as <" << subdata << ">" << endl; just_created_block->rarity_condition = Enums::ConditionSymbols(get_id_from_array(condition_names, subdata)); }

							if (data_order == 2) { cout << "set rarity as <" << subdata << ">" << endl; just_created_block->item_rarity = Enums::rarity(get_id_from_array(rarity_value, subdata));}
						}


						if (parser_mode == Enums::ParserMode::CLASS)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0) { cout << "add new base class <" << subdata << ">" << endl; just_created_block->class_list.push_back(new string(subdata)); }
						}

						if (parser_mode == Enums::ParserMode::FONT_SIZE)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0) { cout << "set font size <" << subdata << ">" << endl; just_created_block->font_size=std::stoi(subdata); }
						}
						
						if (parser_mode == Enums::ParserMode::TEXT_COLOR)
						{
							if (data_order == 0) { cout << "activate text color property" << endl;}
							if (data_order == 1) { cout << "set font color (red) <" << subdata << ">" << endl; just_created_block->text_color_red=std::stoi(subdata); }
							if (data_order == 2) { cout << "set font color (green) <" << subdata << ">" << endl; just_created_block->text_color_green=std::stoi(subdata); }
							if (data_order == 3) { cout << "set font color (blue) <" << subdata << ">" << endl; just_created_block->text_color_blue=std::stoi(subdata); }
							if (data_order == 4) { cout << "set font color (alpha) <" << subdata << ">" << endl; just_created_block->text_color_alpha=std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::BORDER_COLOR)
						{
							if (data_order == 0) { cout << "activate border color property" << endl;  }
							if (data_order == 1) { cout << "set border color (red) <" << subdata << ">" << endl; just_created_block->rama_red = std::stoi(subdata); }
							if (data_order == 2) { cout << "set border color (green) <" << subdata << ">" << endl; just_created_block->rama_green = std::stoi(subdata); }
							if (data_order == 3) { cout << "set border color (blue) <" << subdata << ">" << endl; just_created_block->rama_blue = std::stoi(subdata); }
							if (data_order == 4) { cout << "set border color (alpha) <" << subdata << ">" << endl; just_created_block->rama_alpha = std::stoi(subdata); }
						}						
						
						if (parser_mode == Enums::ParserMode::BACKGROUND_COLOR)
						{
							if (data_order == 0) { cout << "activate background color property" << endl;  }
							if (data_order == 1) { cout << "set background color (red) <" << subdata << ">" << endl; just_created_block->bg_red = std::stoi(subdata); }
							if (data_order == 2) { cout << "set background color (green) <" << subdata << ">" << endl; just_created_block->bg_green = std::stoi(subdata); }
							if (data_order == 3) { cout << "set background color (blue) <" << subdata << ">" << endl; just_created_block->bg_blue = std::stoi(subdata); }
							if (data_order == 4) { cout << "set background color (alpha) <" << subdata << ">" << endl; just_created_block->bg_alpha = std::stoi(subdata); }
						}
						
						if (parser_mode == Enums::ParserMode::ALERT_SOUND)
						{
							if (data_order == 0) { cout << "activate alert sound property" << endl;  }
							if (data_order == 1) { cout << "set alert sound name <" << subdata << ">" << endl; just_created_block->alert_sound_name = subdata; }
							if (data_order == 2) { cout << "set alert sound volume <" << subdata << ">" << endl; just_created_block->alert_sound_volume = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::RAY)
						{
							if (data_order == 0) { cout << "activate ray property" << endl; }

							if (data_order == 1) { cout << "set ray color <" << subdata << ">" << endl; just_created_block->ray_color = Enums::GameColors(get_id_from_game_color_text(subdata)); }
							//if (data_order == 2) { cout << "set alert sound volume <" << subdata << ">" << endl; just_created_block->alert_sound_volume = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::BASETYPE)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0) { cout << "add new base type <" << subdata << ">" << endl; just_created_block->base_type_list.push_back(new string(subdata)); }
						}

						if (parser_mode == Enums::ParserMode::IS_SHAPER_ITEM)
						{
							if (data_order == 0) { cout << "activate shaper item property" << endl; }
							if (data_order == 1) { cout << "set shaper item as <" << subdata << ">" << endl; just_created_block->is_shaper_item = convert_text_to_bool(subdata); }
						}

						if (parser_mode == Enums::ParserMode::ITEM_LEVEL)
						{
							if (data_order == 0) { cout << "activate item level" << endl; }


							if ((data_order == 1) && (!check_is_condition_symbols(subdata))) { cout << "set item level as <" << subdata << "> condition autogenerated" << endl; just_created_block->item_level = std::stoi(subdata); just_created_block->item_level_condition = Enums::ConditionSymbols::EQUAL; }
							if ((data_order == 1) && (check_is_condition_symbols(subdata))) { cout << "set item level condition as <" << subdata << "> id of symbol=" << get_id_from_array(condition_names, "=") << endl; just_created_block->item_level_condition = Enums::ConditionSymbols(get_id_from_array(condition_names, subdata)); }

							if (data_order == 2) { cout << "set item_level as <" << subdata << ">" << endl; just_created_block->item_level = std::stoi(subdata); }
						}

						if (parser_mode == Enums::ParserMode::EXPLICIT_MOD)
						{
							//if (data_order == 0) { cout << "activate rarity property" << endl; }
							if (data_order > 0) { cout << "add new explicit mod <" << subdata << ">" << endl; just_created_block->explicit_mod_list.push_back(new string(subdata)); }
						}

						if (parser_mode == Enums::ParserMode::IDENTIFIED)
						{
							if (data_order == 0) { cout << "activate indetify property" << endl; }
							if (data_order == 1) { cout << "set indetification as <" << subdata << ">" << endl; just_created_block->is_identified = convert_text_to_bool(subdata); }
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
					cout << "--EMPTY SUBDATA#" << endl;
				}
			}
		}
		cout <<  endl << endl;
		
		line_number++;
	}

	if (error_counts <= 0) { cout << green << "Error count:0"; }
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

	//##################################
	//##################################
	parse_loot_filter_data(path_to_poe_folder+"NeverSink's filter.filter");
	//##################################
	//##################################

	ofstream myfile;
	myfile.open("example.txt");

	for (int i = 0; i < 256; i++)
	{
		myfile << (char)i;
	}
	myfile.close();

	recalculate_correction();
	setlocale(LC_ALL, "Russian");
	setlocale(LC_ALL, "ru_RU.UTF-8");
	setlocale(LC_ALL, "");

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
				available_tile[k]=k;
			}


			//exclude potencial duplicate
			for (int b=-1; b<=1; b++)
			for (int a=-1; a<=1; a++)
			if (
				(
					(a!=0)||(b!=0)
				)
				&&(j>=0)
				&& (j<100)
				&& (i>=0)
				&& (i<100))
			{
				int target_tile = tilemap[j + b][i + a];

				//if (target_tile >= 0) { available_tile[target_tile] = -1; }
			}


			tile_array_index = 0;
			for (int k = 0; k < 16; k++)
			if (available_tile[k]>=0)
			{
				final_available_tile[tile_array_index] = available_tile[k];
				tile_array_index++;
			}

			int selected_tile = final_available_tile[rand() % tile_array_index];

			//available_tile._Make_iter;

			//tilemap[j][i] = choosen_tile._Getcont;

			if (rand() % 25 != 0) { selected_tile += 4; } else { selected_tile =rand()%4;}
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
	ourShader=new Shader ("data/5.1.transform.vs", "data/5.1.transform.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------


	// load and create a texture 
	// -------------------------
	// texture 1
	// ---------
	load_texture("data/white_pixel.png",0);
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ETexture::texture[0]);

	batch = new Batcher();
	batch2 = new Batcher();
	font_batch = new Batcher();


	camera = new ECamera();

	font = new EFont();

	camera->x = 0.0f;
	camera->y = 0.0f;
	//camera->zoom = 1;


	for (int i = 0; i < 30; i++)
	for (int j = 0; j < 30; j++)
	{
		int tile_y = (int)(tilemap[j][i] / 4);
		int tile_x = tilemap[j][i] - tile_y * 4;


		batch->draw_rect(0.1f * j, 0.1f * i, 0.05f, 0.05f, tile_x, tile_y);
		batch2->draw_rect(0.1f* j, 0.1f* i, 0.05f, 0.05f, tile_x, tile_y);
	}

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

	while (!glfwWindowShouldClose(window))
	{
		clock_t time = clock();
		delta_time = (time-saved_time_for_delta)/1000.0;
		saved_time_for_delta = time;

		camera->update();

		glClearColor(0.1f, 0.11f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		transform = glm::translate(transform, glm::vec3(camera->x-1, camera->y-1, 0.0f));
		transform = glm::scale(transform, glm::vec3(camera->zoom*correction_x, camera->zoom * correction_y, 1));


		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// get matrix's uniform location and set matrix
		ourShader->use();
		unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// render container


		/*
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		*/




		//batch->draw_call();



		
			/*
			for (int i=0; i<10; i++)
			for (int j = 0; j < 10; j++)
			{
				font->x_adding = 0;
			

				font->draw(font_batch, "Ё", j*100, i*100);
			}*/
		

		batch->reset();
		//batch->setcolor_255(0, 0, 255, 100);

		//button_list.at(0)->draw(batch);
		//batch->setcolor_255(0, 0, 0, 100);
		int block_index = 0;

		for (int i = 0; i < 5; i++)
		{
			block_index = i + block_scroll;

			if (block_index < filter_block_list.size())
			{
				filter_block_list.at(block_index)->x = 15;
				filter_block_list.at(block_index)->y = SCR_HEIGHT - filter_block_list.at(block_index)->size_y - 15 - i * 105;
				filter_block_list.at(block_index)->size_x = SCR_WIDTH - 30;

				filter_block_list.at(block_index)->draw(batch);
			}
		}




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

		font_batch->reset(); 

		font_batch->setcolor_255(255, 255, 255, 100);
		for (int i = 0; i < 5; i++)
		{
			block_index = i + block_scroll;

			if (block_index < filter_block_list.size())
			{
				filter_block_list.at(block_index)->text_pass(font, font_batch);
			}
		}
		font->draw(font_batch, "01!02!03!04" + work_text, 0, 100);
		
		font_batch->reinit();
		font_batch->draw_call();

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
		cout << "Cursor Position at (" << xpos << " : " << ypos << endl;
	}
}

void mouse_position_callback(GLFWwindow* window, double _x, double _y)
{
	//cout << "Mouse move (" << _x << " : " << _y << endl;
	mouse_x = _x;
	mouse_y = SCR_HEIGHT-_y;
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

	work_text += (char)inputed_c;
}

