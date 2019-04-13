#include "CQMemory.h"
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
	//std::vector<GLfloat> p(3 * (xdivs + 1) * (zdivs + 1));
	//std::vector<GLfloat> n(3 * (xdivs + 1) * (zdivs + 1));
	//std::vector<GLfloat> tex(2 * (xdivs + 1) * (zdivs + 1));
	//std::vector<GLuint> el(6 * xdivs * zdivs);

	//float x2 = xsize / 2.0f;
	//float z2 = zsize / 2.0f;
	//float iFactor = (float)zsize / zdivs;
	//float jFactor = (float)xsize / xdivs;
	//float texi = smax / zdivs;
	//float texj = tmax / xdivs;
	//float x, z;
	//int vidx = 0, tidx = 0;
	//for (int i = 0; i <= zdivs; i++) {
	//	z = iFactor * i - z2;
	//	for (int j = 0; j <= xdivs; j++) {
	//		x = jFactor * j - x2;
	//		p[vidx] = x;
	//		p[vidx + 1] = 0.0f;
	//		p[vidx + 2] = z;
	//		n[vidx] = 0.0f;
	//		n[vidx + 1] = 1.0f;
	//		n[vidx + 2] = 0.0f;

	//		tex[tidx] = j * texi;
	//		tex[tidx + 1] = i * texj;

	//		vidx += 3;
	//		tidx += 2;
	//	}
	//}

	//GLuint rowStart, nextRowStart;
	//int idx = 0;
	//for (int i = 0; i < zdivs; i++) {
	//	rowStart = (GLuint)(i * (xdivs + 1));
	//	nextRowStart = (GLuint)((i + 1) * (xdivs + 1));
	//	for (int j = 0; j < xdivs; j++) {
	//		el[idx] = rowStart + j;
	//		el[idx + 1] = nextRowStart + j;
	//		el[idx + 2] = nextRowStart + j + 1;
	//		el[idx + 3] = rowStart + j;
	//		el[idx + 4] = nextRowStart + j + 1;
	//		el[idx + 5] = rowStart + j + 1;
	//		idx += 6;
	//	}
	//}

	//std::cout << " END " << std::endl;

	////initBuffers(&el, &p, &n, &tex);

	return nullptr;
}



