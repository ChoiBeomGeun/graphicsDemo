/*
\author      name : BeomGeun Choi
\par         the assignment number : 5
\par         the course name : CS250
\par         the term : Spring 2018

*/

#include "RasterUtilities.h"
#include <algorithm>

void ClearBuffers(Raster & r, float z) 
{

	for (int i = 0; i < r.Width(); ++i)
	{
		r.IncrementX();
		for (int j = 0; j < r.Height(); ++j)
		{
			r.IncrementY();
			r.GotoPoint(i, j);
			r.WritePixel();
			r.WriteZ(z);
		}
	}
}

void FillTriangle(Raster & r, const Hcoord & P, const Hcoord & Q, const Hcoord & R)
{
	float inverseSlope[3] {0.f,0.f,0.f};
	Hcoord topVec{ 0,0,0 };
	Hcoord middleVec{0,0,0};
	Hcoord bottomVec{0,0,0};
	auto _p = Hcoord(1 / P.w * P);
	auto _q = Hcoord(1 / Q.w * Q);
	auto _r = Hcoord(1 / R.w * R);
	

	if (_p.y < _q.y)
	{
		if (_r.y < _p.y)
		{
			topVec = _q;
			middleVec = _p;
			bottomVec = _r;

		}
		else if (_q.y < _r.y)
		{
			middleVec = _q;
			bottomVec = _p;
			topVec = _r;

		}
		else if (_q.y > _r.y)
		{
			
			middleVec = _r;
			bottomVec = _p;
			topVec = _q;
		}

	}
	else
	{
		if (_r.y < _q.y)
		{
			
			topVec = _p;
			middleVec = _q;
			bottomVec = _r;

		}
		else if (_p.y < _r.y)
		{
			
			middleVec = _p;
			bottomVec = _q;
			topVec = _r;
		}
		else if (_p.y > _r.y)
		{
			
			middleVec = _r;
			bottomVec = _q;
			topVec = _p;
		}
	}



	inverseSlope[0] = (middleVec.x - bottomVec.x) / (middleVec.y - bottomVec.y);
	inverseSlope[1] = (topVec.x - bottomVec.x) / (topVec.y - bottomVec.y);
	inverseSlope[2] = (topVec.x - middleVec.x) / (topVec.y - middleVec.y);



	const auto m = cross(_r - _p, _q - _p);
	const auto d = dot(_p - Hcoord(0, 0, 0, 1), m);
	if (inverseSlope[0] > inverseSlope[1])
	{
		int j_min = static_cast<int>(ceil(bottomVec.y));
		int j_max = static_cast<int>(floor(middleVec.y));

		for (int j = j_min; j <= j_max; ++j)
		{
			int x_min = static_cast<int>(bottomVec.x + inverseSlope[1] * (j - bottomVec.y));
			int x_max = static_cast<int>(bottomVec.x + inverseSlope[0] * (j - bottomVec.y));
			int i_min = static_cast<int>(ceil(x_min));
			int i_max = static_cast<int>(floor(x_max));
			r.GotoPoint(i_min, j);

			for (int i = i_min; i < i_max; ++i)
			{
				r.IncrementX();
				const auto z = (d - m.x*i - m.y*j) / m.z;
				if (z < r.GetZ())
				{
					r.WritePixel();
					r.WriteZ(z);
				}

			}
		}
		j_min = static_cast<int>(ceil(middleVec.y));
		j_max = static_cast<int>(floor(topVec.y));

		for (int j = j_min; j <= j_max; ++j)
		{
			int x_min = static_cast<int>(topVec.x - inverseSlope[1] * (topVec.y - j));
			int x_max = static_cast<int>(middleVec.x + inverseSlope[2] * (j - middleVec.y));
			int i_min = static_cast<int>(ceil(x_min));
			int i_max = static_cast<int>(floor(x_max));
			r.GotoPoint(i_min, j);

			for (int i = i_min; i < i_max; ++i)
			{
				r.IncrementX();
				const auto z = (d - m.x*i - m.y*j) / m.z;
				if (z < r.GetZ())
				{
					r.WritePixel();
					r.WriteZ(z);
				}

			}
		}
	}
	else
	{
		int j_min = static_cast<int>(ceil(bottomVec.y));
		int j_max = static_cast<int>(floor(middleVec.y));


		for (int j = j_min; j <= j_max; ++j)
		{
			int x_min = static_cast<int>(bottomVec.x + inverseSlope[0] * (j - bottomVec.y));
			int x_max = static_cast<int>(bottomVec.x + inverseSlope[1] * (j - bottomVec.y));
			int i_min = static_cast<int>(ceil(x_min));
			int i_max = static_cast<int>(floor(x_max));
			r.GotoPoint(i_min, j);

			for (int i = i_min; i < i_max; ++i)
			{
				r.IncrementX();
				const auto z = (d - m.x*i - m.y*j) / m.z;
				if (z < r.GetZ())
				{
					r.WritePixel();
					r.WriteZ(z);
				}

			}
		}
		j_min = static_cast<int>(ceil(middleVec.y));
		j_max = static_cast<int>(floor(topVec.y));

		for (int j = j_min; j <= j_max; ++j)
		{
			int x_min = static_cast<int>(middleVec.x + inverseSlope[2] * (j - middleVec.y));
			int x_max = static_cast<int>(topVec.x - inverseSlope[1] * (topVec.y - j));
			int i_min = static_cast<int>(ceil(x_min));
			int i_max = static_cast<int>(floor(x_max));
			r.GotoPoint(i_min, j);

			for (int i = i_min; i < i_max; ++i)
			{
				r.IncrementX();
				const auto z = (d - m.x*i - m.y*j) / m.z;
				if (z < r.GetZ())
				{
					r.WritePixel();
					r.WriteZ(z);
				}

			}
		}
		
	}


}