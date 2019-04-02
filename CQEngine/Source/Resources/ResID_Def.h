//*****************************************************************************
//
//! \file ResID_Def.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/25 04:54.pm
//
//*****************************************************************************
#ifndef __RESID_DEF__
#define __RESID_DEF__

#include "CQMacros.h"
#include "ResID.h"

NS_CQ_BEGIN

class ResIDDef
{
public:
	static const ResID DEF_VERTEX_SHADER;
	static const ResID DEF_FRAGMENT_SHADER;
	static const ResID DEF_NO_TEX_VERTEX_SHADER;
	static const ResID DEF_NO_TEX_FRAGMENT_SHADER;
	static const ResID DEF_DIFFUSE_VERTEX_SHADER;
	static const ResID DEF_DIFFUSE_FRAGMENT_SHADER;
	static const ResID DEF_PHONG_VERTEX_SHADER;
	static const ResID DEF_PHONG_FRAGMENT_SHADER;
	static const ResID DEF_MULTILIGHT_VERTEX_SHADER;
	static const ResID DEF_MULTILIGHT_FRAGMENT_SHADER;
	static const ResID DEF_SPOTLIGHT_VERTEX_SHADER;
	static const ResID DEF_SPOTLIGHT_FRAGMENT_SHADER;

public:
	static const ResID HELLOWORLD_WALL_TEX;

public:
	static const ResID BUNNY_MESH;
	static const ResID AIRCRAFT_MESH;






};

NS_CQ_END

#endif /* __RESID_DEF__ */
