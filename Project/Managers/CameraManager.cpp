#include "CameraManager.hpp"

using namespace managers;


Camera* CameraManager::getCamera() {
	return getInstance()->currentCamera;
}

CameraManager* CameraManager::instance = nullptr;

CameraManager* CameraManager::getInstance() {
	if (!instance) 
		instance = new CameraManager();
	return instance;
}

CameraManager::CameraManager() {
	this->ortho = OrthographicCamera(Vector3(-350,-350,200), Vector3(0,0,-1));
	this->currentCamera = &this->ortho;
}


CameraManager::CameraManager(const CameraManager&){}