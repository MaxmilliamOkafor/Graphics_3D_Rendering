#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_pos = position;
	_matrix = Matrix::RotateXYZ(xRotation, yRotation, zRotation) * Matrix::TransformMatrix(-position.GetX(), -position.GetY(), -position.GetZ());
}

Camera::~Camera()
{
}

Matrix Camera::GetCam() 
{ 
	return _matrix;
}

Vertex Camera::GetPosition()
{
	return _pos;
}

void Camera::SetCam(Matrix& m)
{
	_matrix = m;
}

void Camera::SetPosition(Vertex& pos)
{
	_pos = pos;
}