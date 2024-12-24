#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GLFW/glfw3.h>
#include <map>
#include "input_action.h"

// Singleton class
class InputHandler 
{
private:
    std::map<int, InputAction> _actions;

private:
    InputHandler();
    InputHandler* _instance;
    
public:
    InputHandler* get_singleton();

    ~InputHandler();

    void add_action(int key);
    void update(GLFWwindow* window);

    InputAction* get_action(int key);

};

#endif // INPUT_HANDLER_H