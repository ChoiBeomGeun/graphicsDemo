/*
\author      name : BeomGeun Choi
\par         the assignment number : 1
\par         the course name : CS250
\par         the term : Spring 2018

*/
#include "Affine.h"
#include <complex.h>

//(constructor) 
//returns the 4-vector [X,Y,Z,W].
Hcoord::Hcoord(float X, float Y, float Z, float W) :x(X), y(Y), z(Z), w(W)
{

}
//(constructor)
// returns a point with components (X,Y,Z).
Point::Point(float X, float Y, float Z) : Hcoord(X, Y, Z, 1)
{

}
//(default constructor) 
// returns the 3D affine transformation corresponding to the trivial affine transformation
// whose linear part is the 0 transformation, and whose translation part is the 0 vector.
Affine::Affine(void) 
{
	row[0].x = 0;
	row[0].y = 0;
	row[0].z = 0;
	row[0].w = 0;

	row[1].x = 0;
	row[1].y = 0;
	row[1].z = 0;
	row[1].w = 0;

	row[2].x = 0;
	row[2].y = 0;
	row[2].z = 0;
	row[2].w = 0;

	row[3].x = 0;
	row[3].y = 0;
	row[3].z = 0;
	row[3].w = 1;
}
// (constructor) 
// returns the affine transformation whose columns
Affine::Affine(const Vector & Lx, const Vector & Ly, const Vector & Lz, const Point & D)

{
	row[0].x = Lx.x;
	row[0].y = Ly.x;
	row[0].z = Lz.x;
	row[0].w = D.x;

	row[1].x = Lx.y;
	row[1].y = Ly.y;
	row[1].z = Lz.y;
	row[1].w = D.y;

	row[2].x = Lx.z;
	row[2].y = Ly.z;
	row[2].z = Lz.z;
	row[2].w = D.z;

	row[3].x = Lx.w;
	row[3].y = Ly.w;
	row[3].z = Lz.w;
	row[3].w = D.w;

	
}
//(constructor) returns a vector with components ⟨X,Y,Z⟩.
Vector::Vector(float X, float Y, float Z) : Hcoord(X, Y, Z, 0)
{

}
//returns the sum u + v of two four - component vectors.
Hcoord operator+(const Hcoord & u, const Hcoord & v)
{
	return Hcoord(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}
//returns the difference u−v of two four - component vectors.
Hcoord operator-(const Hcoord & u, const Hcoord & v)
{
	return Hcoord(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}
//returns the component - wise negation −v of a four - component vector.
Hcoord operator-(const Hcoord & v)
{
	return  Hcoord(-v.x, -v.y, -v.z, -v.w);
}
//returns the product rv of a scalar and a four - component vector.
Hcoord operator*(float r, const Hcoord & v)
{
	return Hcoord(v.x *r, v.y*r, v.z*r, v.w*r);
}
//returns the result Mv of applying the 4×4 matrix M to the four - component vector v.
Hcoord operator*(const Matrix & A, const Hcoord & v)
{



	return 	Hcoord (A.row[0].x*v.x + A.row[0].y*v.y + A.row[0].z*v.z + A.row[0].w*v.w,
		A.row[1].x*v.x + A.row[1].y*v.y + A.row[1].z*v.z + A.row[1].w*v.w,
		A.row[2].x*v.x + A.row[2].y*v.y + A.row[2].z*v.z + A.row[2].w*v.w,
		A.row[3].x*v.x + A.row[3].y*v.y + A.row[3].z*v.z + A.row[3].w*v.w);
	

	
}
//returns the composition (matrix product) A∘B of the 4×4 matrices A and B
Matrix operator*(const Matrix & A, const Matrix & B)
{

	Matrix temp;
	int Column=0;
	int Row=0;

	while(Row != 4)
	{
		temp.row[Row][Column] =
			A.row[Row][0] * B.row[0][Column]
			+ A.row[Row][1] * B.row[1][Column]
			+ A.row[Row][2] * B.row[2][Column]
			+ A.row[Row][3] * B.row[3][Column];

		Column++;

		if(Column ==4)
		{
			Column = 0;
			Row++;
		}
	}
	return temp;
}
// returns the dot product u ⋅v  of two three-dimensional vectors.
float dot(const Vector & u, const Vector & v)
{
	return 
		((u.x *v.x) + 
		(u.y*v.y)+ 
		(u.z*v.z)
	
			);
}
//  returns the length |v| of a three-dimensional vector.
float abs(const Vector & v)
{
	
	return sqrt((v.x*v.x) + (v.y * v.y) + (v.z*v.z) );
}
// returns the unit vector that points in the same direction as the vector v.
Vector normalize(const Vector & v)
{
	return Vector(v.x/abs(v),v.y/abs(v),v.z/abs(v));
}
//returns the cross product (vector product) u×v  of two three—dimensional vectors.
Vector cross(const Vector & u, const Vector & v)
{
	return Vector(
		(u.y*v.z)-(u.z*v.y),
		-((u.x*v.z)-(u.z*v.x)),
		(u.x*v.y)-(u.y*v.x));
}
//returns the affine transformation R for counterclockwise rotation by the angle t (in radians) about the vector v
Affine rotate(float t, const Vector & v)
{


	Affine temp;
	Matrix Icos;
	Matrix uut;
	Matrix Au;
	Matrix Result;
	float frontuut  = (1-cos(t))/ ((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
	float frontAu = (sin(t)) / (abs(v)) ;
	Icos.row[0].x = 1 * cos(t);
	Icos.row[0].y = 0;
	Icos.row[0].z = 0;

	Icos.row[1].x = 0;
	Icos.row[1].y = 1*cos(t);
	Icos.row[1].z = 0;

	Icos.row[2].x = 0;
	Icos.row[2].y = 0;
	Icos.row[2].z = 1* cos(t);

	uut.row[0].x = (v.x * v.x) * frontuut;
	uut.row[0].y = (v.x * v.y) * frontuut;
	uut.row[0].z = (v.x * v.z) * frontuut;

	uut.row[1].x = (v.y * v.x) * frontuut;
	uut.row[1].y = (v.y * v.y) * frontuut;
	uut.row[1].z = (v.y * v.z) * frontuut;

	uut.row[2].x = (v.z * v.x) * frontuut;
	uut.row[2].y = (v.z * v.y) * frontuut;
	uut.row[2].z = (v.z * v.z) * frontuut;

	Au.row[0].x = 0;
	Au.row[0].y = -(v.z * frontAu);
	Au.row[0].z = v.y * frontAu;

	Au.row[1].x = v.z * frontAu;
	Au.row[1].y = 0;
	Au.row[1].z = -(v.x* frontAu);

	Au.row[2].x = -(v.y * frontAu);
	Au.row[2].y = v.x * frontAu;
	Au.row[2].z = 0;
	
	
	for(int i =0; i<3; i++)
	{
		Result[i] = Icos.row[i] + uut.row[i] + Au.row[i];
	}
	Result.row[3].x = 0;
	Result.row[3].y = 0;
	Result.row[3].z = 0;
	Result.row[3].w = 1;
	return Result;
} 
//returns the affine transformation Tv  for translation by the vector v.
Affine translate(const Vector & v)
{
	Affine temp;
	temp.row[0].x = 1;
	temp.row[0].y = 0;
	temp.row[0].z = 0;
	temp.row[0].w = v.x;

	temp.row[1].x = 0;
	temp.row[1].y = 1;
	temp.row[1].z = 0;
	temp.row[1].w = v.y;

	temp.row[2].x = 0;
	temp.row[2].y = 0;
	temp.row[2].z = 1;
	temp.row[2].w = v.z;
	
	temp.row[3].x = 0;
	temp.row[3].y = 0;
	temp.row[3].z = 0;
	temp.row[3].w = 1;
	
	return temp;
}
//returns the affine transformation Hr for uniform scaling by r with respect to the origin.
Affine scale(float r)
{
	Affine temp;
	temp.row[0].x = r;
	temp.row[0].y = 0;
	temp.row[0].z = 0;
	temp.row[0].w = 0;

	temp.row[1].x = 0;
	temp.row[1].y = r;
	temp.row[1].z = 0;
	temp.row[1].w =0;

	temp.row[2].x = 0;
	temp.row[2].y = 0;
	temp.row[2].z = r;
	temp.row[2].w = 0;

	temp.row[3].x = 0;
	temp.row[3].y = 0;
	temp.row[3].z = 0;
	temp.row[3].w = 1;

	return temp;
}
// returns the affine transformation Hrx,ry,rz for inhomogeneous scaling by factors rx,ry,rz with respect to the origin.
Affine scale(float rx, float ry, float rz)
{
	Affine temp;
	temp.row[0].x = rx;
	temp.row[0].y = 0;
	temp.row[0].z = 0;
	temp.row[0].w = 0;

	temp.row[1].x = 0;
	temp.row[1].y = ry;
	temp.row[1].z = 0;
	temp.row[1].w = 0;

	temp.row[2].x = 0;
	temp.row[2].y = 0;
	temp.row[2].z = rz;
	temp.row[2].w = 0;

	temp.row[3].x = 0;
	temp.row[3].y = 0;
	temp.row[3].z = 0;
	temp.row[3].w = 1;

	return temp;
}
// returns the inverse A^−1 of the affine transformation A.
Affine inverse(const Affine & A)
{
	Affine inverse;
	Affine L;
	Affine M;
	Affine C;
	Affine Linverse;
	Affine T;
	Point V;
	float D;
	V.x = A.row[0].w;
	V.y = A.row[1].w;
	V.z = A.row[2].w;
	
	L.row[0].x = A.row[0].x;
	L.row[0].y = A.row[0].y;
	L.row[0].z = A.row[0].z;

	L.row[1].x = A.row[1].x;
	L.row[1].y = A.row[1].y;
	L.row[1].z = A.row[1].z;

	L.row[2].x = A.row[2].x;
	L.row[2].y = A.row[2].y;
	L.row[2].z = A.row[2].z;

	M.row[0].x = (L.row[1].y * L.row[2].z )- (L.row[1].z * L.row[2].y);
	M.row[0].y = (L.row[1].x * L.row[2].z) - (L.row[1].z * L.row[2].x);
	M.row[0].z = (L.row[1].x * L.row[2].y) - (L.row[1].y * L.row[2].x);

	M.row[1].x = (L.row[0].y * L.row[2].z) - (L.row[0].z * L.row[2].y);
	M.row[1].y = (L.row[0].x * L.row[2].z) - (L.row[0].z * L.row[2].x);
	M.row[1].z = (L.row[0].x * L.row[2].y) - (L.row[0].y * L.row[2].x);

	M.row[2].x = (L.row[0].y * L.row[1].z) - (L.row[0].z * L.row[1].y);
	M.row[2].y = (L.row[0].x * L.row[1].z) - (L.row[0].z * L.row[1].x);
	M.row[2].z = (L.row[0].x * L.row[1].y) - (L.row[0].y * L.row[1].x);

	C.row[0].x = M.row[0].x;
	C.row[0].y = -M.row[0].y;
	C.row[0].z = M.row[0].z;

	C.row[1].x = -M.row[1].x;
	C.row[1].y = M.row[1].y;
	C.row[1].z = -M.row[1].z;

	C.row[2].x = M.row[2].x;
	C.row[2].y = -M.row[2].y;
	C.row[2].z = M.row[2].z;

	Linverse.row[0].x = C.row[0].x;
	Linverse.row[0].y = C.row[1].x;
	Linverse.row[0].z = C.row[2].x;

	Linverse.row[1].x = C.row[0].y;
	Linverse.row[1].y = C.row[1].y;
	Linverse.row[1].z = C.row[2].y;

	Linverse.row[2].x = C.row[0].z ;
	Linverse.row[2].y = C.row[1].z;
	Linverse.row[2].z = C.row[2].z;

	D = (L.row[0].x * C.row[0].x) +
		(L.row[1].x * C.row[1].x) +
		(L.row[2].x * C.row[2].x);
	
	
	inverse.row[0].x = (1 / D)*C.row[0].x;
	inverse.row[0].y = (1 / D)*C.row[1].x;
	inverse.row[0].z = (1 / D)*C.row[2].x;
	inverse.row[0].w = 0;

	inverse.row[1].x = (1 / D)*C.row[0].y;
	inverse.row[1].y = (1 / D)* C.row[1].y;
	inverse.row[1].z = (1 / D)*C.row[2].y;
	inverse.row[1].w = 0;

	inverse.row[2].x = (1 / D)*C.row[0].z;
	inverse.row[2].y = (1 / D)*C.row[1].z;
	inverse.row[2].z = (1 / D)*C.row[2].z;
	inverse.row[2].w = 0;

	inverse.row[3].x = 0;
	inverse.row[3].y = 0;
	inverse.row[3].z = 0;
	inverse.row[3].w = 1;



	T.row[0].x = 1;
	T.row[0].y = 0;
	T.row[0].z = 0;
	T.row[0].w = -V.x;

	T.row[1].x = 0;
	T.row[1].y = 1;
	T.row[1].z = 0;
	T.row[1].w = -V.y;

	T.row[2].x = 0;
	T.row[2].y = 0;
	T.row[2].z = 1;
	T.row[2].w =- V.z;

	T.row[3].x = 0;
	T.row[3].y = 0;
	T.row[3].z = 0;
	T.row[3].w = 1;




	return inverse * T;
}
