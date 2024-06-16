#include "ShaderManager.hpp"

using namespace managers;

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::getInstance() {
	if (!instance)
		instance = new ShaderManager();
	return instance;
}

Shader* ShaderManager::operator[](std::string name) {
	auto i = getInstance();
	return i->shaders.find(name) != i->shaders.end() ? i->shaders.at(name) : nullptr;
}

ShaderManager::ShaderManager(const ShaderManager&) {}

ShaderManager::ShaderManager() {
	this->shaders[ShaderNames::MODEL_SHADER] = new Shader("Shaders/shaders");
}


void ShaderManager::buildShaders() {
	for (auto i : getInstance()->shaders)
		i.second->buildShader();
}