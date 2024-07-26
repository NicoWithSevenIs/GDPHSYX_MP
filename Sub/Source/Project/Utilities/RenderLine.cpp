#include "RenderLine.hpp"

void RenderLine::Update(Vector3 p1, Vector3 p2, glm::mat4 projection_matrix)
{
	this->p1 = p1;
	this->p2 = p2;
	this->projection_matrix = projection_matrix;
}

void RenderLine::Draw()
{

	glUseProgram(0);

	glm::vec4 d1 = this->projection_matrix * glm::vec4(p1.x, p1.y, p1.z , 1.f);
	glm::vec4 d2 = this->projection_matrix * glm::vec4(p2.x, p2.y, p2.z, 1.f);

	glBegin(GL_LINES);
	glVertex3f(d1.x, d1.y, d1.z);
	glVertex3f(d2.x, d2.y, d2.z);

	glEnd();


	
}
