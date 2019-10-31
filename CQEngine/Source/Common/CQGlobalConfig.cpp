#include "CQMacros.h"
#include "CQWGLRenderContext.h"
#include "CQWindowsApplication.h"

USING_NS_CQ

CQFrameConfiguration frameConfiguration;
CQWGLRenderContext * wglRenderContext = CQ_RAW_NEW(CQWGLRenderContext, frameConfiguration);
/* Bridge pattern : Windows + WGL */
CQWindowsApplication glWindowsApplication(wglRenderContext);
CQIApplication * g_pApplication = &glWindowsApplication;