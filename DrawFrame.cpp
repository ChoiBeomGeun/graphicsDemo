/*
\author      name : BeomGeun Choi
\par         the assignment number : Project 1
\par         the course name : CS250
\par         the term : Spring 2018

*/

#include "DrawFrame.h"
#include "Affine.h"
#include "Mesh.h"
#include "CubeMesh.h"
#include "Camera.h"
#include  "Projection.h"
#include  "Raster.h"
#include "RasterUtilities.h"
#include "HalfSpace.h"
#include  "Clip.h"
#include  "SnubDodecMesh.h"

#include <vector>
#include <random>
#include <thread>
using namespace std;


random_device Random_device;
mt19937 Gen(Random_device());
uniform_int_distribution<int> dist_(-2, 2);
uniform_int_distribution<int> Rotationdist_(0, 360);
uniform_int_distribution<int> fdist_(1, 3);
class Humanoid : public Mesh
{
public:
	int VertexCount(void) { return 64; }
	Point GetVertex(int i) { return vertices[i]; }
	Vector Dimensions(void) { return Vector(2, 2, 2); }
	Point Center(void) { return Point(0, 0, 0); }
	int FaceCount(void) { return 96; }
	Face GetFace(int i) { return faces[i]; }
	int EdgeCount(void) { return 6; }
	Edge GetEdge(int i) { return edges[i]; }

	Point vertices[64] = {
		Point(3.25000f, -2.48000f, 14.0000f),      Point(3.25000f, -2.48000f, 9.01000f),
		Point(3.25000f, 2.48000f, 9.01000f),      Point(3.25000f, 2.48000f, 14.0000f),
		Point(0.773000f, -2.4800f, 14.000f),      Point(0.773000f, -2.4800f, 9.0100f),
		Point(0.773000f, 2.48000f, 14.0000f),      Point(0.773000f, 2.48000f, 9.01000f),
		Point(3.47000f, -1.29000f, 17.4000f),      Point(3.47000f, -1.29000f, 15.0000f),
		Point(3.47000f, 1.19000f, 15.0000f),      Point(3.47000f, 1.19000f, 17.4000f),
		Point(0.601000f, -1.2900f, 17.400f),      Point(0.601000f, -1.2900f, 15.000f),
		Point(0.601000f, 1.19000f, 17.4000f),      Point(0.601000f, 1.19000f, 15.0000f),
		Point(3.15000f, -2.47000f, 8.01000f),      Point(3.15000f, -2.47000f, 3.05000f),
		Point(3.15000f, -0.48600f, 3.0500f),      Point(3.15000f, -0.48600f, 8.0100f),
		Point(0.892000f, -2.4700f, 8.0100f),      Point(0.892000f, -2.4700f, 3.0500f),
		Point(0.892000f, -0.4860f, 8.0100f),      Point(0.892000f, -0.4860f, 3.050f),
		Point(3.23000f, -3.96000f, 14.0000f),      Point(3.23000f, -3.96000f, 9.01000f),
		Point(3.23000f, -2.48000f, 9.01000f),      Point(3.23000f, -2.48000f, 14.0000f),
		Point(0.747000f, -3.9600f, 14.000f),      Point(0.747000f, -3.9600f, 9.0100f),
		Point(0.747000f, -2.4800f, 14.000f),      Point(0.747000f, -2.4800f, 9.0100f),
		Point(3.27000f, 2.46000f, 14.0000f),      Point(3.27000f, 2.46000f, 9.01000f),
		Point(3.27000f, 3.95000f, 9.01000f),      Point(3.27000f, 3.95000f, 14.0000f),
		Point(0.795000f, 2.46000f, 14.0000f),      Point(0.795000f, 2.46000f, 9.01000f),
		Point(0.795000f, 3.95000f, 14.0000f),      Point(0.795000f, 3.95000f, 9.01000f),
		Point(2.49000f, -0.49800f, 15.000f),      Point(2.49000f, -0.49800f, 14.000f),
		Point(2.49000f, 0.493000f, 14.0000f),      Point(2.49000f, 0.493000f, 15.0000f),
		Point(1.50000f, -0.49800f, 15.000f),      Point(1.50000f, -0.49800f, 14.000f),
		Point(1.50000f, 0.493000f, 15.0000f),      Point(1.50000f, 0.493000f, 14.0000f),
		Point(3.25000f, -2.50000f, 9.01000f),      Point(3.25000f, -2.50000f, 8.01000f),
		Point(3.25000f, 2.45000f, 8.01000f),      Point(3.25000f, 2.45000f, 9.01000f),
		Point(0.771000f, -2.5000f, 9.0100f),      Point(0.771000f, -2.5000f, 8.0100f),
		Point(0.771000f, 2.45000f, 9.01000f),      Point(0.771000f, 2.45000f, 8.01000f),
		Point(3.27000f, 0.465000f, 8.01000f),      Point(3.27000f, 0.465000f, 3.05000f),
		Point(3.27000f, 2.45000f, 3.05000f),      Point(3.27000f, 2.45000f, 8.01000f),
		Point(0.795000f, 0.46500f, 8.0100f),      Point(0.795000f, 0.46500f, 3.0500f),
		Point(0.795000f, 2.45000f, 8.01000f),      Point(0.795000f, 2.45000f, 3.05000f)
	};
	Face faces[96] =
	{
		Face(1 - 1, 2 - 1, 3 - 1),      Face(1 - 1, 3 - 1, 4 - 1),      Face(5 - 1, 6 - 1, 2 - 1),
		Face(5 - 1, 2 - 1, 1 - 1),      Face(7 - 1, 8 - 1, 6 - 1),      Face(7 - 1, 6 - 1, 5 - 1),
		Face(4 - 1, 3 - 1, 8 - 1),      Face(4 - 1, 8 - 1, 7 - 1),      Face(7 - 1, 5 - 1, 1 - 1),
		Face(7 - 1, 1 - 1, 4 - 1),      Face(2 - 1, 6 - 1, 8 - 1),      Face(2 - 1, 8 - 1, 3 - 1),
		Face(9 - 1, 10 - 1, 11 - 1),      Face(9 - 1, 11 - 1, 12 - 1),      Face(13 - 1, 14 - 1, 10 - 1),
		Face(13 - 1, 10 - 1, 9 - 1),      Face(15 - 1, 16 - 1, 14 - 1),      Face(15 - 1, 14 - 1, 13 - 1),
		Face(12 - 1, 11 - 1, 16 - 1),      Face(12 - 1, 16 - 1, 15 - 1),      Face(15 - 1, 13 - 1,9 - 1),
		Face(15 - 1, 9 - 1, 12 - 1),      Face(10 - 1, 14 - 1, 16 - 1),      Face(10 - 1, 16 - 1, 11 - 1),
		Face(17 - 1, 18 - 1, 19 - 1),      Face(17 - 1, 19 - 1, 20 - 1),      Face(21 - 1, 22 - 1, 18 - 1),
		Face(21 - 1, 18 - 1, 17 - 1),      Face(23 - 1, 24 - 1, 22 - 1),      Face(23 - 1, 22 - 1, 21 - 1),
		Face(20 - 1, 19 - 1, 24 - 1),      Face(20 - 1, 24 - 1, 23 - 1),      Face(23 - 1, 21 - 1, 17 - 1),
		Face(23 - 1, 17 - 1, 20 - 1),      Face(18 - 1, 22 - 1, 24 - 1),      Face(18 - 1, 24 - 1, 19 - 1),
		Face(25 - 1, 26 - 1, 27 - 1),      Face(25 - 1, 27 - 1, 28 - 1),      Face(29 - 1, 30 - 1, 26 - 1),
		Face(29 - 1, 26 - 1, 25 - 1),      Face(31 - 1, 32 - 1, 30 - 1),      Face(31 - 1, 30 - 1, 29 - 1),
		Face(28 - 1, 27 - 1, 32 - 1),      Face(28 - 1, 32 - 1, 31 - 1),      Face(31 - 1, 29 - 1, 25 - 1),
		Face(31 - 1, 25 - 1, 28 - 1),      Face(26 - 1, 30 - 1, 32 - 1),      Face(26 - 1, 32 - 1, 27 - 1),
		Face(33 - 1, 34 - 1, 35 - 1),      Face(33 - 1, 35 - 1, 36 - 1),      Face(37 - 1, 38 - 1, 34 - 1),
		Face(37 - 1, 34 - 1, 33 - 1),      Face(39 - 1, 40 - 1, 38 - 1),      Face(39 - 1, 38 - 1, 37 - 1),
		Face(36 - 1, 35 - 1, 40 - 1),      Face(36 - 1, 40 - 1, 39 - 1),      Face(39 - 1, 37 - 1, 33 - 1),
		Face(39 - 1, 33 - 1, 36 - 1),      Face(34 - 1, 38 - 1, 40 - 1),      Face(34 - 1, 40 - 1, 35 - 1),
		Face(41 - 1, 42 - 1, 43 - 1),      Face(41 - 1, 43 - 1, 44 - 1),      Face(45 - 1, 46 - 1, 42 - 1),
		Face(45 - 1, 42 - 1, 41 - 1),      Face(47 - 1, 48 - 1, 46 - 1),      Face(47 - 1, 46 - 1, 45 - 1),
		Face(44 - 1, 43 - 1, 48 - 1),      Face(44 - 1, 48 - 1, 47 - 1),      Face(47 - 1, 45 - 1, 41 - 1),
		Face(47 - 1, 41 - 1, 44 - 1),      Face(42 - 1, 46 - 1, 48 - 1),      Face(42 - 1, 48 - 1, 43 - 1),
		Face(49 - 1, 50 - 1, 51 - 1),      Face(49 - 1, 51 - 1, 52 - 1),      Face(53 - 1, 54 - 1, 50 - 1),
		Face(53 - 1, 50 - 1, 49 - 1),      Face(55 - 1, 56 - 1, 54 - 1),      Face(55 - 1, 54 - 1, 53 - 1),
		Face(52 - 1, 51 - 1, 56 - 1),      Face(52 - 1, 56 - 1, 55 - 1),      Face(55 - 1, 53 - 1, 49 - 1),
		Face(55 - 1, 49 - 1, 52 - 1),      Face(50 - 1, 54 - 1, 56 - 1),      Face(50 - 1, 56 - 1, 51 - 1),
		Face(57 - 1, 58 - 1, 59 - 1),      Face(57 - 1, 59 - 1, 60 - 1),      Face(61 - 1, 62 - 1, 58 - 1),
		Face(61 - 1, 58 - 1, 57 - 1),      Face(63 - 1, 64 - 1, 62 - 1),      Face(63 - 1, 62 - 1, 61 - 1),
		Face(60 - 1, 59 - 1, 64 - 1),      Face(60 - 1, 64 - 1, 63 - 1),      Face(63 - 1, 61 - 1, 57 - 1),
		Face(63 - 1, 57 - 1, 60 - 1),      Face(58 - 1, 62 - 1, 64 - 1),      Face(58 - 1, 64 - 1, 59 - 1)
	};
	Edge edges[6] = { Edge(0,1), Edge(0,2), Edge(0,3),
		Edge(1,3), Edge(1,2), Edge(2,3)
	};
};
class HeartMesh : public Mesh
{
public:
	int VertexCount(void) override { return 20; }
	Point GetVertex(int i) override { return vertices[i]; }
	Vector Dimensions(void) override { return Vector(0, 0, 0); }
	Point Center(void) override { return Point(0, 0, 0); }
	int FaceCount(void) override { return 35; }
	Face GetFace(int i) override { return faces[i]; }
	int EdgeCount(void) override { return 0; }
	Edge GetEdge(int i) override { return Edge(i, 0); }
private:
	const Point vertices[20]{
		Point(-0.1184881f ,-0.01023257f, -0.0416434f),
		Point(-0.05646208f, 0.01369846f, -0.05925572f),
		Point(-0.1207125f, 0.07951081f, -0.03522691f),
		Point(0.1206389f, -0.01093817f, 0.05112677f),
		Point(-0.1194581f, -0.01667452f, 0.04812055f),
		Point(-0.1216826f, 0.07306886f, 0.05453705f),
		Point(-0.001634081f, 0.07593703f, 0.05604018f),
		Point(0.1184144f, 0.07880521f, 0.05754327f),
		Point(0.0105904f, -0.1338063f, 0.03962369f),
		Point(0.01156042f, -0.1273644f, -0.05014032f),
		Point(-0.06068832f, 0.1309448f, -0.02447538f),
		Point(-0.06165837f, 0.1245029f, 0.06528863f),
		Point(0.1216089f, -0.004496217f, -0.03863716f),
		Point(0.1193845f, 0.08524716f, -0.03222068f),
		Point(0.06358649f, 0.01656663f, -0.05775261f),
		Point(0.005563954f, 0.03762949f, -0.06686808f),
		Point(0.00305659f, 0.08211827f, -0.04177955f),
		Point(0.05936022f, 0.133813f, -0.02297227f),
		Point(0.05839021f, 0.1273711f, 0.06679174f),
		Point(0.00856219f, -0.0448674f, -0.06350422f)
	};
	const Face faces[36]{
		Face(2 ,1, 0),	 Face(5 ,4, 3),	 Face(6 ,5, 3),
		Face(7 ,6, 3), Face(8 ,4, 0), Face(9, 8, 0),
		Face(11, 10, 2), Face(5 ,11, 2),Face(5 ,2, 0),
		Face(4 ,5, 0),Face(7 ,3, 12), Face(13, 7, 12),
		Face(14, 13, 12),Face(16, 13,15),Face(1 ,9, 0),
		Face(6 ,18, 17),Face(11, 6, 10),Face(7 ,13, 17),
		Face(18, 7, 17),Face(16, 17, 13), Face(7 ,18, 6),
		Face(2 ,10, 16),Face(6 ,11, 5),Face(12, 3, 8),
		Face(9, 12, 8), Face(4 ,8, 3), Face(19, 14, 9),
		Face(14, 12, 9), Face(1 ,19, 9), Face(1 ,15, 19),
		Face(19, 15, 14), Face(2 ,15, 1), Face(14, 15, 13),
		Face(2 ,16, 15), Face(17, 16, 6),Face(6 ,16, 10)
	};
};
HeartMesh  heart_mesh;
Humanoid human_mesh;
std::vector<Point> world_verts;
std::vector<Hcoord> clip_verts;
std::vector<Camera> cameras;
const Vector LIGHT(0, 0, 1),
EX(1, 0, 0),
EY(0, 1, 0),
EZ(0, 0, 1),
ZERO(0, 0, 0);
Matrix world_to_ndc[3];
const float PI = 4.0f*atan(1.0f);
const Point O(0, 0, 0);
CubeMesh cube;
SnubDodecMesh snub_mesh;
Affine EarthAffine;
Affine CameraObject;
std::vector<Point> cam_vertices;
std::vector<Point> ndc_vertices;
Vector snub_rot_axis = Vector(0, 1, 0);
std::vector<Affine> OrbitingObjectsAffine;

std::vector<Affine> HeartAffine;
std::vector<Affine> HumanAffine;
Point cameara_center;
Point DynamicCameraPos = Point{ 0,0,0 };
Point DynamicHUmanPos = Point{ 0,0,0 };
std::vector<Affine> BaseCubeAffine;
const float snub_rot_rate = 2 * PI / 10.0f; 


Affine ndc_to_dev;
float radius = 1.5f;
float t = 0;
 const Vector WHITE(255, 255, 255),
	 PURPLE(255, 0, 255),
	 BLACK(0, 0, 0),
	 RED(255, 0, 0),
	 GREEN(0,  255, 0),
	 SKYBLUE(0.329f*255, 0.972f * 255, 0.949f * 255),
	 PRETTYPINK(0.937f * 255, 0.662f * 255, 0.870f * 255),
	 NAVY(0.231f * 255, 0.290f * 255, 0.890f * 255),
	 SUN(0.980f * 255, 0.541f * 255, 0);
 Point snub_center = Point(0, 0, -2);
 void DisplayClippedFaces(Mesh& mesh, const Affine& obj_to_world,
	 const Vector& clr, Raster & r, int camnum);
void InitFrame(int width, int height)
{
	ndc_to_dev = translate(Vector(-0.5f, -0.5f, 0))
		* scale(0.5f * width, 0.5f * height, 1)
		* translate(Vector(1, 1, 0));

	for (int i = 0; i < 15; ++i)
	{

		BaseCubeAffine.push_back(translate(Vector((i % 3) - 1.f, -1.1f, -(i / 3) - 1.f))
			* scale(0.375f, 0.05f, 0.375f));

		BaseCubeAffine.push_back(translate(Vector((i % 3) + 1.f, -1.1f, -(i / 3) - 1.f))
			* scale(0.375f , 0.05f , 0.375f));


		BaseCubeAffine.push_back(translate(Vector((i % 3) - 4.f, -1.1f, -(i / 3) - 1.f))
			* scale(0.375f , 0.05f , 0.375f ));

		BaseCubeAffine.push_back(translate(Vector((i % 3) + 1.f, -1.1f, -(i / 3) + 3.f))
			* scale(0.375f, 0.05f, 0.375f));


		BaseCubeAffine.push_back(translate(Vector((i % 3) - 4.f, -1.1f, -(i / 3) + 3.f))
			* scale(0.375f, 0.05f, 0.375f));


		BaseCubeAffine.push_back(translate(Vector((i % 3) - 1.f, -1.1f, -(i / 3) + 3.f))
			* scale(0.375f, 0.05f, 0.375f));
		HeartAffine.push_back(translate(Vector(static_cast<float>(dist_(Gen)), static_cast<float>(dist_(Gen)) + 2.f,
			static_cast<float>(dist_(Gen))))*
			scale(static_cast<float>(fdist_(Gen)), static_cast<float>(fdist_(Gen)), static_cast<float>(fdist_(Gen)))
			* rotate(snub_rot_rate, Vector(
				static_cast<float>(Rotationdist_(Gen)), static_cast<float>(Rotationdist_(Gen)), static_cast<float>(Rotationdist_(Gen)))));
	}

	cameras.push_back(Camera(Point(0, 0, 0) + Vector(0, 0, 1), -Vector(0, 0, 1), Vector(0, 1, 0), 0.5f*PI, 1, 0.01f, 10));
	cameras.push_back(Camera(Point(0, 0, 0) + Vector(0, 0, 1), -Vector(0, 0, 1), Vector(0, 1, 0), 0.5f*PI, 1, 0.01f, 10));
	cameras.push_back(Camera(Point(0, 0, 0) + Vector(0, 0, 1), -Vector(0, 0, 1), Vector(0, 1, 0), 0.5f*PI, 1, 0.01f, 10));

	EarthAffine = translate(snub_center - O);		
	CameraObject = translate(snub_center - O)*	scale(0.5f, 0.5f, 3.5f);

	for (int i = 0; i < 10; ++i)
	{
		HumanAffine.push_back(translate(snub_center - O));
	}

	for (int i = 0; i < 20; ++i)
		OrbitingObjectsAffine.push_back(translate(Vector(snub_center - O))*(translate(
			Vector(radius*static_cast<float>(cos(i)), 0.f
				, radius*static_cast<float>(sin(i)))))* scale(0.05f, 0.05f, 0.05f));
	//for (int i = 0; i < 3; ++i)
	//	world_to_ndc[i] = CameraToNDC(cameras[i]) * WorldToCamera(cameras[i]);		
}

void DrawFrame(Raster & r, double dt, int cam_num)
{


	for (int i = 0; i < 3; ++i)
		world_to_ndc[i] = CameraToNDC(cameras[i]) * WorldToCamera(cameras[i]);
	r.SetColor(255, 255, 255);
	ClearBuffers(r);
	





	if (t >= 360)
		t = 0;
	t += static_cast<float>(dt);


	for (int i = 0; i < 20; ++i)
		OrbitingObjectsAffine[i] = translate(Vector(snub_center - O))
		*(translate(Vector(radius*cos(t + i * PI*0.1f), 0, radius*sin(t + i * PI*0.1f))))
		* rotate(-t - i * PI*0.1f + PI * 0.5f, Vector(0, 1, 0))
		* scale(1.5f, 1.5f, 1.5f);

	EarthAffine = translate(snub_center - O)
		* rotate(snub_rot_rate*static_cast<float>(dt), snub_rot_axis)
		* translate(O - snub_center)
		* EarthAffine;

	cameara_center = DynamicCameraPos;

	DynamicCameraPos = Point(
		(4 + sin(2 * PI / 25 * t))*sin(PI / 4 * (2 + sin(2 * PI / 35 * t)))*cos(PI*(1 + sin(2 * PI / 35 * t))),
		(4 + sin(2 * PI / 25 * t))*cos(PI / 4 * (2 + sin(2 * PI / 35 * t))),
		(4 + sin(2 * PI / 25 * t))*sin(PI / 4 * (2 + sin(2 * PI / 35 * t)))*sin(PI*(1 + sin(2 * PI / 35 * t)))
	);

	DynamicHUmanPos = Point(sin(PI*t * 5 / 10 + PI), sin(PI*t * 5 / 15 - PI / 2), sin(PI*t * 5 / 20));
	for (int i = 0; i < 10; ++i)
		HumanAffine[i] = translate(Vector(snub_center - O))
		*(translate(Point(DynamicHUmanPos.x - i, DynamicHUmanPos.y, DynamicHUmanPos.z - i) - O))
		* rotate(-t - i * PI*0.05f + PI * 0.5f, Vector(0, 1, 0))
		*scale(0.05f, 0.05f, 0.05f);
	const Vector look = normalize(DynamicCameraPos - cameara_center);
	const Vector look_center = normalize(snub_center - DynamicCameraPos);






	Point cameraEye = translate(snub_center - O)*
		(DynamicCameraPos);





	const Vector right = normalize(-look_center);
	const Vector look_ = normalize(look);
	const Vector up = normalize(cross(look, right));




	cameras[1] = Camera(DynamicCameraPos + look_
		, look_,
		EY, 0.5f*PI, 1, 0.01f, 10);

	cameras[2] = Camera(cameraEye+ look_center
		, look_center,
		EY, 0.5f*PI, 1, 0.01f, 10);

	Affine newCameraObject = Affine(right, up, look, O);
	 CameraObject = translate(snub_center - O)*
		 translate(DynamicCameraPos - O)
		*newCameraObject
		*scale(.5f, .2f, .1f);


	for (auto bases : BaseCubeAffine)
	{

		DisplayClippedFaces(cube, bases, GREEN, r, cam_num);

	}
	for (auto aCubeAffine : BaseCubeAffine)
	{
		DisplayClippedFaces(cube, aCubeAffine, GREEN, r, cam_num);

	}
	for (auto aOrbitingAffine : OrbitingObjectsAffine)
	{
		DisplayClippedFaces(heart_mesh, aOrbitingAffine, NAVY, r, cam_num);

	}

	for (auto aHeartAffine : HeartAffine)
	{
		DisplayClippedFaces(heart_mesh, aHeartAffine, RED, r, cam_num);
	}
	for (auto aHumanAffine : HumanAffine)
	{
		DisplayClippedFaces(human_mesh, aHumanAffine, BLACK, r, cam_num);
	}
	DisplayClippedFaces(snub_mesh, EarthAffine, SUN, r, cam_num);

	DisplayClippedFaces(cube, CameraObject, SKYBLUE, r, cam_num);
}




void DisplayClippedFaces(Mesh& mesh, const Affine& obj_to_world,
	const Vector& clr, Raster & r, int camnum) {

	Clip cube_clip;
	Clip tclip = Clip(Polyhedron(true));
	world_verts.clear();
	for (int i = 0; i < mesh.VertexCount(); ++i)
		world_verts.push_back(obj_to_world * mesh.GetVertex(i));

	for (int i = 0; i < mesh.FaceCount(); ++i)
	{
		const Point &Pworld = world_verts[mesh.GetFace(i).index1],
			&Qworld = world_verts[mesh.GetFace(i).index2],
			&Rworld = world_verts[mesh.GetFace(i).index3];
		Hcoord Ptex(Pworld),
			Qtex(Qworld),
			Rtex(Rworld);
		clip_verts.clear();
		clip_verts.push_back(Ptex);
		clip_verts.push_back(Qtex);
		clip_verts.push_back(Rtex);
		if (cube_clip(clip_verts))
		{
			for (unsigned j = 0; j < clip_verts.size(); ++j)
			{
				const Hcoord& temp = clip_verts[j];
				Hcoord Pndc = world_to_ndc[camnum] * temp;
				clip_verts[j] = Hcoord(Pndc);
			}
			if (tclip(clip_verts))
			{
				Vector normal = cross(Qworld - Pworld, Rworld - Pworld);
				float mu = min(abs(dot(normal, cameras[camnum].Back())) / abs(normal) + 0.1f, 1.0f);
				r.SetColor(Raster::byte(mu * clr.x),
					Raster::byte(mu * clr.y),
					Raster::byte(mu * clr.z));
				for (unsigned k = 0; k < clip_verts.size(); ++k)
				{
					const Hcoord& Pndc = clip_verts[k];
					Hcoord Pdev = ndc_to_dev * Pndc;
					clip_verts[k] = Hcoord(Pdev);
				}
				for (unsigned k = 2; k < clip_verts.size(); ++k)
					FillTriangle(r, clip_verts[0], clip_verts[k - 1], clip_verts[k]);
			}
		}
	}
}