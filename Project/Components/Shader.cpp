#include "Shader.hpp"


Shader::Shader(): shader(0), dir("") {}

Shader::Shader(std::string dir): shader(0), dir(dir){}

std::string Shader::getBuffStr(std::string dir) {
    std::fstream src(dir);

    std::stringstream buff;
    buff << src.rdbuf();
    //std::cout << buff.str() << std::endl;

    return buff.str();
}

void Shader::buildShader() {

    if (this->dir.empty()) {
        std::cout << "[Error] Directory is Empty" << std::endl;
        return;
    }
       
    std::string vStr = this->getBuffStr(this->dir + ".vert");
    std::string fStr = this->getBuffStr(this->dir + ".frag");

    const char* v = vStr.c_str();
    const char* f = fStr.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    this->shader = glCreateProgram();
    glAttachShader(this->shader, vertexShader);
    glAttachShader(this->shader, fragShader);

    glLinkProgram(this->shader);

}

GLuint Shader::getShaderProg() {
    return this->shader;
}