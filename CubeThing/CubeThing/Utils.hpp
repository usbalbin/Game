#pragma once

template<typename T>
struct Vector {
	inline Vector(T x, T y) : x(x), y(y) {}
	
	inline Vector operator+(Vector other) {
		return Vector(this->x + other.x, this->y + other.y);
	}

	inline Vector operator-(Vector other) {
		return Vector(this->x - other.x, this->y - other.y);
	}

	inline Vector operator*(Vector other) {
		return Vector(this->x * other.x, this->y * other.y);
	}

	inline Vector operator/(Vector other) {
		return Vector(this->x / other.x, this->y / other.y);
	}

	T x, y;
};