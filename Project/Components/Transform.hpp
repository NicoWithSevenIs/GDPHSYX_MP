#pragma once

#include "../Vector3.hpp"

class Transform {

	public:
		Vector3 translation;
		Vector3 scale;

	public:
		Transform(Vector3 translation = Vector3::zero, Vector3 scale = Vector3::one);

	public:
		void Translate(Vector3 direction);
		void Scale(float scale);

};