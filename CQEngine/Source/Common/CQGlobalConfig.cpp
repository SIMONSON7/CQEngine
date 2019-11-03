#include "CQMacros.h"
#include "CQWGLRenderContext.h"
#include "CQWindowsApplication.h"

USING_NS_CQ

const char * appName = "CQEngine";
CQFrameConfiguration frameConfiguration;
CQWGLRenderContext * wglRenderContext = CQ_RAW_NEW(CQWGLRenderContext, frameConfiguration);
/* Bridge pattern : Windows + WGL */
CQWindowsApplication glWindowsApplication(appName, wglRenderContext);
CQIApplication * g_pApplication = &glWindowsApplication;