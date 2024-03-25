#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image_write.h"
#include "Clipboard.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "algorithm"

#include "Camera.h"
#include "VectorLine.h"
#include "VectorCircle.h"
#include "CreateWindow.h"
#include "TransparentSquareRenderer.h"

#include <Graph.h>

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

class Game
{
private:
	GLFWwindow* window;

	Camera _camera;
	TransparentSquareRenderer _tr_square;
	std::set<int> selection_set;

	VectorCircle _circles;
	VectorLine _edges;
	
	graph::Graph graph;

	glm::vec3 first_point;

public:
	Game();
	Game(std::string filename);

	void play();
	void draw(float aspect);
	void move(int index, glm::vec3 pos, glm::vec3 w_size);

	void add_circle(glm::vec3 pos, glm::vec3 w_size);
	void add_edge(int posA, int posB);

	int check_mouse_colision(glm::vec3 pos, glm::vec3 w_size);
	void update_selection_set();

	void save_file(std::string filename);
	void save_selected_to_image();

	void scroll_processing(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

static void clearError();
static void getError(std::string line);