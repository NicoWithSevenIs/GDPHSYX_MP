#pragma once


#include "../Camera/OrthographicCamera.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../../config.hpp"
#include <vector>
#include <functional>


//Stores all instances of camera. Only way to retrieve a camera ouside is via getMain()
namespace managers {

	class CameraManager {
		
		private:
			OrthographicCamera ortho;
			PerspectiveCamera persp;


			//all instances of camera should be added here upon instantiation so it could be used by DoOnAllCameras
			std::vector<Camera*> cameras;

		private:
			Camera* currentCamera;

		public:
			static Camera* getMain();

			//sets the shader for all cameras
			static void initializeCameras(Shader* shader);

			//camera switching
			static void switchToOrtho();
			static void switchToPerspective();

			static void DoOnAllCameras(std::function<void(Camera*)> callback);

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
