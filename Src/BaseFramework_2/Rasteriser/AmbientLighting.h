#pragma once
#include "Vector3D.h"
#include "Light.h"

class AmbientLighting : public Light
{
public:
	AmbientLighting();
	AmbientLighting(float r, float g, float b);
	AmbientLighting(const AmbientLighting& a);
	~AmbientLighting();
};

