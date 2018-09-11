/*
*
*		qiu_hao		2018/03/08		03.19.pm
*/
#ifndef __COUTILS_H__
#define __COUTILS_H__

#include "CQScheduler.h"

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
*
*/
template<typename Fn, typename...Args>
inline auto makeAction(Fn&& _f, Args&&... _args)
{
	return new CQAction<Fn, Args...>(std::forward<Fn>(_f), std::forward<Args>(_args)...);
}

//*****************************************************************************
//
//! \brief Coarse-grained Timer.
//! \param [in] _ac	 None.
//! \param [in] _sec Delay time.Engine call every frame when time equal to zero.
//! \retval Handler for delayed calls.
//
//*****************************************************************************
int64_t delayCall(Action *_ac, const float _sec, const bool _isRepeat = false);

/*
*
*/
void cancelDelayCall(int64_t _id);

NS_CQ_END

#endif /*__COUTILS_H__*/
