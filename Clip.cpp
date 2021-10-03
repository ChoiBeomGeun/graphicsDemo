/*
\author      name : BeomGeun Choi
\par         the assignment number : 7
\par         the course name : CS250
\par         the term : Spring 2018

*/

#include "Clip.h"

Hcoord MakeInterSection(Hcoord A, Hcoord B,HalfSpace H)
{
	const float t = dot(H, A) / (dot(H, A) - dot(H, B));
	return (1 - t) * A + t*B;
}

void VertexChange(std::vector<Hcoord>& vertices,HalfSpace H,unsigned & IntersectionCheck)
{

		std::vector<Hcoord> SaveVector;

		for (unsigned i = 0; i < vertices.size(); i++)
		{
			Hcoord Cur = vertices[i];
			Hcoord Next = vertices[i + 1];

			if(i == vertices.size()-1)
			{
				Cur = vertices[vertices.size()-1];
				Next = vertices[0];

			}

			if ((dot(H, Cur) > 0) && (dot(H, Next) <= 0))
				SaveVector.push_back(MakeInterSection(Cur, Next, H));
			if ((dot(H, Cur) <= 0) && (dot(H, Next) <= 0)) {
				SaveVector.push_back(Cur);
				IntersectionCheck++;
			}
			else if ((dot(H, Cur) <= 0) && (dot(H, Next) > 0)) {
				SaveVector.push_back(Cur);
				SaveVector.push_back(MakeInterSection(Cur, Next, H));
			}


		}
	


		vertices = SaveVector;

}


bool Clip::operator()(std::vector<Hcoord>& vertices)
{
	unsigned IntersectionChecking =0;
	for (auto aH : half_spaces)
	{
		VertexChange(vertices, aH, IntersectionChecking);


	}

	if (IntersectionChecking == vertices.size())
		return false;
	return true;
}
