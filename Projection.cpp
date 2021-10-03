/*
\author      name : BeomGeun Choi
\par         the assignment number : 4
\par         the course name : CS250
\par         the term : Spring 2018

*/
#include "Projection.h"

Affine CameraToWorld(const Camera & cam)
{
	return Affine(cam.Right(),cam.Up(),cam.Back(),cam.Eye());
}

Affine WorldToCamera(const Camera & cam)
{
	return Affine(inverse(CameraToWorld(cam)));
}

Matrix CameraToNDC(const Camera & cam)
{
	Matrix temp;
	temp.row[0].x = (2 * cam.ViewportGeometry().z) / cam.ViewportGeometry().x;
	temp.row[0].y = 0;
	temp.row[0].z = 0;
	temp.row[0].w = 0;

	temp.row[1].x = 0;
	temp.row[1].y = (2 * cam.ViewportGeometry().z) / cam.ViewportGeometry().y;
	temp.row[1].z = 0;
	temp.row[1].w = 0;

	temp.row[2].x = 0;
	temp.row[2].y = 0;
	temp.row[2].z = (cam.NearDistance() + cam.FarDistance()) / (cam.NearDistance() - cam.FarDistance());
	temp.row[2].w = (2*cam.NearDistance() * cam.FarDistance()) / (cam.NearDistance() - cam.FarDistance());

	temp.row[3].x = 0;
	temp.row[3].y = 0;
	temp.row[3].z = -1;
	temp.row[3].w = 0;

	return temp;
}
