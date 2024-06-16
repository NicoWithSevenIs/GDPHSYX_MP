#pragma once

#include "../Components/Shader.hpp"
#include "../Components/ShaderNames.hpp"

#include <unordered_map>
#include <string>
namespace managers {


	class ShaderManager {

		private:
			std::unordered_map<std::string, Shader*> shaders;

		public:
			//static Shader* getShader(std::string name);
			static void buildShaders();
			Shader* operator[](std::string name);


		#pragma region singleton

			private:
				static ShaderManager* instance;

			public:
				static ShaderManager* getInstance();
				
			private:
				ShaderManager();
				ShaderManager(const ShaderManager&);
				ShaderManager& operator = (const ShaderManager&);

		#pragma endregion
		
	};


}

