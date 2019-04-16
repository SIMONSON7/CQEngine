#include "CQMemory.h"
#include "CQMesh.h"
#include "CQSceneNode.h"
#include "CQMeshRenderer.h"
#include "CQPlane.h"

USING_NS_CQ

CQPlane::CQPlane()
{
	
}

CQPlane::~CQPlane()
{

}

void CQPlane::setupGeometry(CQMesh * _mesh)
{
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>
		(node_->getObj()->getComponentByName("MeshRender")).get();

	mr->setup(_mesh);
}

void CQPlane::setupSurface(CQMaterial * _mat)
{
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>
		(node_->getObj()->getComponentByName("MeshRender")).get();

	auto matList = CQ_NEW(std::vector<CQMaterial*>);
	matList->push_back(_mat);
	mr->setup(nullptr, nullptr, matList);
}

SubMesh * CQPlane::__genGeoData(float xsize, float zsize, int xdivs, int zdivs, float smax, float tmax)
{
	SubMesh * mesh = CQ_NEW(SubMesh);
	std::vector<Vertex>			verList((xdivs + 1) * (zdivs + 1));
	std::vector<unsigned int>	idxList(6 * xdivs * zdivs);

	float x2 = xsize / 2.0f;
	float z2 = zsize / 2.0f;
	float iFactor = (float)zsize / zdivs;
	float jFactor = (float)xsize / xdivs;
	float texi = smax / zdivs;
	float texj = tmax / xdivs;
	float x, z;
	int vidx = 0;
	for (int i = 0; i <= zdivs; i++) 
	{
		z = iFactor * i - z2;
		for (int j = 0; j <= xdivs; j++) 
		{
			x = jFactor * j - x2;

			verList[vidx].pos_.x = x;
			verList[vidx].pos_.y = 0.0f;
			verList[vidx].pos_.z = z;

			verList[vidx].normal_.x = 0.0f;
			verList[vidx].normal_.y = 1.0f;
			verList[vidx].normal_.z = 0.0f;

			verList[vidx].uv_.x = j * texi;
			verList[vidx].uv_.y = i * texj;

			vidx += 1;
		}
	}

	unsigned rowStart, nextRowStart;
	int idx = 0;
	for (int i = 0; i < zdivs; i++) 
	{
		rowStart = (unsigned)(i * (xdivs + 1));
		nextRowStart = (unsigned)((i + 1) * (xdivs + 1));
		for (int j = 0; j < xdivs; j++) 
		{
			idxList[idx] = rowStart + j;
			idxList[idx + 1] = nextRowStart + j;
			idxList[idx + 2] = nextRowStart + j + 1;
			idxList[idx + 3] = rowStart + j;
			idxList[idx + 4] = nextRowStart + j + 1;
			idxList[idx + 5] = rowStart + j + 1;

			idx += 6;
		}
	}

	mesh->vBuff_ = verList;
	mesh->iBuff_ = idxList;
	return mesh;
}



