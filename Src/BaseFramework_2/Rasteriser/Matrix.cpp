#include "Matrix.h"
#include <initializer_list>

Matrix::Matrix()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			_matrix[i][j] = 0.0f;
		}
	}
}

Matrix::Matrix(std::initializer_list<float> list)
{
	if (list.size() != ROWS * COLUMNS)
	{
		throw "Insufficient values supplied";
	}

	auto it = begin(list);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			_matrix[i][j] = *it++;
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	Copy(other);
}

Matrix::~Matrix()
{
}

float Matrix::GetM(const int row, const int column) const
{
	return _matrix[row][column];
}

void Matrix::SetM(const int row, const int column, const float value)
{
	_matrix[row][column] = value;
}

Matrix& Matrix::operator= (const Matrix &rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

bool Matrix::operator==(const Matrix &other) const
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (_matrix[i][j] != other.GetM(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

const Matrix Matrix::operator*(const Matrix &other) const
{
	Matrix result;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			float tempVal = 0.0f;

			for (int k = 0; k < ROWS; k++)
			{
				tempVal += _matrix[i][k] * other.GetM(k, j);
			}
			result.SetM(i, j, tempVal);
		}
	}
	return result;
}

const Vertex Matrix::operator*(const Vertex &other) const
{	
	Vertex v(other);
	float _x = 0.0f;	
	float _y = 0.0f;
	float _z = 0.0f;
	float _w = 0.0f;
	
	_x = _matrix[0][0] * other.GetX() + _matrix[0][1] * other.GetY() + _matrix[0][2] * other.GetZ() + _matrix[0][3] * other.GetW();
	_y = _matrix[1][0] * other.GetX() + _matrix[1][1] * other.GetY() + _matrix[1][2] * other.GetZ() + _matrix[1][3] * other.GetW();
	_z = _matrix[2][0] * other.GetX() + _matrix[2][1] * other.GetY() + _matrix[2][2] * other.GetZ() + _matrix[2][3] * other.GetW();
	_w = _matrix[3][0] * other.GetX() + _matrix[3][1] * other.GetY() + _matrix[3][2] * other.GetZ() + _matrix[3][3] * other.GetW();

	v.SetX(_x);
	v.SetY(_y);
	v.SetZ(_z);
	v.SetW(_w);

	return v;
}

void Matrix::Copy(const Matrix &other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			_matrix[i][j] = other.GetM(i, j);
		}
	}
}

Matrix Matrix::GeneratePerspectiveMatrix(float d, float a)
{
	return 
	{
		(d/a), 0, 0, 0,
		0, d, 0, 0,
		0, 0, d, 0,
		0, 0, 1, 0
	};
}

Matrix Matrix::GenerateViewMatrix(float d, int width, int height)
{
	return
	{
		(float)width / 2,   0,     0,  (float)width / 2,
		0, -(float)height / 2,     0, (float)height / 2,
		0,				    0, d / 2,			  d / 2,
		0,				    0,     0,				  1
	};
}

float Matrix::ConvertRadian(float deg)
{
	return (float)(deg * (3.14159265359 / 180.0f));
}

Matrix Matrix::RotationX(float deg)
{
	float rad = ConvertRadian(deg);

	return {
		1,				  0,               0, 0,
		0,  (float)cos(rad), (float)sin(rad), 0,
		0, -(float)sin(rad), (float)cos(rad), 0,
		0,				  0,			   0, 1
	};
}

Matrix Matrix::RotationY(float deg)
{
	float rad = ConvertRadian(deg);

	return {
		(float)cos(rad), 0, -(float)sin(rad), 0,
					  0, 1,			       0, 0,
		(float)sin(rad), 0,  (float)cos(rad), 0,
					  0, 0,                0, 1
	};
}

Matrix Matrix::RotationZ(float deg)
{
	float rad = ConvertRadian(deg);

	return {
		(float)cos(rad), (float)sin(rad), 0, 0,
	   -(float)sin(rad), (float)cos(rad), 0, 0,
		              0,               0, 1, 0,
					  0,			   0, 0, 1
	};
}

Matrix Matrix::RotateXYZ(float x, float y, float z)
{
	return (RotationX(x) * RotationY(y) * RotationZ(z));
}

Matrix Matrix::TransformMatrix(float x, float y, float z)
{
	return {
		1, 0, 0,  x,
		0, 1, 0,  y,
		0, 0, 1,  z,
		0, 0, 0,  1
	};
}

Matrix Matrix::Identity()
{
	return {
		1, 0, 0,  0,
		0, 1, 0,  0,
		0, 0, 1,  0,
		0, 0, 0,  1
	};
}

Matrix Matrix::Translation(float x, float y, float z)
{
	return { 1.0f, 0.0f, 0.0f, x,
			 0.0f, 1.0f, 0.0f, y,
			 0.0f, 0.0f, 1.0f, z,
			 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix Matrix::Scaling(float x, float y, float z)
{
	return  { x, 0.0f, 0.0f, 0.0f,
			  0.0f, y, 0.0f, 0.0f,
			  0.0f, 0.0f, z, 0.0f,
			  0.0f, 0.0f, 0.0f, 1.0f };
}