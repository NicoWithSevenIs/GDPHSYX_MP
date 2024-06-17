#include "Input.hpp"

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(*getInstance())[key].invoke(action);
}



#pragma region Singleton

Input* Input::instance = NULL;

Input::Input() {}
Input::Input(const Input&){}

Input* Input::getInstance() {
	if (!instance) instance = new Input();
	return instance;
}


#pragma endregion
