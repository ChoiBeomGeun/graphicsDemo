/*
\author      name : BeomGeun Choi
\par         the assignment number : 6
\par         the course name : CS250
\par         the term : Spring 2018

*/
#include "HalfSpace.h"

HalfSpace::HalfSpace(const Vector & m, const Point & C)
{
	x = m.x;
	y = m.y;
	z = m.z;
	w = -(m.x*C.x + m.y * C.y + m.z * C.z);
}

HalfSpace::HalfSpace(const Point & A, const Point & B, const Point & C, const Point & P)
{
	const Vector & m = cross(B-A,C-A);
	
	float d = dot(m, A- Point(0, 0, 0));
	HalfSpace check = HalfSpace(m.x, m.y, m.z, -d);
	x = check.x;
	y = check.y;
	z = check.z;
	w = check.w;
	  
	 if (dot(check,P) >0)
	 {
		 x = -check.x;
		 y = -check.y;
		 z = -check.z;
		 w = -check.w;
	 }

	 

}

Polyhedron::Polyhedron(bool cube)
{
	if (cube)
	{
		//right,left
		half_spaces.push_back(HalfSpace( Point(1, 1, -1), Point(1, 1, 1) , Point(1, -1, 1),Point(1, -1, -1) ));
		half_spaces.push_back(HalfSpace(Point(-1, -1, 1),  Point(-1, 1, 1), Point(-1, -1, 1), Point(-1, -1, -1)));
		//top,bottom
		half_spaces.push_back(HalfSpace(Point(-1, 1, -1), Point(-1, 1, 1), Point(1, 1, 1),Point(1, 1, -1)));
		half_spaces.push_back(HalfSpace(Point(-1, -1, 1), Point(-1, -1, -1), Point(1, -1, -1) ,Point(1, -1, 1)));
		//front,back
		half_spaces.push_back(HalfSpace(Point(-1, 1, 1), Point(-1, -1, 1),Point(1, -1, 1),Point(1, 1, 1) ));
		half_spaces.push_back(HalfSpace(Point(-1, -1, -1), Point(-1, 1, -1),Point(1, -1, -1), Point(1, 1, -1)));



	}
	else
		half_spaces.clear();
}

Polyhedron::Polyhedron(float fov, float a, float N, float F)
{
	float nW = (2 * N * tan(fov*.5f)) *0.5f;
	float nH = (nW / a) ;
	float fW= (2 * F* tan(fov*.5f)) *0.5f;
	float fH = (fW / a) ;


	//top
	half_spaces.push_back(HalfSpace(Point(fW, fH, -F) , Point(-fW, fH, -F), Point(nW, nH, -N) , Point(nW, nH, -N)));
	//far
	half_spaces.push_back(HalfSpace(Point(fW, fH, -F), Point(fW, -fH, -F), Point(-fW, fH, -F), Point(-fW, fH, -F)));
	//bot
	half_spaces.push_back(HalfSpace(Point(nW, -nH, -N) , Point(-nW, -nH, -N), Point(fW, -fH, -F), Point(fW, -fH, -F)));
	//left
	half_spaces.push_back(HalfSpace(Point(-nW, nH, -N) , Point(-fW, fH, -F), Point(-nW, -nH, -N) , Point(-nW, -nH, -N)));
	//near
	half_spaces.push_back(HalfSpace(Point(nW, nH, -N) , Point(-nW, nH, -N), Point(nW, -nH, -N), Point(nW, -nH, -N)));
	//right
	half_spaces.push_back(HalfSpace(Point(nW, nH, -N) , Point(nW, -nH, -N), Point(fW, fH, -F) , Point(fW, fH, -F)));

}

bool contains(const Polyhedron & polyhedron, const Hcoord & P)
{
	int NumberOfContains = polyhedron.half_spaces.size();
	for (auto p : polyhedron.half_spaces)
	{
		if (P.w > 0 && dot(p, P) <= 0)
			--NumberOfContains;
	}
	return NumberOfContains == 0;
}
