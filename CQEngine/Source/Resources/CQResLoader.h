//*****************************************************************************
//
//! \file CQResLoader.h
//! \brief Resource Loader.
//! \author qiu_hao
//! \date 2018/03/08 03.46.pm
//
//*****************************************************************************
#ifndef __CORESLOADER_H__
#define __CORESLOADER_H__

#include <vector>
#include <string>
#include <thread>
#include <condition_variable>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "CQMacros.h"
#include "CQNoncopyable.h"
#include "CQSafeStack.h"
#include "CQAction.h"

NS_CQ_BEGIN

struct Img;
struct SubMesh;

struct RawData
{
	unsigned char * data_;
	size_t size_;
};

struct AsyncRawData
{
	RawData * rawData_;
	std::string abPath_;
	std::function<void(RawData*)> cb_;
};

class CQResLoader : private CQNoncopyable
{
public:
	static
	CQResLoader * shareLoader();

	virtual ~CQResLoader();

public:
	RawData * loadRawDataSync(const std::string & _abPath);

	void loadRawDataAsync(const std::string & _abPath, std::function<void(RawData*)> & _cb);

	void unloadRawData(RawData * _data);

public:
	Img * loadImgSync(const std::string & _abPath);

	void unloadImg(Img * _img);

	std::vector<SubMesh*> loadSubMeshesSync(const std::string & _abPath);

	void unloadMesh(SubMesh * _mesh);

private:
	void __rdLoadThreadFun();

	void __doCallBack();

private:
	SubMesh * __processSubMesh(aiMesh* mesh);

private:
	explicit CQResLoader();

private:
	int64_t asyncDCHd_;

	CQSafeStack<AsyncRawData*> asyncStack_;

	CQSafeStack<AsyncRawData*> cbStack_;

	std::shared_ptr<std::thread> rdLoadThd_;

};

NS_CQ_END

#endif /*__CORESLOADER_H__*/