#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include <GLFW/glfw3.h>

class InputAction 
{
private:
    int _key;
    bool _wasPressed;
    bool _isPressed;

public:
    InputAction();
    InputAction(int key);

    void update(GLFWwindow* window);

    bool is_pressed() const;
    bool is_held() const;
    bool is_released() const;

    int get_key() const;
};

#endif      // INPUT_ACTION_H