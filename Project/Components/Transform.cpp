#include "Transform.hpp"

Transform::Transform(Vector3 translation, Vector3 scale): translation(translation), scale(scale){}

void Transform::Translate(Vector3 direction) {
	this->translation += direction;
}
void Transform::Scale(float scale) {
	this->scale *= scale;
}