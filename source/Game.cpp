#include "Game.h"

unsigned int SCR_WIDTH = 1500;
unsigned int SCR_HEIGHT = 800;


/*
    Basic class constructor
*/
Game::Game() :
    window(createWindow(SCR_WIDTH, SCR_HEIGHT)),
    _circles(), _edges(),
    _camera(-7.0f, 7.0f, -7.0f, 7.0f, 1500.0f / 800.0f, glm::vec3(0.0f, 0.0f, -3.0f)),
    _tr_square(), first_point(0.0f, 0.0f, 0.0f),
    graph(UNORDERED_LINK)
{
    glfwSetWindowUserPointer(window, this);

    //// init callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //// Set a poligonal mode rendering
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}


/*
    In this constructor, we first load 
    the graph from a specially formatted file.
*/
Game::Game(std::string filename):
    window(createWindow(SCR_WIDTH, SCR_HEIGHT)),
    _circles(), _edges(),
    _camera(-7.0f, 7.0f, -7.0f, 7.0f, 1500.0f / 800.0f, glm::vec3(0.0f, 0.0f, -3.0f)),
    _tr_square(), first_point(0.0f, 0.0f, 0.0f),
    graph(UNORDERED_LINK)
{
    std::string line;
    glm::vec2 num;
    glm::ivec2 i_num;
    std::ifstream myfile(filename);
    if (myfile.is_open())
    {
        if (getline(myfile, line))
        {
            std::stringstream test_ss(line);
            while (test_ss >> num.x, test_ss >> num.y)
            {
                _circles.add_circle(glm::vec3(num, 0.0f));
                graph.add_node(_circles.size());
            }
        }

        if (getline(myfile, line))
        {
            std::stringstream test_ss(line);
            while (test_ss >> i_num.x, test_ss >> i_num.y)
            {
                add_edge(i_num.x, i_num.y);
            }
        }

    }
    else std::cout << "Unable to open file\n";

    glfwSetWindowUserPointer(window, this);

    //// init callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //// Set a poligonal mode rendering
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

/*
    The main method of the class that we call 
    from the outside and it controls the rendering cycle.
*/
void Game::play()
{
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);

        //// Render here ----------------------------------------------------
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw((float)SCR_WIDTH / (float)SCR_HEIGHT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    graph.compile_adj();
    graph.compile_table();

    graph.search_all_lengths();

    graph.save_lengths_table("testfiles/lengths_table.txt");
    graph.save_adjacency_matrix("testfiles/adjacency_matrix.txt");
}

/*
    This method draws the entire graph on the screen.
*/
void Game::draw(float aspect)
{
    _camera.set_aspect(aspect);
    glm::mat4 projection = _camera.get_projection_matrix();

    glm::mat4 view = _camera.get_view_matrix();

    _edges.draw(projection, view);

    _circles.draw(projection, view);

    _tr_square.draw(projection, view);

    glBindVertexArray(0);
}

/*
    This method moves individual selected parts of the graph.
*/
void Game::move(int index, glm::vec3 pos, glm::vec3 w_size)
{
    pos = _camera.get_mouse_positions(pos, w_size);
    glm::vec3 dir = pos - first_point;

    for (const auto& it : selection_set)
    {
        _circles[it].set_pos(dir);
        glm::vec3 new_pos = _circles[it].get_pos();

        for (const auto& jt : _circles[it].edgesA)
        {
            _edges[jt].set_posA(new_pos);
        }

        for (const auto& jt : _circles[it].edgesB)
        {
            _edges[jt].set_posB(new_pos);
        }
    }
}

/*
    The following methods add additional vertices and edges to 
    the graph, respectively. Also, in addition to adding visual 
    vertices and edges, they create corresponding vertices and 
    edges in the graph class, for further analysis of the graph.
*/
void Game::add_circle(glm::vec3 pos, glm::vec3 w_size)
{
    pos = _camera.get_mouse_positions(pos, w_size);
    _circles.add_circle(pos);
    graph.add_node(std::stoi(_circles[_circles.size() - 1].get_name()));
}
void Game::add_edge(int posA, int posB)
{
    _edges.add_line(_circles[posA].get_pos(), _circles[posB].get_pos());
    _circles[posA].edgesA.insert(_edges.size() - 1);
    _circles[posB].edgesB.insert(_edges.size() - 1);

    _edges[_edges.size() - 1].set_rel(glm::ivec2(posA, posB));

    graph.add_link({(UINT)(posA + 1), (UINT)(posB + 1), 1.0f});
}

/*
    This method checks whether we have clicked on any of 
    the vertices and if so, returns the index of this vertex.
*/
int Game::check_mouse_colision(glm::vec3 pos, glm::vec3 w_size)
{
    pos = _camera.get_mouse_positions(pos, w_size);

    for (int i = 0; i < _circles.size(); ++i)
    {
        if (_circles[i].check_hit(pos))
        {
            _circles[i].set_first_point();

            first_point = pos;

            if (!selection_set.count(i) && _tr_square.get_access())
            {
                selection_set.clear();
                _tr_square.set_select(false);

                _circles.reset_color(selection_set);
                _circles[i].set_color(glm::vec3(1.0f, 0.0f, 0.2f));
                selection_set.insert(i);
                return i;
            }
            for (const auto& it : selection_set)
            {
                _circles[it].set_first_point();
            }
            return i;
        }
    }

    _tr_square.set_select(false);
    _tr_square.set_posA(pos);
    return -1;
}

/*
    The method forms a set of vertices that we 
    selected using a semi-transparent rectangle.
*/
void Game::update_selection_set()
{
    if (_tr_square.get_select())
    {
        return;
    }

    _circles.reset_color(selection_set);
    selection_set.clear();

    glm::vec4 borders = _tr_square.get_borders();
    borders += glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);

    for (int i = 0; i < _circles.size(); ++i)
    {
        glm::vec3 pos = _circles[i].get_pos();

        if ((pos.y < borders.z && pos.y > borders.w) &&
            (pos.x < borders.y && pos.x > borders.x))
        {
            _circles[i].set_first_point();
            _circles[i].set_color(glm::vec3(0.0f, 1.0f, 0.2f));
            selection_set.insert(i);
        }
    }
}


/*
    The method saves the drawn graph in a special formatted file, 
    from which we can then immediately restore the graph.
*/
void Game::save_file(std::string filename)
{
    std::ofstream myfile(filename);
    if (myfile.is_open())
    {
        for (auto& it : _circles)
        {
            myfile << it.get_pos().x  << " " << it.get_pos().y << " ";
        }
        myfile << "\n";
        for (auto& it : _edges)
        {
            myfile << it.get_rel().x << " " << it.get_rel().y << " ";
        }
        myfile << "\n";
        myfile.close();
    }
}

/*
    The method renders the selected vertices and 
    edges that fell into the selection into a separate 
    framebuffer from which we then read each pixel 
    and save it all in a .png image.
*/
void Game::save_selected_to_image()
{
    glm::vec4 a(INFINITY, -INFINITY, -INFINITY, INFINITY);

    for (const auto& it : selection_set)
    {
        glm::vec3 pos = _circles[it].get_pos();
        a.x = std::min(a.x, pos.x);
        a.y = std::max(a.y, pos.x);
        a.z = std::max(a.z, pos.y);
        a.w = std::min(a.w, pos.y);
    }

    a += glm::vec4(-1.0f, 1.0f, 1.0f, -1.0f);

    int width, height;
    width = (a.y - a.x) * 200;
    height = (a.z - a.w) * 200;


    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glViewport(0, 0, width, height);

    unsigned int texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    Camera copy_cam(a.x, a.y, a.w, a.z, 1.0f, glm::vec3(0.0f, 0.0f, -3.0f));

    std::set<int> test_s;
    std::set<int> selection_line_set;
    for (auto& it : selection_set)
    {
        _circles[it].reset_color();
        for (const auto& jt : _circles[it].edgesA)
        {
            if (test_s.count(jt))
            {
                selection_line_set.insert(jt);
            }
            else
            {
                test_s.insert(jt);
            }
        }

        for (const auto& jt : _circles[it].edgesB)
        {
            if (test_s.count(jt))
            {
                selection_line_set.insert(jt);
            }
            else
            {
                test_s.insert(jt);
            }
        }
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 projection = copy_cam.get_projection_matrix();

    glm::mat4 view = copy_cam.get_view_matrix();

    _edges.draw(projection, view, selection_line_set);
    _circles.draw(projection, view, selection_set);

    glBindVertexArray(0);

    for (auto& it : selection_set)
    {
        _circles[it].set_color(glm::vec3(1.0f, 0.0f, 0.5f));
    }

    char* buffer = new char[width * height * 4];
    glReadPixels(0, 0, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);

    stbi_flip_vertically_on_write(true);
    std::string filename_png = "testfiles/output_" + std::to_string(width) + "-" + std::to_string(height) + ".png";

    stbi_write_png(filename_png.c_str(), width, height, 4, buffer, width * 4);
    std::cout << "recording the image to the file is finished\n";

    delete[] buffer;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteFramebuffers(1, &fbo);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}


/*
    A method for handling the mouse scroll event.
*/
void Game::scroll_processing(GLFWwindow* window, double xoffset, double yoffset)
{
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    _camera.procces_mouse_scroll(glm::vec3((float)mouseX, -(float)mouseY, 0.0f),
        glm::vec3((float)width, -(float)height, 0.0f), yoffset);
}

/*
    Handling various input events.
*/
void Game::processInput(GLFWwindow* window)
{
    static bool mouse_pressed = false;
    static bool draw_circle_access = true;
    static bool draw_line_access = false;
    static bool key_1_pressed = false;
    static bool key_2_pressed = false;
    static bool key_3_pressed = false;
    static bool key_S_pressed = false;
    static bool hit_access = false;
    static bool first_click = true;
    static bool select = false;

    static int captured = -1;
    static int posA = -1;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !key_1_pressed)
    {
        draw_circle_access = true;

        _circles.reset_color(selection_set);
        selection_set.clear();

        _tr_square.set_access(false);

        hit_access = false;
        draw_line_access = false;
        key_1_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE && key_1_pressed)
    {
        key_1_pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !key_2_pressed)
    {
        draw_line_access = true;

        _circles.reset_color(selection_set);
        selection_set.clear();
        _tr_square.set_access(false);

        hit_access = false;
        draw_circle_access = false;
        key_2_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE && key_2_pressed)
    {
        key_2_pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !key_3_pressed)
    {
        hit_access = true;

        _circles.reset_color(selection_set);
        selection_set.clear();
        _tr_square.set_access(true);

        draw_line_access = false;
        draw_circle_access = false;
        key_3_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE && key_3_pressed)
    {
        key_3_pressed = false;
    }


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_pressed && draw_circle_access)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        this->add_circle(glm::vec3((float)mouseX, (float)mouseY, 0.0f),
            glm::vec3((float)SCR_WIDTH, (float)(SCR_HEIGHT), 0.0f));
        mouse_pressed = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_pressed && draw_line_access)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        int pos = this->check_mouse_colision(glm::vec3((float)mouseX, (float)mouseY, 0.0f),
            glm::vec3((float)SCR_WIDTH, (float)(SCR_HEIGHT), 0.0f));
        if (pos != -1)
        {
            selection_set.insert(pos);
            _circles[pos].set_color(glm::vec3(1.0f, 0.0f, 0.0f));

            if (selection_set.size() == 2)
            {
                this->add_edge(posA, pos);
                _circles.reset_color(selection_set);
                selection_set.clear();
            }
            posA = pos;
        }

        
        mouse_pressed = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_pressed && hit_access)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);


        captured = this->check_mouse_colision(glm::vec3((float)mouseX, (float)mouseY, 0.0f),
            glm::vec3((float)SCR_WIDTH, (float)(SCR_HEIGHT), 0.0f));

        mouse_pressed = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && mouse_pressed)
    {
        mouse_pressed = false;
        captured = -1;

        if (!_tr_square.get_select() && hit_access)
        {
            update_selection_set();
            _tr_square.set_posA(glm::vec2(0.0f));
            _tr_square.set_posB(glm::vec2(0.0f));
            _tr_square.set_select(true);
        }
    }

    if (captured != -1)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        this->move(captured, glm::vec3((float)mouseX, (float)mouseY, 0.0f),
            glm::vec3((float)SCR_WIDTH, (float)(SCR_HEIGHT), 0.0f));
    }
    
    if (captured == -1 && mouse_pressed && hit_access)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        _tr_square.set_posB(_camera.get_mouse_positions(glm::vec3((float)mouseX, (float)mouseY, 0.0f),
            glm::vec3((float)SCR_WIDTH, (float)(SCR_HEIGHT), 0.0f)));
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !key_S_pressed)
        {
            key_S_pressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && key_S_pressed)
        {
            save_selected_to_image();
            key_S_pressed = false;
        }
    }
}


/*
    A callback method to handle the window resize event. 
    Resizes the framebuffer relative to the window size.
*/
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

/*
    A callback method to handle the scroll event. 
    Calls another method of the main class object (Game),
    which then changes the coordinates of the workspace.
*/
void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Game* graph = static_cast<Game*>(glfwGetWindowUserPointer(window));

    graph->scroll_processing(window, xoffset, yoffset);
}


/*
    Function to check errors from opengl functions.
*/
static void clearError() {
    while (glGetError());
}
static void getError(std::string line) {
    while (unsigned int error = glGetError()) {
        std::cout << "Error in line: " << line << ". Error number: (0x" << std::hex << error << ")\n";
    }
}