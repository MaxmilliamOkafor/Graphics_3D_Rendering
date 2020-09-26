#include "Light.h"

Light::Light()
{
}

Light::Light(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;
}

Light::~Light()
{
}

Light::Light(const Light & other)
{
	_r = other.GetRed();
	_g = other.GetGreen();
	_b = other.GetBlue();
}

Light& Light::operator=(const Light& rhs)
{
	_r = rhs.GetRed();
	_g = rhs.GetGreen();
	_b = rhs.GetBlue();
	return *this;
}

void Light::SetRed(float r)
{
	_r = r;
}

void Light::SetGreen(float g)
{
	_g = g;
}

void Light::SetBlue(float b)
{
	_b = b;
}

float Light::GetRed() const
{
	return _r;
}

float Light::GetGreen() const
{
	return _g;
}

float Light::GetBlue() const
{
	return _b;
}

