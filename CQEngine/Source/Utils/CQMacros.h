/*
*
*		qiu_hao		2017/12/15		11:02.pm
*/
#ifndef __CQMACROS_H__
#define __CQMACROS_H__

/// @name namespace CQEngine
/// @{
#ifdef __cplusplus
#	define NS_CQ_BEGIN                     namespace CQEngine {
#	define NS_CQ_END                       }
#	define USING_NS_CQ                     using namespace CQEngine;
#	define NS_CQ                           ::CQEngine
#else
#	define NS_CQ_BEGIN 
#	define NS_CQ_END 
#	define USING_NS_CQ 
#	define NS_CQ
#endif 
//  end of namespace group
/// @}


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

// C++11 features
#if defined(_MSC_VER) && ((_MSC_VER) >= 1700)
#	define CQ_USE_CPP11 1 
#else
#	define CQ_USE_CPP11 0
#endif

#define MAX_PATH_SIZE 512
#define MAX_STRBUFF_SIZE 2048

#if defined(_MSC_VER)
#	define getcwd(d, s) (_getcwd(d, s))
#endif

#define VNAME(var) (#var)

#define Interface  class
#define implements public	

#endif /* __CQMACROS_H__ */
