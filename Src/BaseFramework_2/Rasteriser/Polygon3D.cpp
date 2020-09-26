#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
	
	_Zdepth = p.GetDepthValue();
	_normal = p.GetNormal();
	_cull = p.GetIsCull();
	_color = p.GetColor();

}

int Polygon3D::GetIndex(int x) const
{
	return _indices[x];
}

Polygon3D& Polygon3D::operator= (const Polygon3D &rhs)
{
	if (this != &rhs)
	{
		_indices[0] = rhs.GetIndex(0);
		_indices[1] = rhs.GetIndex(1);
		_indices[2] = rhs.GetIndex(2);
		
		_Zdepth = rhs.GetDepthValue();
		_normal = rhs.GetNormal();
		_cull = rhs.GetIsCull();
		_color = rhs.GetColor();
	}

	return *this;
}

void Polygon3D::SetIsCull(bool isCull)
{
	 _cull = isCull;
}

void Polygon3D::SetNormal(Vector3D normal)
{
	_normal = normal;
}

void Polygon3D::SetColor(COLORREF color)
{
	_color = color;
}

void Polygon3D::SetDepthValue(float z)
{
	_Zdepth = z;
}

Vector3D Polygon3D::GetNormal() const
{
	return _normal;
}

bool Polygon3D::GetIsCull()  const
{
	return _cull;
}

float Polygon3D::GetDepthValue() const
{
	return _Zdepth;
}

COLORREF Polygon3D::GetColor() const
{
	return _color;
}