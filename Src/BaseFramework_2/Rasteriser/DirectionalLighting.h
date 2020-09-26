#pragma once
#include "Vector3D.h"
#include "Light.h"

class DirectionalLighting : public Light
{
public:
	DirectionalLighting();
	DirectionalLighting(float red, float green, float blue, Vector3D direction);
	DirectionalLighting(const DirectionalLighting& d);
	~DirectionalLighting();	
	void SetDirection(Vector3D direction);
	Vector3D GetDirection() const;

private:
	Vector3D _dir;
};

