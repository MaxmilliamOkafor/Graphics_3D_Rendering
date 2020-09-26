#include "DirectionalLighting.h"

DirectionalLighting::DirectionalLighting()
{
}

DirectionalLighting::DirectionalLighting(float red, float green, float blue, Vector3D direction) : Light(red, green, blue)
{
	_dir = direction;
}

DirectionalLighting::DirectionalLighting(const DirectionalLighting& d)
{
	_r = d.GetRed();
	_g = d.GetGreen();
	_b = d.GetBlue();
	_dir = d.GetDirection();
}

DirectionalLighting::~DirectionalLighting()
{
}

void DirectionalLighting::SetDirection(Vector3D d)
{
	_dir = d;
}

Vector3D DirectionalLighting::GetDirection() const
{
	return _dir;
}