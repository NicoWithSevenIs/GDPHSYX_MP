#include "Model.h"


Model::Model(std::string filename) {
	this->objData.LoadModel(filename);
	this->initializeBuffers();
}

Model::~Model() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Model::initializeBuffers() {
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
}

void Model::assignShader(Shader* shader) {
	this->shader = shader;
}

void Model::setColor(Vector3 color) {
	this->color = color;
}

void Model::Draw() {

	if (this->shader == nullptr) {
		std::cout << "[ERROR] No Shaders Attached" << std::endl;
		return;
	}

	glUseProgram(shader->getShaderProg());
		
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(GL_FLOAT) * this->objData.getAttributes().vertices.size(),
		this->objData.getAttributes().vertices.data(),
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		sizeof(GLuint) * this->objData.getMeshIndices().size(),
		this->objData.getMeshIndices().data(),
		GL_STATIC_DRAW
	);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glm::mat4 transformation_matrix = glm::translate(glm::mat4(1.0f), (glm::vec3)this->transform.translation);
	transformation_matrix = glm::scale(transformation_matrix, (glm::vec3)this->transform.scale);

	unsigned int transformLoc = glGetUniformLocation(shader->getShaderProg(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

	unsigned int colorLoc = glGetUniformLocation(shader->getShaderProg(), "color");
	glUniform3fv(colorLoc, 1, glm::value_ptr((glm::vec3)this->color));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->objData.getMeshIndices().size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}
