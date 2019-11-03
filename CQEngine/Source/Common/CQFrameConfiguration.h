//*****************************************************************************
//
//! \file CQFrameConfiguration.h
//! \brief The description of a frame.
//! \author qiu_hao
//! \date 2019/10/31 10:47.pm
//
//*****************************************************************************
#ifndef __CQ_FRAMECONFIGURATION_H__
#define __CQ_FRAMECONFIGURATION_H__

#include <stdint.h>
#include "CQMacros.h"

NS_CQ_BEGIN

struct CQFrameConfiguration 
{
	/// Inline all-elements constructor.
	/// \param[in] r the red color depth in bits
	/// \param[in] g the green color depth in bits
	/// \param[in] b the blue color depth in bits
	/// \param[in] a the alpha color depth in bits
	/// \param[in] d the depth buffer depth in bits
	/// \param[in] s the stencil buffer depth in bits
	/// \param[in] msaa the msaa sample count
	/// \param[in] width the screen width in pixel
	/// \param[in] height the screen height in pixel
	CQFrameConfiguration(
		uint32_t r = 8,
		uint32_t g = 8,
		uint32_t b = 8,
		uint32_t a = 8,
		uint32_t d = 24,
		uint32_t s = 0,
		uint32_t msaa = 0,
		uint32_t width = 1080,
		uint32_t height = 720) :
		redBits(r), greenBits(g), blueBits(b), alphaBits(a),
		depthBits(d), stencilBits(s), msaaSamples(msaa),
		screenWidth(width), screenHeight(height)
	{}

	uint32_t redBits; ///< red color channel depth in bits
	uint32_t greenBits; ///< green color channel depth in bits
	uint32_t blueBits; ///< blue color channel depth in bits
	uint32_t alphaBits; ///< alpha color channel depth in bits
	uint32_t depthBits; ///< depth buffer depth in bits
	uint32_t stencilBits; ///< stencil buffer depth in bits
	uint32_t msaaSamples; ///< MSAA samples
	uint32_t screenWidth;
	uint32_t screenHeight;
};

NS_CQ_END

#endif /* __CQ_FRAMECONFIGURATION_H__ */

