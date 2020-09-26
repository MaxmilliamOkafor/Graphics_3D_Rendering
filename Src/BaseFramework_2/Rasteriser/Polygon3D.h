#pragma once
#include "Vector3D.h"
#include "Windows.h"

class Polygon3D
{
static const int indicesLimit = 3;

public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	Polygon3D(const Polygon3D& p);
	~Polygon3D();
	int GetIndex(int x) const;
	Polygon3D& operator= (const Polygon3D &rhs);
	void SetIsCull(bool isCull);
	bool GetIsCull() const;
	void SetNormal(Vector3D normal);
	Vector3D GetNormal() const;
	void SetDepthValue(float z);
	float GetDepthValue() const;
	void SetColor(COLORREF color);
	COLORREF GetColor() const;

private:
	int _indices[3];
	float _Zdepth;
	COLORREF _color;
	bool _cull;
	Vector3D _normal;
};

