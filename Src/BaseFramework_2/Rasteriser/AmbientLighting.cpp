#include "AmbientLighting.h"

AmbientLighting::AmbientLighting()
{
}

AmbientLighting::AmbientLighting(float red, float green, float blue) : Light(red, green, blue)
{
}

AmbientLighting::AmbientLighting(const AmbientLighting& a)
{
	_r = a.GetRed();
	_g = a.GetGreen();
	_b = a.GetBlue();
}

AmbientLighting::~AmbientLighting()
{
}