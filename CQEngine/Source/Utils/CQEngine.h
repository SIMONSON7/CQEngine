//*****************************************************************************
//
//! \file CQEngine.h
//! \brief Engine header files.
//! \author qiu_hao
//! \date 2018/09/11 11.13.pm
//
//*****************************************************************************
#ifndef __CQENGINE__
#define __CQENGINE__

// Util
#include "CQMacros.h"
#include "CQDebug.h"
#include "CQMemory.h"
#include "CQIO.h"
#include "CQMath.h"
#include "CQAny.h"
#include "CQUtils.h"

// Time
#include "CQTime.h"
#include "CQAction.h"
#include "CQScheduler.h"

// Event
#include "CQEvtDispatcher.h"
#include "CQEvtListener.h"
#include "CQInput.h"

// Res
#include "ResID_Def.h"
#include "CQResLoader.h"
#include "CQShader.h"
#include "CQTexture.h"
#include "CQMesh.h"
#include "CQResManager.h"

// Component
#include "CQComponent.h"
#include "CQTransform.h"
#include "CQMeshRenderer.h"

// Scene
#include "CQObject.h"
#include "CQSceneNode.h"
#include "CQScene.h"
#include "CQSceneManager.h"
#include "CQCuller.h"

// AI
#include "CQBevTree.h"
#include "CQBevPrecondition.h"
#include "CQBevNode.h"
#include "CQBevLeaf.h"
#include "CQBevLoop.h"
#include "CQBevPrioritySelector.h"
#include "CQBevNonePrioritySelector.h"
#include "CQBevParallel.h"
#include "CQBevSequence.h"

// Render
#include "CQCamera.h"
#include "CQGLProgram.h"
#include "CQGLTexture.h"
#include "CQShaderProgram.h"
#include "CQLight.h"
#include "CQMaterial.h"
#include "CQRenderer.h"

// Prefab
#include "CQPrefab.h"
#include "CQPlane.h"
#include "CQCube.h"
#include "CQPrefabFactory.h"

// Core
#include "CQCore.h"

#endif /* __CQENGINE__ */
