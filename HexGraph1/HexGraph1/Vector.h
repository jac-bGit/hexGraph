#pragma once
struct Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	bool operator==(const Vector3 other) {
		return x == other.x && y == other.y && z == other.z;
	}

	Vector3 operator+(const Vector3 other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
};