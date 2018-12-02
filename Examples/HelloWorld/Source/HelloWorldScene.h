/*
*
*		qiu_hao		2018/08/18		11:10.pm
*/

#include "CQEngine.h"

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

USING_NS_CQ

class HelloWorldScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit HelloWorldScene() {} 

	virtual ~HelloWorldScene() {}

private:
	void debugOutput();

public:
	virtual void onInit();

	virtual void update();

	virtual void onDestory();

	void onMouseClick(void* _clickData);

	void onMouseWheel(void* _wheelData);

private:
	/////////////////////// TMP //////////////////
	CQGLProgram program_;
	CQGLTexture *texture_;
	ImgData* img_;

	float radius_ = 1.0f;
	float angle_ = 0;
	unsigned int VBO, VAO, EBO;
	unsigned int indexs_[3];

	std::shared_ptr<Data> d1_;
	std::shared_ptr<Data> d2_;

	CQCamera* camera_;

	std::shared_ptr<CQEvtListener> clickListener_; 
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __HELLOWORLD_SCENE_H__ */
