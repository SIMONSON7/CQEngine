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

SubMesh * CQPlane::genGeoData(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax, float _tmax)
{
	SubMesh * mesh = CQ_NEW(SubMesh);
	std::vector<Vertex>			verList((_xdivs + 1) * (_zdivs + 1));
	std::vector<unsigned int>	idxList(6 * _xdivs * _zdivs);

	float x2 = _xsize / 2.0f;
	float z2 = _zsize / 2.0f;
	float iFactor = (float)_zsize / _zdivs;
	float jFactor = (float)_xsize / _xdivs;
	float texi = _smax / _zdivs;
	float texj = _tmax / _xdivs;
	float x, z;
	int vidx = 0;
	for (int i = 0; i <= _zdivs; i++) 
	{
		z = iFactor * i - z2;
		for (int j = 0; j <= _xdivs; j++) 
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
	for (int i = 0; i < _zdivs; i++) 
	{
		rowStart = (unsigned)(i * (_xdivs + 1));
		nextRowStart = (unsigned)((i + 1) * (_xdivs + 1));
		for (int j = 0; j < _xdivs; j++) 
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



