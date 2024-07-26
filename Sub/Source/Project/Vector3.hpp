#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>
#include <string>


class Vector3 {

	
	public:
		float x,y,z;

		static const Vector3 zero;
		static const Vector3 one;

		static const Vector3 up;
		static const Vector3 down;

		static const Vector3 left;
		static const Vector3 right;

		static const Vector3 back;
		static const Vector3 front;


	public:
		Vector3(): x(0), y(0), z(0){}
		Vector3(const float x, const  float y, const float z): x(x), y(y), z(z){}
		Vector3(const glm::vec3& vec): x(vec.x), y(vec.y), z(vec.z){}


	public:
		static Vector3 Normalized(const Vector3 v);
		static float Distance(const Vector3 a, const Vector3 b);

		static float Dot(const Vector3 a, const Vector3 b);
		static Vector3 Cross(const Vector3 a, const Vector3 b);
		static Vector3 Component(const Vector3 a, const Vector3 b);

		//static float Angle(const Vector3 a, const Vector3 b);
		static Vector3 Min(const Vector3 a, const Vector3 b);
		static Vector3 Max(const Vector3 a, const Vector3 b);

		static Vector3 Abs(const Vector3 v);
		static std::string to_string(const Vector3 v);

		static Vector3 Lerp(const float t, const Vector3 start, const Vector3 end);

	public:
		explicit operator glm::vec3() const{
			return glm::vec3(x,y,z);
		}

		inline Vector3 operator + (const Vector3& other) const {
			return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
		}

		inline Vector3 operator - (const Vector3& other) const {
			return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
		}

		inline void operator += (const Vector3 other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
		}

		inline void operator -= (const Vector3 other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
		}

		//Scalar Multiplication
		inline friend Vector3 operator * (const float scalar, const Vector3& v)  {
			return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
		}

		inline friend Vector3 operator * (const Vector3& v, const float scalar) {
			return scalar * v;
		}


		inline void operator *= (const float scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		}

		inline Vector3 operator / (const float scalar) const {
			return Vector3((*this)) * (1/scalar);
		}

		inline void operator /= (const float scalar) {
			*this *= 1 / scalar;
		}


		//negation
		inline Vector3 operator -() {
			return Vector3((*this)) * -1;
		}

		//equality
		inline bool operator == (const Vector3& other) const {
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}

		inline bool operator != (const Vector3& other) const {
			return !((*this) == other);
		}


		float Magnitude() const;
		float SquareMagnitude() const;
		void Normalize();	

		//printing
		friend std::ostream& operator << (std::ostream& os, const Vector3& v);



};
