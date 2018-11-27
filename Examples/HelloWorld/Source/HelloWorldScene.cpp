#include "HelloWorldScene.h"

REGISTER_START_SCENE(HelloWorldScene)



void HelloWorldScene::onInit()
{
	dbgPuts("[HelloWorldScene] init success!");

	// camera
	// TODO : should have a default camera.
	camera_ = CQ_NEW(CQCamera);

	// IO
	CQIO::addSearchPath(CQIO::getCurDir() /*+ "/GIT_SOURCE" */+ "/CQEngine/CQEngine/Assets/shader/");
	CQIO::addSearchPath(CQIO::getCurDir() /*+ "/GIT_SOURCE" */+ "/CQEngine/CQEngine/Assets/texture/");
	dbgPuts(CQIO::getCurDir().c_str());
	// shader
	d1_ = CQIO::cvLoadFile("def.vs");
	d2_ = CQIO::cvLoadFile("def.fs");
	if (d1_->staus_ != Data::LOAD_SUCCESS ||
		d2_->staus_ != Data::LOAD_SUCCESS)
	{
		return;
	}

	program_.attachNativeShader(static_cast<char*>(d1_->buff_), CQGLProgram::SHADER_VERTEX);
	program_.attachNativeShader(static_cast<char*>(d2_->buff_), CQGLProgram::SHADER_PIXEL);
	program_.genProgram();

	// macros
#define VERTEX_POS_SIZE			3
#define VERTEX_TEXCOORD0_SIZE	2
#define VERTEX_TEXCOORD1_SIZE	2

#define VERTEX_POS_INDEX		0
#define VERTEX_TEXCOORD0_INDEX	1

#define VERTEX_POS_OFFSET		0
#define VERTEX_TEXCOORD0_OFFSET	3

#define VERTEX_ATTRIB_SIZE		(VERTEX_POS_SIZE + \
								 VERTEX_TEXCOORD0_SIZE)
	// array of structures
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f,0.0f, // left  bottom
		0.5f, -0.5f, 0.0f,		1.0f,0.0f, // right bottom
		0.0f,  0.5f, 0.0f,		0.5f,1.0f, // top middle  
	};

	indexs_[0] = 2;
	indexs_[1] = 1;
	indexs_[2] = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs_), indexs_, GL_STREAM_DRAW);
		{
			// pos
			glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float), (void*)VERTEX_POS_OFFSET);
			glEnableVertexAttribArray(0);

			// uv
			glVertexAttribPointer(VERTEX_TEXCOORD0_INDEX, VERTEX_TEXCOORD0_SIZE, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float), (void*)(VERTEX_TEXCOORD0_OFFSET * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	// texture
	img_ = CQResLoader::shareLoader()->loadImgDataSync("img.jpg");

	program_.setInt("uTexture0", 0);
	texture_ = CQ_NEW(CQGLTexture,img_->width_, img_->height_, img_->data_);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	/////////////////////// TMP //////////////////
	delayCall(makeAction(&HelloWorldScene::debugOutput, this), 2.0f, false);
}

void HelloWorldScene::update()
{
	glClearColor(1.0f, 1.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// camera
	// NOTICE: zNear can NOT be zero, otherwise result will occur NAN!
	// TODO : add Assert.
	//Matrix4 viewMat = lookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	//Matrix4 projMat = perspective(60.0f, 1.5f, 0.1f, 100.0f);

	auto transform = camera_->getTransform();
	transform->lookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	float aspect(800.0f / 600.0f);
	auto viewMat = transform->calWorldToLcalMatRH();
	auto projMat = camera_->calPerspectiveMat(60, aspect, 0.1f, 100.0f);

	// program
	program_.load();

	//tmat4x4<T>& rotate(value_type angle, tvec3<T> const & v)
	Matrix4 tmp(1.0f);
	Vector3 v(0.0f, 1.0f, 0.0f);
	Matrix4 rotateMat = rotate(tmp, ++angle_, v);

	//Matrix4 translateMat(1);
	//translateMat.translate(0.0f, 0.0f, -1.0f);

	Matrix4 modelMat = rotateMat;//* translateMat;

	Matrix4 mvp = projMat * viewMat * modelMat;
	program_.setMatrix("mvp", mvp);

	//
	texture_->Bind();

	// rebind VAO
	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, sizeof(indexs_) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}

void HelloWorldScene::onDestory()
{
	dbgPuts("[HelloWorldScene] onDestory success!");

	program_.unLoad();
	CQ_DELETE(texture_, CQGLTexture);
	CQ_DELETE(camera_, CQCamera);
	CQResLoader::shareLoader()->unloadImgData(img_);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void HelloWorldScene::debugOutput()
{
	dbgPuts("[HelloWorldScene] debugOutput!");
}

