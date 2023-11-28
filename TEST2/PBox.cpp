#include "PBox.h"

std::vector<Vector3D> PBox::GetVertices()
{
	std::vector<Vector3D> vertices;

	vertices.push_back(Vector3D(-halfSize.x, -halfSize.y, -halfSize.z));

	vertices.push_back(Vector3D(-halfSize.x, -halfSize.y, halfSize.z));

	vertices.push_back(Vector3D(-halfSize.x, halfSize.y, -halfSize.z));

	vertices.push_back(Vector3D(halfSize.x, -halfSize.y, -halfSize.z));

	vertices.push_back(Vector3D(halfSize.x, halfSize.y, -halfSize.z));

	vertices.push_back(Vector3D(halfSize.x, -halfSize.y, halfSize.z));

	vertices.push_back(Vector3D(-halfSize.x, halfSize.y, halfSize.z));

	vertices.push_back(Vector3D(halfSize.x, halfSize.y, halfSize.z));

	for (auto& vertice : vertices)
	{
		vertice = offset * vertice;
	}

	return vertices;
}
