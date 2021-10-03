/*
\author      name : BeomGeun Choi
\par         the assignment number : 3
\par         the course name : CS250
\par         the term : Spring 2018

*/

#include "SimpleRender.h"





SimpleRender::SimpleRender(Render & r) : render(r)
{
	
	Matrix Perspective;
	Perspective.row[0].x = 1.f;
	Perspective.row[0].y = 0;
	Perspective.row[0].z = 0;
	Perspective.row[0].w = 0;

	Perspective.row[1].x = 0;
	Perspective.row[1].y = 1.f;
	Perspective.row[1].z = 0;
	Perspective.row[1].w = 0;

	Perspective.row[2].x = 0;
	Perspective.row[2].y = 0;
	Perspective.row[2].z = 1.f/11.f;
	Perspective.row[2].w = -5.f/11.f;

	Perspective.row[3].x = 0;
	Perspective.row[3].y = 0;
	Perspective.row[3].z = -2.f/11.f;
	Perspective.row[3].w = 10.f/11.f;

	PersProj = Perspective;
}

SimpleRender::~SimpleRender(void)
{
}

void SimpleRender::DisplayEdges(Mesh& m, const Affine& A, const Vector& color)
{
	for (int i = 0 ; i <= m.EdgeCount(); i++)
	{
		render.DrawLine(PersProj*A*m.GetVertex(m.GetEdge(i).index1), PersProj*A*m.GetVertex(m.GetEdge(i).index2));
	}
	render.SetColor(color);
}

void SimpleRender::DisplayFaces(Mesh & m, const Affine & A, const Vector & color)
{



	const Vector L(0, 0, 1);
	const Point E(0, 0, 5);
	world_vertices.clear();
	for (int i = 0; i < m.VertexCount(); ++i) {
		world_vertices.push_back(A * m.GetVertex(i));
	}



	for (int i = 0; i < m.FaceCount(); i++)
	{
 		Point P = world_vertices[m.GetFace(i).index1];
		Point Q = world_vertices[m.GetFace(i).index2];
		Point R = world_vertices[m.GetFace(i).index3];
		Vector M = cross(Q - P, R - P);



		if (dot(M, (E-P)) > 0) 
		{
			float U = abs(dot(M, L)) / (abs(M)*abs(L));
			render.SetColor(U*color);

			render.FillTriangle(
				PersProj*A*m.GetVertex(m.GetFace(i).index1),
				PersProj*A*m.GetVertex(m.GetFace(i).index2)
				, PersProj*A*m.GetVertex(m.GetFace(i).index3));

		}
	
	}

	
	
}
