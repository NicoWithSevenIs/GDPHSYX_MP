#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader {

	private:
		GLuint shader;
		std::string dir;

	public:
		Shader();
		Shader(std::string dir);

	private:
		std::string getBuffStr(std::string dir);

	public:
		void buildShader();
		GLuint getShaderProg();

};