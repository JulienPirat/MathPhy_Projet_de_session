#include "Vector3D.h"

Vector3D::Vector3D() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(double xVal, double yVal, double zVal) {
	x = xVal;
	y = yVal;
	z = zVal;
}


Vector3D& Vector3D::operator=(const Vector3D& autre) {
	x = autre.x;
	y = autre.y;
	z = autre.z;
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& autre) const {
	return Vector3D(x + autre.x, y + autre.y, z + autre.z);
}

void Vector3D::operator+=(const Vector3D& autre) {
	x = x + autre.x;
	y = y + autre.y;
	z = z + autre.z;
}

Vector3D Vector3D::operator-(const Vector3D& autre) const {
	return Vector3D(x - autre.x, y - autre.y, z - autre.z);
}

void Vector3D::operator-=(const Vector3D& autre) {
	x = x - autre.x;
	y = y - autre.y;
	z = z - autre.z;
}

Vector3D Vector3D::operator*(double scalaire) const {
	return Vector3D(x * scalaire, y * scalaire, z * scalaire);
}

void Vector3D::operator*=(double scalaire) {
	x = x * scalaire;
	y = y * scalaire;
	z = z * scalaire;
}

Vector3D Vector3D::operator*(float scalaire) const
{
	return Vector3D(x * scalaire, y * scalaire, z * scalaire);
}

void Vector3D::operator*=(float scalaire)
{
	x = x * scalaire;
	y = y * scalaire;
	z = z * scalaire;
}

Vector3D Vector3D::operator/(double scalaire) const {
	if (scalaire != 0) {
		return Vector3D(x / scalaire, y / scalaire, z / scalaire);
	}
	std::cout << "ERR : Division par 0 impossible" << std::endl;
	return Vector3D(x, y, z);
}

void Vector3D::operator/=(double scalaire) {
	if(scalaire != 0){
		x = x / scalaire;
		y = y / scalaire;
		z = z / scalaire;
	}
	std::cout << "ERR : Division par 0 impossible" << std::endl;
}

float Vector3D::operator*(const Vector3D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

void Vector3D::afficher() const {
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

double Vector3D::norme() const {
	return std::sqrt(x * x + y * y + z * z);
}

double Vector3D::produitScalaire(const Vector3D& autre) const {
	return x * autre.x + y * autre.y + z * autre.z;
}

Vector3D Vector3D::produitVectoriel(const Vector3D& autre) const {
	return Vector3D(y * autre.z - z * autre.y, z * autre.x - x * autre.z, x * autre.y - y * autre.x);
}

Vector3D Vector3D::addScaledVector(const Vector3D& autre, double scale) {
	x = x + autre.x * scale;
	y = y + autre.y * scale;
	z = z + autre.z * scale;
	return Vector3D(x, y, z);
}

float Vector3D::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

void Vector3D::normalize()
{
	float l = magnitude();
	if (l > 0)
	{
		(*this) *= ((float)1) / l;
	}
}

bool Vector3D::operator==(Vector3D other)
{
	if (this->x == other.x && this->y == other.y && this->z == other.z) {
		return true;
	}
	else {
		return false;
	}
}
