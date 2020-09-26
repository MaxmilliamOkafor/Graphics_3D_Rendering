#pragma once
#include <vector>

class Light
{
public:
	Light();
	Light(float r, float g, float b);
	~Light();
	Light(const Light& other);
	Light& operator=(const Light& rhs);
	void SetRed(float r);
	float GetRed() const;
	void SetGreen(float g);
	float GetGreen() const;
	void SetBlue(float b);
	float GetBlue() const;

protected:
	float _r;
	float _g;
	float _b;
};