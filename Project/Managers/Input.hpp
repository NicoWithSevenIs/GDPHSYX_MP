#pragma once

#include <functional>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


struct Key_Event {
	int invoke_type;
	std::function<void()> function;
};

class KeyData {

private:
	std::vector<std::function<void()>> onPress;
	std::vector<std::function<void()>> onRelease;

public:
	inline void invoke(int invoke_type) { for (auto i : invoke_type == GLFW_PRESS ? onPress : onRelease) i(); }

	inline void operator += (const Key_Event& action) {
		std::vector<std::function<void()>>* event = action.invoke_type == GLFW_PRESS ? &onPress : &onRelease;
		event->push_back(action.function);
	}
	/*
	inline void operator -= (const Key_Event& action) {
	}
	*/
};


class Input
{

	private:
		std::unordered_map<int, KeyData> key_list;
		std::vector<std::function<void(float, float)>> mouse_callbacks;

	public:
		KeyData& operator [](int key) {
			return this->key_list[key];
		}

		inline void operator += (std::function<void(float, float)> callback){
			mouse_callbacks.push_back(callback);
		}
		
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double xPos, double yPos);


	#pragma region Singleton
	private:
		static Input* instance;

	private:
		Input();
		Input(const Input&);
		Input& operator=(const Input&);

	public:
		static Input* getInstance();

		//static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	#pragma endregion

};

