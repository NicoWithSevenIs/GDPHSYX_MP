#include "Input.hpp"

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(*getInstance())[key].invoke(action);
}

void Input::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	for (auto i : getInstance()->mouse_callbacks) 
		i(xPos,yPos);	
}

template<typename T>
T Input::getLine(std::string message)
{
	T value;
	std::string line;

	std::cout << message << ": ";
	std::getline(std::cin, line);

	std::istringstream stream(line);

	stream >> value;

	return value;
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
