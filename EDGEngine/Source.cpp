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
#include "Helper.h"

using namespace std;

//Helper helper_object;
float Helper::correction_x = 0;
float Helper::correction_y = 0;



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void recalculate_correction();
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//void load_texture();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void load_texture(const char* _path, int _id);

// settings
int SCR_WIDTH = 640;
int SCR_HEIGHT = 640;

unsigned int texture[32];
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

string work_text;

int main()
{
	recalculate_correction();
	setlocale(LC_ALL, ".1251"); // для ввода; 

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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
	load_texture("data/tile03.png",0);
	load_texture("data/tile_info.png", 1);
	load_texture("data/font_arial.png", 2);
	// texture 2
	// ---------
	

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->use();

	//ourShader->setInt("texture2", 1);
	glfwSwapInterval(0);
	

	// render loop
	// -----------

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

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

	for (int i = 0; i < 900; i++)
	{
		batch->fill_indices();
		batch2->fill_indices();
		font_batch->fill_indices();
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

		transform = glm::translate(transform, glm::vec3(camera->x, camera->y, 0.0f));
		transform = glm::scale(transform, glm::vec3(camera->zoom*Helper::correction_x, camera->zoom * Helper::correction_y, 1));


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

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		ourShader->setInt("texture1", 2);

		font_batch->reset();
		font->x_adding = 0;
		batch->setcolor_255(255, 255, 255, 100); font->draw(font_batch, "Ну наконец то эта ", 0, 0);
		batch->setcolor_255(255, 0, 0, 100); font->draw(font_batch, "срань ", 0, 0);
		batch->setcolor_255(255, 255, 255, 100); font->draw(font_batch, "заработала!", 0, 0);
		font_batch->reinit();


		font_batch->draw_call();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
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
	glGenTextures(_id, &texture[_id]);
	glBindTexture(GL_TEXTURE_2D, texture[_id]);
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

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera->speed_x += 100.0f * delta_time*Helper::correction_x; }
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera->speed_x -= 100.0f * delta_time * Helper::correction_x; }

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera->speed_y -= 100.0f * delta_time * Helper::correction_y; }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera->speed_y += 100.0f * delta_time * Helper::correction_y; }

	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) { camera->zoom = 1.0f; }

	draw_tile_info = false;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) { draw_tile_info = true; }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{//
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	


	glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);

	std::cout << "Resize event width:" << width << " height: " << height << std::endl;

	recalculate_correction();
	
}

void recalculate_correction()
{
	Helper::correction_x = 1.0 / SCR_WIDTH * 2.0;
	Helper::correction_y = 1.0 / SCR_HEIGHT * 2.0;

	std::cout << "helper correction_x: " << Helper::correction_x << " correction_y: " << Helper::correction_y << std::endl;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
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

