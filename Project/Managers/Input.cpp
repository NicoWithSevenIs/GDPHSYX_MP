#include "Input.hpp"

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	getInstance()->key_list[key] = action;
}

bool Input::isKeyDown(int key) {
	return getInstance()->key_list[key] == GLFW_PRESS;
}

bool Input::isKeyUp(int key) {
	return getInstance()->key_list[key] == GLFW_RELEASE;
}

bool Input::isKey(int key) {
	return getInstance()->key_list[key] == GLFW_PRESS || getInstance()->key_list[key] == GLFW_REPEAT;
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
