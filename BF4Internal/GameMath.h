#pragma once
#include <iostream>
#include <algorithm>
/* This header contains all the utilities for managing math
*/
namespace _Math {

	


	class Vector2 {
	public:
		float x, y;

	public:
		Vector2();
		Vector2(float x, float y);
		inline Vector2 operator+(const Vector2& other);
		inline Vector2 operator-(const Vector2& other);
		inline Vector2 operator*(const Vector2& other);
		inline Vector2 operator*(const float other);
		inline Vector2 operator/(const Vector2& other);
		virtual void Normalize();
		virtual float Magnitude();
		float Distance(Vector2 to);
	};



	class Vector3  {
	public:
		float x,y,z;

	public:
		Vector3();
		Vector3(float x, float y, float z);
		inline Vector3 operator+(const Vector3& other);
		inline Vector3 operator-(const Vector3& other);
		inline Vector3 operator*(const Vector3& other);
		inline Vector3 operator/(const Vector3& other);
		void Normalize() ;
		float Magnitude() ;
		float Distance(Vector3 to);
	};



	class Vector4  {
	public:
		float x,y,z,w;

	public:
		Vector4();
		Vector4(float x, float y, float z, float w);
		inline Vector4 operator+(const Vector4& other);
		inline Vector4 operator-(const Vector4& other);
		inline Vector4 operator*(const Vector4& other);
		inline Vector4 operator/(const Vector4& other);
		void Normalize();
		float Magnitude();
		float Distance(Vector4 to);
	};


	class Angles{
	public:
		float pitch,yaw, roll;
	public:
		Angles();
		Angles(float yaw, float pitch, float roll);
		inline Angles operator+(const Angles& other);
		inline Angles operator-(const Angles& other);
		void ToRadians();
		void ToDegrees();
		bool isValid();
	};

	Vector2 Lerp(Vector2 from, Vector2 to, float t);
	Vector2 QuadraticBezier(Vector2 from, Vector2 to, Vector2 offset, float t);
	typedef float Matrix4x4[4][4];
	float ToRadians(float Degrees);
	float ToDegrees(float Radians);
	void Normalize(Vector3 in, Vector3& out);
	float Get3DDistance(Vector3 from, Vector3 to);
	float DotProduct(Vector3 first, Vector3 second);
}