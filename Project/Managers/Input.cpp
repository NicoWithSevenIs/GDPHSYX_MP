#include "Input.hpp"

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(*getInstance())[key].invoke(action);
}

void Input::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	for (auto i : getInstance()->mouse_callbacks) 
		i(xPos,yPos);	
}

void Input::askCableInput(CableCreator* cableCreator) {
	std::cout << "Cable Length: ";
	std::cin >> cableCreator->cableLength;
	std::cout << "Particle Gap: ";
	std::cin >> cableCreator->particleGap;
	std::cout << "Particle Radius: ";
	std::cin >> cableCreator->particleRadius;
	std::cout << "Gravity Strength: ";
	std::cin >> cableCreator->gravityStrength;
	std::cout << "ApplyForce" << std::endl;
	std::cout << "X: ";
	std::cin >> cableCreator->forceToApply.x;
	std::cout << "Y: ";
	std::cin >> cableCreator->forceToApply.y;
	std::cout << "Z: ";
	std::cin >> cableCreator->forceToApply.z;
}


template<typename T>
T Input::getLine(std::string message)
{
	T value;

	std::cout << message << ": ";
	std::cin >> value;

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
