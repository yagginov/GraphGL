#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image_write.h"
#include "clipboard.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "algorithm"

#include "camera.h"
#include "vector_line.h"
#include "vector_circle.h"
#include "create_window.h"
#include "transparent_square.h"

#include "graph_lib/graph.h"

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
	glm::vec3 last_mouse_pos;

	glm::vec3 copy_point;
	std::string copy_info;

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

	void create_copy_info();
	void paste_graph();

	void save_file(std::string filename);
	void save_selected_to_image();

	void scroll_processing(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

static void clearError();
static void getError(std::string line);