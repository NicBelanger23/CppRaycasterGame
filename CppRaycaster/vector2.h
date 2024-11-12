#pragma once
#include <math.h>
class vector2
{
public:
	float X;
	float Y;
	vector2() {X = 0; Y = 0;};
	vector2(float x, float y) {
		X = x; Y = y;
	};

	static vector2 zero() { return vector2(0, 0); }
	static vector2 one() { return vector2(1, 1); }

	vector2& operator*=(const float& coefficent) {
		X *= coefficent;
		Y *= coefficent;
		return *this;
	};

	// Overload the * operator
	vector2 operator*(const float& coefficent) const {
		return vector2(X * coefficent, Y * coefficent);
	};

	vector2 operator+(const vector2& other) const {
		return vector2(X + other.X, Y + other.Y);
	};

	vector2 operator-(const vector2& other) const {
		return vector2(X - other.X, Y - other.Y);
	};

	vector2& operator+=(const vector2& other) {
		X += other.X;
		Y += other.Y;
		return *this;
	};
	vector2& operator-=(const vector2& other) {
		X -= other.X;
		Y -= other.Y;
		return *this;
	};

	float sqrmagnitude() { //easier to compute than the magnitude
		return (X * X) + (Y * Y);
	};

	float magnitude() {
		return pow(sqrmagnitude(), 0.5);
	};

	void Copy(float x, float y) {
		X = x; Y = y;
	};

	void Copy(const vector2& other) {
		X = other.X; Y = other.Y;
	};

	vector2 normalize() {
		
		float m = magnitude();
		if (m == 0) { return vector2::one(); }
		return vector2(X / m, Y / m);
	};

	float dot(vector2 v) {
		return X * v.X + Y * v.Y;
	};

	float cross(vector2 v) {
		return X * v.Y - Y * v.X;
	};

	double signedAngle(vector2 v) {
		// atan2(sinTheta, cosTheta)
		double angle = atan2(cross(v), dot(v));
		return angle; // Angle is in radians
	}
};

