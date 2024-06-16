#pragma once


#include "../Camera/OrthographicCamera.hpp"

namespace managers {

	class CameraManager {
		
		private:
			OrthographicCamera ortho;

		private:
			Camera* currentCamera;

		public:
			static Camera* getCamera();
			//static void switchCamera();


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
