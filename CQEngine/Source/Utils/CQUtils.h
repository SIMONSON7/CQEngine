/*
*
*		qiu_hao		2018/03/08		03.19.pm
*/
#ifndef __COUTILS_H__
#define __COUTILS_H__

#include "CQMacros.h"
#include "CQAction.h"

NS_CQ_BEGIN

class CQTexture;

/*
* If the user does not specify the way to load, it will be selected automatically
* according to the size of the file, type, and so on.
*/
CQTexture* loadTexture(const char *_filePath);

// TODO : return pointer of Mesh
/*
* If the user does not specify the way to load, it will be selected automatically
* according to the size of the file, type, and so on.
*/
void * loadMesh(const char *_filePath);

/*

*/
template<typename Fn, typename...Args>
auto makeAction(const Fn&& _f, Args&&... _args)
{
	return CQAction<Fn, Args...>(std::forward<Fn>(_f), std::forward<Args>(_args)...);
}



NS_CQ_END

#endif /*__COUTILS_H__*/
