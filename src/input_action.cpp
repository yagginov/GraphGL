#include "input_action.h"

InputAction::InputAction()
    : _key(GLFW_KEY_0), _wasPressed(false), _isPressed(false) {}

InputAction::InputAction(int key)
    : _key(key), _wasPressed(false), _isPressed(false) {}

void InputAction::update(GLFWwindow* window) 
{
    _wasPressed = _isPressed;
    _isPressed = glfwGetKey(window, _key) == GLFW_PRESS;
}

bool InputAction::is_pressed() const 
{
    return _isPressed && !_wasPressed;
}

bool InputAction::is_held() const 
{
    return _isPressed && _wasPressed;
}

bool InputAction::is_released() const 
{
    return !_isPressed && _wasPressed;
}

int InputAction::get_key() const
{
    return _key;
}