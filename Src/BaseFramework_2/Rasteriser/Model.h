#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include <vector>
#include "Matrix.h"
#include "Camera.h"
#include "algorithm"
#include <functional> 
#include "DirectionalLighting.h"
#include "AmbientLighting.h"
#include <math.h>
#include "Windows.h"

using namespace std; 

const float MIN = 0.0f;
const float MAX = 255.0f;

class Model
{
public:
	Model();
	~Model();
	vector<Polygon3D>& GetPolygons();
	vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);
	void DehomogenizeTransformedVertices();
	void CalculateBackfaces(Vertex pos);
	void Sort(void);
	void CalculateLIghtingDirectional(vector<DirectionalLighting>& d);
	void CalculateLightingAmbientLight(AmbientLighting a);

private:
	vector<Vertex> _vertices;	
	vector<Polygon3D> _polygons;
	vector<Vertex> _transformedVertices;
	float _ka_red;
	float _ka_green;
	float _ka_blue;
	float _kd_red;
	float _kd_green;
	float _kd_blue;
};

