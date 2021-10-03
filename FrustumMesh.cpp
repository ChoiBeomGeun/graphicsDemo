/*
\author      name : BeomGeun Choi
\par         the assignment number : 3
\par         the course name : CS250
\par         the term : Spring 2018

*/

#include "FrustumMesh.h"



const FrustumMesh::Face FrustumMesh::faces[12]{
	Face(5,6,7),Face(7,8,5),Face(2,1,4),Face(4,3,2),
	Face(5,1,2),Face(2,6,5),Face(3,4,8),Face(8,7,3),
	Face(6,2,3),Face(3,7,6),Face(8,4,1),Face(1,5,8)

};
const FrustumMesh::Edge FrustumMesh::edges[16]{
	Edge(0,1),Edge(0,2),Edge(0,3),Edge(0,4),
	Edge(1,2),Edge(2,3),Edge(3,4),Edge(4,1),
	Edge(5,6),Edge(6,7),Edge(7,8),Edge(8,5),
	Edge(1,5),Edge(4,8),Edge(2,6),Edge(3,7)
};
FrustumMesh::FrustumMesh(float fov, float a, float n, float f)
{

	float nwidth = 2.f * tan(fov/2.f)*n;
	float nheight = nwidth/a;
	float fwidth = 2.f * tan(fov/2.f)*f;
	float fheight = fwidth / a;
	nwidth /= 2;
	nheight /= 2;
	fwidth /= 2;
	fheight /= 2;

	vertices[0] = Point(0, 0, 0);
	vertices[1] = Point(nwidth, nheight,-n);
	vertices[2] = Point(nwidth, -nheight, -n);
	vertices[3] = Point(-nwidth, -nheight, -n);
	vertices[4] = Point(-nwidth, nheight, -n);

	vertices[5] = Point(fwidth, fheight, -f);
	vertices[6] = Point(fwidth, -fheight, -f);
	vertices[7] = Point(-fwidth, -fheight, -f);
	vertices[8] = Point(-fwidth, fheight, -f);
}

int FrustumMesh::VertexCount(void)
{
	return sizeof(vertices) / sizeof(*vertices);
}

Point FrustumMesh::GetVertex(int i)
{
	return 	vertices[i];
}

Vector FrustumMesh::Dimensions(void) 
{
	float deltaX = vertices[0].x;
	float deltaY = vertices[0].y;
	float deltaZ = vertices[0].z;

	for (int i = 0; i <= 8; i++) {
		if (deltaX != vertices[i].x)
			deltaX = abs(deltaX - vertices[i].x);
		if (deltaY != vertices[i].y)
			deltaY = abs(deltaY - vertices[i].y);
		if (deltaZ != vertices[i].z)
			deltaZ = abs(deltaZ - vertices[i].z);

	}
	return Vector(deltaX, deltaY, deltaZ);

}

Point FrustumMesh::Center(void)
{
	Point temp{ 0,0,0 };
	for (int i = 0; i <= VertexCount(); i++)
	{
		temp.x += GetVertex(i).x;
		temp.y += GetVertex(i).y;
		temp.z += GetVertex(i).z;
	}
	return Point(temp.x / VertexCount(),
		temp.y / VertexCount(),
		temp.z / VertexCount());
}

int FrustumMesh::FaceCount(void)
{
	return sizeof(faces) / sizeof(*faces);
}

Mesh::Face FrustumMesh::GetFace(int i)
{
	return 	faces[i];
}

int FrustumMesh::EdgeCount(void)
{
	return sizeof(edges) / sizeof(*edges);
}

Mesh::Edge FrustumMesh::GetEdge(int i)
{
	return edges[i];
}
