#include "Vector3.hpp"

const Vector3 Vector3::zero = Vector3();
const Vector3 Vector3::one = Vector3(1, 1, 1);

const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);

const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::right = Vector3(1, 0, 0);

const Vector3 Vector3::front = Vector3(0, 0, 1);
const Vector3 Vector3::back = Vector3(0, 0, -1);

float Vector3::Magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

float Vector3::SquareMagnitude() const
{
	return x * x + y * y + z * z;
}

void Vector3::Normalize() {
	(*this) *= 1/this->Magnitude();
}

std::ostream& operator << (std::ostream& os, const Vector3& v){
	os << "{" << v.x << "," << v.y << "," << v.z << "}";
	return os;
}


Vector3 Vector3::Normalized(const Vector3 v){
	Vector3 to_normalize(v);
	to_normalize.Normalize();
	return to_normalize;
}

float Vector3::Distance(const Vector3 a, const Vector3 b) {
	float x = b.x - a.x;
	float y = b.y - a.y;
	float z = b.z - a.z;

	return sqrt(x * x + y * y + z * z);
}
 
float Vector3::Dot(const Vector3 a, const Vector3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(const Vector3 a, const Vector3 b){
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

Vector3 Vector3::Component(const Vector3 a, const Vector3 b){
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 Vector3::Min(const Vector3 a, const Vector3 b){
	return a.Magnitude() < b.Magnitude() ? a : b;
}

Vector3 Vector3::Max(const Vector3 a, const Vector3 b){
	return a.Magnitude() > b.Magnitude() ? a : b;
}

Vector3 Vector3::Abs(const Vector3 v){
	return Vector3(abs(v.x), abs(v.y), abs(v.z));
}

std::string Vector3::to_string(const Vector3 v){
	return "{" + std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z) + "}";
}

Vector3 Vector3::Lerp(const float t, const Vector3 start, const Vector3 end){
	return start + (end - start) * t;
}
