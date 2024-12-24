#include "input_handler.h"

InputHandler::InputHandler() {}

InputHandler::~InputHandler()
{
    _actions.clear();

    delete _instance;
}

InputHandler* InputHandler::get_singleton() 
{
    if (_instance == nullptr) 
    {
        _instance = new InputHandler();
    }
    return _instance;
}

void InputHandler::add_action(int key) 
{
    _actions[key] = InputAction(key);
}

void InputHandler::update(GLFWwindow* window) 
{
    for (auto& action : _actions) 
    {
        action.second.update(window);
    }
}

InputAction* InputHandler::get_action(int key) 
{
    if (_actions.find(key) != _actions.end()) 
    {
        return &_actions[key];
    }
    return nullptr;
}