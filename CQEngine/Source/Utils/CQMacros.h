/*
*
*		qiu_hao		2017/12/15		11:02.pm
*/
#ifndef __CQMACROS_H__
#define __CQMACROS_H__


#if defined( _DEBUG ) || defined (__DEBUG__)
#   ifndef CQDEBUG
#       define CQDEBUG
#   endif
#endif

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 4251)
#endif





#if defined(CQDEBUG)
#   if defined(_MSC_VER)
#       define CQASSERT( x )           if ( !((void)0,(x))) { __debugbreak(); }
#   elif defined (ANDROID_NDK)
#       include <android/log.h>
#       define CQASSERT( x )           if ( !(x)) { __android_log_assert( "assert", "grinliz", "ASSERT in '%s' at %d.", __FILE__, __LINE__ ); }
#   else
#       include <assert.h>
#       define CQASSERT                assert
#   endif
#else
#   define CQASSERT( x )               {}
#endif



#endif /* __CQMACROS_H__ */