#include "GameMath.h"


using namespace _Math;




float _Math::ToRadians(float Degrees)
{
	return Degrees * 3.14f / 180.0f;
}
void _Math::Normalize(Vector3 in, Vector3& out) {
	float mag = sqrtf(powf(in.x, 2) + powf(in.y, 2) + powf(in.z, 2));
	out.x = in.x / mag;
	out.y = in.y / mag;
	out.z = in.z / mag;
}

float _Math::ToDegrees(float Radians)
{
	return Radians * 180.0f / 3.14f;
}

float _Math::Get3DDistance(Vector3 from, Vector3 to) {
	return sqrtf(powf((to.x - from.x), 2) + powf((to.y - from.y), 2) + powf((to.z - from.z), 2));
}
float _Math::DotProduct(Vector3 first, Vector3 second) {
	return first.x * second.x +
		first.y * second.y +
		first.z * second.z;
}
Vector2 _Math::Lerp(Vector2 from, Vector2 to, float t) {
	return from + (to - from) * t;
}
Vector2 _Math::QuadraticBezier(Vector2 from, Vector2 to, Vector2 offset, float t) {
	return from * powf((1-t),2) + offset * 2 * (1 - t) * t + to* powf(t,2);
}
//Vector2
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

inline Vector2 Vector2::operator+(const Vector2& other) {
	return{ this->x + other.x, this->y + other.y };
}
inline Vector2 Vector2::operator-(const Vector2& other) {
	return{ this->x - other.x, this->y - other.y };
}
inline Vector2 Vector2::operator*(const Vector2& other) {
	return{ this->x * other.x, this->y * other.y };
}
inline Vector2 Vector2::operator*(const float other) {
	return{ this->x * other, this->y * other };
}
inline Vector2 Vector2::operator/(const Vector2& other) {
	return{ this->x / other.x, this->y / other.y };
}

float Vector2::Magnitude() {
	return sqrt(this->x * this->x + this->y * this->y);
}

void Vector2::Normalize() {
	float mag = this->Magnitude();
	this->x /= mag;
	this->y /= mag;
}
float Vector2::Distance(Vector2 to) {
	Vector2 len = *(Vector2*)this - to;
	return len.Magnitude();
}




// Vector3
Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

inline Vector3 Vector3::operator+(const Vector3& other) {
	return{ this->x + other.x, this->y + other.y, this->z + other.z};
}
inline Vector3 Vector3::operator-(const Vector3& other) {
	return{ this->x - other.x, this->y - other.y, this->z -other.z};
}
inline Vector3 Vector3::operator*(const Vector3& other) {
	return{ this->x * other.x, this->y * other.y, this->z * other.z};
}
inline Vector3 Vector3::operator/(const Vector3& other) {
	return{ this->x / other.x, this->y / other.y, this->z / other.z };
}

float Vector3::Magnitude() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
void Vector3::Normalize(){
	float mag = this->Magnitude();
	this->x /= mag;
	this->y /= mag;
	this->z /= mag;
}

float Vector3::Distance(Vector3 to) {
	Vector3 len = *(Vector3*)this - to;
	return len.Magnitude();
}



//Vector4

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

inline Vector4 Vector4::operator+(const Vector4& other) {
	return{ this->x + other.x, this->y + other.y, 
		this->z + other.z, this->w + other.w};
}
inline Vector4 Vector4::operator-(const Vector4& other) {
	return{ this->x - other.x, this->y - other.y, 
		this->z - other.z, this->w - other.w };
}
inline Vector4 Vector4::operator*(const Vector4& other) {
	return{ this->x * other.x, this->y * other.y, 
		this->z * other.z, this->w * other.w};
}
inline Vector4 Vector4::operator/(const Vector4& other) {
	return{ this->x / other.x, this->y / other.y, 
		this->z / other.z, this->w * other.w };
}

float Vector4::Magnitude() {
	return sqrt(this->x * this->x + this->y * this->y +
		this->z * this->z + this->w* this->w);
}
void Vector4::Normalize() {
	float mag = this->Magnitude();
	this->x /= mag;
	this->y /= mag;
	this->z /= mag;
	this->w /= mag;
}

float Vector4::Distance(Vector4 to) {
	Vector4 len = *(Vector4*)this - to;
	return len.Magnitude();
}


Angles::Angles() {
	yaw = pitch = roll = 0;
}

Angles::Angles(float yaw, float pitch, float roll){
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = roll;
}

inline Angles Angles::operator+(const Angles& other) {
	Angles out( yaw + other.yaw, pitch + other.pitch,
		roll + other.roll);
	return out;
}
inline Angles Angles::operator-(const Angles& other) {
	Angles out(yaw - other.yaw, pitch - other.pitch,
		roll - other.roll );
	return out;
}

void Angles::ToRadians() {
	this->pitch = _Math::ToRadians(this->pitch);
	this->yaw = _Math::ToRadians(this->yaw);
	this->roll = _Math::ToRadians(this->roll);
}


void Angles::ToDegrees() {
	this->pitch = _Math::ToDegrees(this->pitch);
	this->yaw = _Math::ToDegrees(this->yaw);
	this->roll = _Math::ToDegrees(this->roll);
}

bool Angles::isValid() {
	if (this->pitch > -99 && this->yaw > -99 && this->roll > -99)
		return false;
	return true;
}
