#include "CameraManager.hpp"

using namespace managers;

Camera* CameraManager::getMain() {
	return getInstance()->currentCamera;
}

void CameraManager::initializeCameras(Shader* shader) {

	CameraManager* i = getInstance();

	i->ortho = OrthographicCamera(Vector3(-350,-350,200), Vector3(0,0,-1));
	i->ortho.setOrthoData(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	i->cameras.push_back(&i->ortho);


	for (auto i : i->cameras) {
		i->assignShader(shader);
	}

	i->currentCamera = &i->ortho;
}


#pragma region Singleton

CameraManager* CameraManager::instance = nullptr;

CameraManager* CameraManager::getInstance() {
	if (!instance) 
		instance = new CameraManager();
	return instance;
}

CameraManager::CameraManager() {}


CameraManager::CameraManager(const CameraManager&){}

#pragma endregion