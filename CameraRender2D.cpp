/*
\author      name : BeomGeun Choi
\par         the assignment number : 4
\par         the course name : CS250
\par         the term : Spring 2018

*/
#include "CameraRender2D.h"
#include "Projection.h"




CameraRender2D::CameraRender2D(Render & r) : render(r)
{

}

CameraRender2D::~CameraRender2D(void)
{
	cam_vertices.clear();
	ndc_vertices.clear();
}

void CameraRender2D::SetCamera(const Camera & cam)
{
	world2camera = WorldToCamera(cam);
	camera2ndc = CameraToNDC(cam);

}

void CameraRender2D::DisplayEdges(Mesh & m, const Affine & A, const Vector & color)
{

	cam_vertices.clear();
	ndc_vertices.clear();
	render.SetColor(color);
	for (int i = 0; i < m.VertexCount(); ++i) {

		cam_vertices.push_back(world2camera * A * m.GetVertex(i));
		ndc_vertices.push_back((1/(camera2ndc* cam_vertices[i]).w)
								*(camera2ndc* cam_vertices[i]));

	}

	for (int i = 0; i < m.EdgeCount(); i++)
	{
		const Point &P = ndc_vertices[m.GetEdge(i).index1],
			&Q = ndc_vertices[m.GetEdge(i).index2];
		if (cam_vertices[m.GetEdge(i).index1].z < 0 &&
			cam_vertices[m.GetEdge(i).index2].z < 0)
		{
			render.DrawLine(P, Q);
			
		}

	}


}

void CameraRender2D::DisplayFaces(Mesh & m, const Affine & A, const Vector & color)
{
	const Vector L(0, 0, 1);
	const Point E(0, 0, 0);
	cam_vertices.clear();
	ndc_vertices.clear();
	for (int i = 0; i < m.VertexCount(); ++i) {
		cam_vertices.push_back(world2camera *A * m.GetVertex(i));
		ndc_vertices.push_back((1 / (camera2ndc* cam_vertices[i]).w) 
								*(camera2ndc* cam_vertices[i]));
	}


	for (int i = 0; i < m.FaceCount(); i++)
	{
		Point P = cam_vertices[m.GetFace(i).index1];
		Point Q = cam_vertices[m.GetFace(i).index2];
		Point R = cam_vertices[m.GetFace(i).index3];
		Vector M = cross(Q - P, R - P);



		if (dot(M, (E - P)) > 0)
		{
			float U = abs(dot(M, L)) / (abs(M)*abs(L));

			render.SetColor(U*color);
			if (P.z < 0 &&
				Q.z < 0 &&
				R.z < 0)
			{
				render.FillTriangle(
					ndc_vertices[m.GetFace(i).index1],
					ndc_vertices[m.GetFace(i).index2],
					ndc_vertices[m.GetFace(i).index3]);
			}


		}

	}
}
