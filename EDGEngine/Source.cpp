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

#include <iostream>
#include <list>   
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
int SCR_WIDTH = 640;
int SCR_HEIGHT = 640;

unsigned int texture1, texture2;
int width, height, nrChannels;
unsigned char* data1;
unsigned char* data2;

glm::mat4 transform;

Shader * ourShader;

Batcher * batch;
Batcher* batch2;

ECamera* camera;

short tilemap[100][100];
int available_tile[20];
int final_available_tile[20];
int tile_array_index = 0;

bool draw_tile_info = false;

int main()
{
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

				if (target_tile >= 0) { available_tile[target_tile] = -1; }
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
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	data1 = stbi_load("data/tile03.png", &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data1);
	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data2 = stbi_load("data/tile_info.png", &width, &height, &nrChannels, STBI_rgb_alpha);

	if (data2)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data2);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->use();

	//ourShader->setInt("texture2", 1);
	glfwSwapInterval(1);
	

	// render loop
	// -----------

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	batch = new Batcher();
	batch2 = new Batcher();
	camera = new ECamera();

	camera->x = 0.0f;
	camera->y = 0.0f;
	//camera->zoom = 1;


	for (int i = 0; i < 30; i++)
	for (int j = 0; j < 30; j++)
	{
		int tile_y = (int)(tilemap[j][i] / 4);
		int tile_x = tilemap[j][i] - tile_y * 4;


		batch->draw_rect_without_color(0.1f * j, 0.1f * i, 0.05f, 0.05f, tile_x, tile_y);
		batch2->draw_rect_without_color(0.1f* j, 0.1f* i, 0.05f, 0.05f, tile_x, tile_y);
	}

	for (int i = 0; i < 900; i++)
	{
		batch->fill_indices();
		batch2->fill_indices();
	}

	batch->init();
	batch2->init();

	while (!glfwWindowShouldClose(window))
	{
		camera->update();
		transform = glm::scale(transform, glm::vec3((SCR_HEIGHT * 1.0f) / SCR_WIDTH, 1, 1));
		// input
		// -----


		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		//if (rand() % 10 <= 5)
		//{

		//}
		//else
		//{
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, texture2);
		//}


		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		// create transformations
		transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		transform = glm::translate(transform, glm::vec3(camera->x, camera->y, 0.0f));
		transform = glm::scale(transform, glm::vec3((SCR_HEIGHT * 1.0f) / SCR_WIDTH * camera->zoom, camera->zoom, 1));


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

		if (!draw_tile_info)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			ourShader->setInt("texture1", 0);
		}
		else
		{

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			ourShader->setInt("texture1", 1);
		}

		batch->draw_call();
		
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}	

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera->speed_x += 0.0001f; }
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera->speed_x -= 0.0001f; }

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera->speed_y -= 0.0001f; }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera->speed_y += 0.0001f; }

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

	std::cout << "Resize event" << std::endl;

	glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
	
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