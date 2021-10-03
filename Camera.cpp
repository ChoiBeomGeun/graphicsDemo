/*
\author      name : BeomGeun Choi
\par         the assignment number : 3
\par         the course name : CS250
\par         the term : Spring 2018

*/

#include "Camera.h"

Camera::Camera(void)
{
	eye = Point(0, 0, 0);
	back = Vector(0, 0, 1);
	up = Vector(0, 1, 0);
	right = Vector(1, 0, 0);
	distance = 10;
	near = 0.1f;
	far = 10.f;
	width = 10;
	height = 10;
}

Camera::Camera(const Point & E, const Vector & look, const Vector & vp, float fov, float aspect, float near, float far)
{
	eye = E;
	this->far = far;
	this->near = near;
	right = normalize(cross(look, vp));
	back = -normalize(look);
	up = cross(back, right);
	distance = near;
	width = 2.f * distance * tan(fov/2.f);
	height = width / aspect;
}

Point Camera::Eye(void) const
{
	return eye;
}

Vector Camera::Right(void) const
{
	return right;
}

Vector Camera::Up(void) const
{
	return up;
}

Vector Camera::Back(void) const
{
	return back;
}

Vector Camera::ViewportGeometry(void) const
{
	return Vector(width, height, distance);
}

float Camera::NearDistance(void) const
{
	return near;
}

float Camera::FarDistance(void) const
{
	return far;
}

Camera & Camera::Zoom(float factor)
{
	this->width *= factor;
	this->height *= factor;
	return *this;
}

Camera & Camera::Forward(float p_distance)
{
	this->eye = this->eye - (p_distance* back);
	return *this;
}

Camera & Camera::Yaw(float angle)
{
	this->right = rotate(angle, this->up) * this->right;
	this->back = rotate(angle, this->up) * this->back;
	return *this;
}

Camera & Camera::Pitch(float angle)
{
	this->up = rotate(angle, this->right) * this->up;
	this->back = rotate(angle, this->right) * this->back;
	return *this;

}

Camera & Camera::Roll(float angle)
{
	this->right = rotate(angle, this->back) * this->right;
	this->up = rotate(angle, this->back) * this->up;
	return *this;
}
