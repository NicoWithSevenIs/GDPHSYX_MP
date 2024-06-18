#pragma once


#include "../Camera/OrthographicCamera.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../../config.hpp"
#include <vector>
namespace managers {

	class CameraManager {
		
		private:
			OrthographicCamera ortho;
			PerspectiveCamera persp;

			std::vector<Camera*> cameras;

		private:
			Camera* currentCamera;

		public:
			static Camera* getMain();
			//static void switchCamera();
			static void initializeCameras(Shader* shader);

			static void switchToOrtho();
			static void switchToPerspective();

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
