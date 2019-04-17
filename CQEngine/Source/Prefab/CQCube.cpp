#include "CQMemory.h"
#include "CQMesh.h"
#include "CQSceneNode.h"
#include "CQMeshRenderer.h"
#include "CQCube.h"

USING_NS_CQ

CQCube::CQCube()
{

}

CQCube::~CQCube()
{

}

SubMesh * CQCube::genGeoData(float _side)
{
	SubMesh * mesh = CQ_NEW(SubMesh);
	std::vector<Vertex>			verList(24);	// 4 * 6
	std::vector<unsigned int>	idxList(36);

	float side2 = _side / 2.0f;
	// Front
	verList[0].pos_ = { -side2, -side2, side2 };
	verList[1].pos_ = { side2, -side2, side2 };
	verList[2].pos_ = { side2,  side2, side2 };
	verList[3].pos_ = { -side2,  side2, side2 };
	// Right
	verList[4].pos_ = { side2, -side2, side2 };
	verList[5].pos_ = { side2, -side2, -side2 };
	verList[6].pos_ = { side2,  side2, -side2 };
	verList[7].pos_ = { side2,  side2, side2 };
	// Back
	verList[8].pos_ = { -side2, -side2, -side2 };
	verList[9].pos_ = { -side2,  side2, -side2 };
	verList[10].pos_ = { side2,  side2, -side2 };
	verList[11].pos_ = { side2, -side2, -side2 };
	// Left
	verList[12].pos_ = { -side2, -side2, side2 };
	verList[13].pos_ = { -side2,  side2, side2 };
	verList[14].pos_ = { -side2,  side2, -side2 };
	verList[15].pos_ = { -side2, -side2, -side2 };
	// Bottom
	verList[16].pos_ = { -side2, -side2, side2 };
	verList[17].pos_ = { -side2, -side2, -side2 };
	verList[18].pos_ = { side2, -side2, -side2 };
	verList[19].pos_ = { side2, -side2, side2 };
	// Top
	verList[20].pos_ = { -side2,  side2, side2 };
	verList[21].pos_ = { side2,  side2, side2 };
	verList[22].pos_ = { side2,  side2, -side2 };
	verList[23].pos_ = { -side2,  side2, -side2 };

	// Front
	verList[0].normal_ = { 0.0f, 0.0f, 1.0f };
	verList[1].normal_ = { 0.0f, 0.0f, 1.0f };
	verList[2].normal_ = { 0.0f, 0.0f, 1.0f };
	verList[3].normal_ = { 0.0f, 0.0f, 1.0f };
	// Right
	verList[4].normal_ = { 1.0f, 0.0f, 0.0f };
	verList[5].normal_ = { 1.0f, 0.0f, 0.0f };
	verList[6].normal_ = { 1.0f, 0.0f, 0.0f };
	verList[7].normal_ = { 1.0f, 0.0f, 0.0f };
	// Back
	verList[8].normal_ = { 0.0f, 0.0f, -1.0f };
	verList[9].normal_ = { 0.0f, 0.0f, -1.0f };
	verList[10].normal_ = { 0.0f, 0.0f, -1.0f };
	verList[11].normal_ = { 0.0f, 0.0f, -1.0f };
	// Left
	verList[12].normal_ = { -1.0f, 0.0f, 0.0f };
	verList[13].normal_ = { -1.0f, 0.0f, 0.0f };
	verList[14].normal_ = { -1.0f, 0.0f, 0.0f };
	verList[15].normal_ = { -1.0f, 0.0f, 0.0f };
	// Bottom
	verList[16].normal_ = { 0.0f, -1.0f, 0.0f };
	verList[17].normal_ = { 0.0f, -1.0f, 0.0f };
	verList[18].normal_ = { 0.0f, -1.0f, 0.0f };
	verList[19].normal_ = { 0.0f, -1.0f, 0.0f };
	// Top
	verList[20].normal_ = { 0.0f, 1.0f, 0.0f };
	verList[21].normal_ = { 0.0f, 1.0f, 0.0f };
	verList[22].normal_ = { 0.0f, 1.0f, 0.0f };
	verList[23].normal_ = { 0.0f, 1.0f, 0.0f };

	// Front
	verList[0].uv_ = { 0.0f, 0.0f };
	verList[1].uv_ = { 1.0f, 0.0f };
	verList[2].uv_ = { 1.0f, 1.0f };
	verList[3].uv_ = { 0.0f, 1.0f };
	// Right
	verList[4].uv_ = { 0.0f, 0.0f };
	verList[5].uv_ = { 1.0f, 0.0f };
	verList[6].uv_ = { 1.0f, 1.0f };
	verList[7].uv_ = { 0.0f, 1.0f };
	// Back
	verList[8].uv_ = { 0.0f, 0.0f };
	verList[9].uv_ = { 1.0f, 0.0f };
	verList[10].uv_ = { 1.0f, 1.0f };
	verList[11].uv_ = { 0.0f, 1.0f };
	// Left
	verList[12].uv_ = { 0.0f, 0.0f };
	verList[13].uv_ = { 1.0f, 0.0f };
	verList[14].uv_ = { 1.0f, 1.0f };
	verList[15].uv_ = { 0.0f, 1.0f };
	// Bottom
	verList[16].uv_ = { 0.0f, 0.0f };
	verList[17].uv_ = { 1.0f, 0.0f };
	verList[18].uv_ = { 1.0f, 1.0f };
	verList[19].uv_ = { 0.0f, 1.0f };
	// Top
	verList[20].uv_ = { 0.0f, 0.0f };
	verList[21].uv_ = { 1.0f, 0.0f };
	verList[22].uv_ = { 1.0f, 1.0f };
	verList[23].uv_ = { 0.0f, 1.0f };

	idxList = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};

	return mesh;
}