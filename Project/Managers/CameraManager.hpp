#pragma once


#include "../Camera/OrthographicCamera.hpp"
#include "../../config.hpp"
#include <vector>
namespace managers {

	class CameraManager {
		
		private:
			OrthographicCamera ortho;
			std::vector<Camera*> cameras;

		private:
			Camera* currentCamera;

		public:
			static Camera* getMain();
			//static void switchCamera();
			static void initializeCameras(Shader* shader);

		#pragma region Singleton

		private:
			static CameraManager* instance;

		public:
			static CameraManager* getInstance();

		private:
			CameraManager();
			CameraManager(const CameraManager&);
			CameraManager& operator= (const CameraManager&);


		#pragma endregion 


	};

}
