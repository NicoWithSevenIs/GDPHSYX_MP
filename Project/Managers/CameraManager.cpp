#include "CameraManager.hpp"

using namespace managers;

Camera* CameraManager::getMain() {
	return getInstance()->currentCamera;
}

void CameraManager::initializeCameras(Shader* shader) {

	CameraManager* i = getInstance();

	i->ortho = OrthographicCamera(Vector3(-350,-350,200), Vector3::back);
	i->ortho.setOrthoData(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -3.f, 10000.f);
	i->cameras.push_back(&i->ortho);

	i->persp = PerspectiveCamera(Vector3(0, 0, 600), Vector3::back);
	i->cameras.push_back(&i->persp);


	for (auto i : i->cameras) {
		i->assignShader(shader);
	}

	i->currentCamera = &i->ortho;
}


void CameraManager::switchToOrtho() {
	getInstance()->currentCamera = &getInstance()->ortho;
}

void CameraManager::switchToPerspective() {
	getInstance()->currentCamera = &getInstance()->persp;
}

void CameraManager::DoOnAllCameras(std::function<void(Camera*)> callback) {
	for (auto camera : getInstance()->cameras) {
		callback(camera);
	}
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