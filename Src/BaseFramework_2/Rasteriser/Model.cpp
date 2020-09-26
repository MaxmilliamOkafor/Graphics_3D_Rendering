#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

vector<Vertex>& Model::GetVertices()
{
	return _transformedVertices;
}

vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

size_t Model::GetVertexCount() const
{
	return _transformedVertices.size();
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z, 1.0f));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

void Model::ApplyTransformToLocalVertices(const Matrix &m)
{
	_transformedVertices.clear();

	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_transformedVertices.push_back(m * _vertices[i]);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix &transform)
{
	for (size_t i = 0; i < GetVertexCount(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

void Model::DehomogenizeTransformedVertices()
{
	for (int i = 0; i < GetVertexCount(); i++)
	{
		_transformedVertices[i] = _transformedVertices[i].dehomogenizeVertices(_transformedVertices[i]);
	}
}

void Model::CalculateBackfaces(Vertex posVertex)
{
	Vertex vertexArray[3];
	Vector3D aVec, bVec, eyeVector, normal;
	float dotProduct;
	
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertexArray[j] = GetVertices()[GetPolygons()[i].GetIndex(j)];
		}

		aVec = vertexArray[0] - vertexArray[1];
		bVec = vertexArray[0] - vertexArray[2];

		normal = Vector3D::CrossProduct(aVec, bVec);
		normal = Vector3D::Normalising(normal);
		GetPolygons()[i].SetNormal(normal);

		eyeVector = vertexArray[0] - posVertex;
		eyeVector = Vector3D::Normalising(eyeVector);

		dotProduct = Vector3D::DotProduct(normal, eyeVector);

		if (dotProduct < 0)
		{
			GetPolygons()[i].SetIsCull(false);
		}
		else
		{
			GetPolygons()[i].SetIsCull(true);
		}
	}
}

bool order(Polygon3D& elem1, Polygon3D& elem2)
{
	return elem1.GetDepthValue() > elem2.GetDepthValue();
}

// Sorting the dept value of each polygon by the vertices average Z value
void Model::Sort(void)
{
	float average = 0.0f;
	Vertex vertexArr[3];

	for (int i = 0; i < GetPolygonCount(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertexArr[j] = GetVertices()[GetPolygons()[i].GetIndex(j)];
		}

		average = (vertexArr[0].GetZ() + vertexArr[1].GetZ() + vertexArr[2].GetZ()) / 3;	
		_polygons[i].SetDepthValue(average);
	}

	sort(_polygons.begin(), _polygons.end(), order);
}

void Model::CalculateLightingAmbientLight(AmbientLighting a)
{
	size_t polygonSize = GetPolygonCount();
	float totalR, totalG, totalB;
	COLORREF color;
	_ka_red = 0.2f;
	_ka_green = 0.2f;
	_ka_blue = 0.2f;

	for (int i = 0; i < polygonSize; i++)
	{
		totalR = 0;
		totalG = 0;
		totalB = 0;

		totalR = a.GetRed() * _ka_red;
		totalG = a.GetGreen() * _ka_green;
		totalB = a.GetBlue() * _ka_blue;

		color = RGB(totalR, totalG, totalB); 
		_polygons[i].SetColor(color);		 
	}
}

void Model::CalculateLIghtingDirectional(vector<DirectionalLighting>& d)
{
	_kd_red = 1.0f;
	_kd_green = 1.0f;
	_kd_blue = 1.0f;

	float totalR, totalG, totalB;
	float tempR, tempG, tempB;

	totalR = 0;
	totalG = 0;
	totalB = 0;
	tempR = 0;
	tempG = 0;
	tempB = 0;

	float dotProduct = 0;
	COLORREF color;
	Vector3D normalDirectional;
	
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		totalR = GetRValue(_polygons[i].GetColor());
		totalG = GetGValue(_polygons[i].GetColor());
		totalB = GetBValue(_polygons[i].GetColor());

		for (int j = 0; j < d.size(); j++)
		{
			tempR = d[j].GetRed() * _kd_red;
			tempG = d[j].GetGreen() * _kd_green;
			tempB = d[j].GetBlue() * _kd_blue;

			normalDirectional = Vector3D::Normalising(d[j].GetDirection());
			dotProduct = Vector3D::DotProduct(normalDirectional, _polygons[i].GetNormal());

			if (dotProduct > 0)
			{
				totalR = tempR * dotProduct;
				totalG = tempG * dotProduct;
				totalB = tempB * dotProduct;
			}
		}

		totalR = totalR > MAX ? MAX : totalR; totalR = totalR < MIN ? MIN : totalR;
		totalG = totalG > MAX ? MAX : totalG; totalG = totalG < MIN ? MIN : totalG;
		totalB = totalB > MAX ? MAX : totalB; totalB = totalB < MIN ? MIN : totalB;
		color = RGB(totalR, totalG, totalB);
		_polygons[i].SetColor(color);
	}
}