#pragma once
#include "Vertex.h"
#include <initializer_list>
#include <math.h>

const int ROWS = 4;
const int COLUMNS = 4;

class Matrix
{
public:
	Matrix();
	Matrix(std::initializer_list<float> list);
	Matrix(const Matrix& other);							
	~Matrix();
	float GetM(const int row, const int column) const;	
	void SetM(const int row, const int column, const float value);

	Matrix& operator= (const Matrix &rhs);					
	bool operator==(const Matrix&other) const;				
	const Matrix operator*(const Matrix &other) const;		
	const Vertex operator* (const Vertex &other) const; 	
	Matrix GeneratePerspectiveMatrix(float d, float aspectRatio);
	Matrix GenerateViewMatrix(float d, int width, int height);
	static float ConvertRadian(float deg);
	static Matrix RotationX(float deg);
	static Matrix RotationY(float deg);
	static Matrix RotationZ(float deg);
	static Matrix RotateXYZ(float x, float y, float z);
	static Matrix TransformMatrix(float x, float y, float z);
	static Matrix Identity();
	static Matrix Translation(float x, float y, float z);
	static Matrix Scaling(float x, float y, float z);

private:
	float _matrix[ROWS][COLUMNS];
	void Copy(const Matrix& other);
};

