#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	~Camera();
	Vertex GetPosition();
	void SetPosition(Vertex& pos);
	Matrix GetCam();
	void SetCam(Matrix& matrix);

private:
	Vertex _pos;
	Matrix _matrix;
};

