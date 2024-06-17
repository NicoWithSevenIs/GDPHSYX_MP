#pragma once

#include <functional>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input
{
	
	/**/
	private:
		std::unordered_map<int, int> key_list;

	public:

		static bool isKeyDown(int key);
		static bool isKeyUp(int key);
		static bool isKey(int key);


	#pragma region Singleton
	private:
		static Input* instance;

	private:
		Input();
		Input(const Input&);
		Input& operator=(const Input&);

	public:
		static Input* getInstance();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		//static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	#pragma endregion

};

