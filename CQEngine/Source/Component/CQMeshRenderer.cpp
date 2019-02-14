#include <glad/glad.h>
#include "CQDebug.h"
#include "CQMesh.h"
#include "CQLight.h"
#include "CQMaterial.h"
#include "CQMeshRenderer.h"

USING_NS_CQ;

CQMeshRenderer::CQMeshRenderer()
{

}

CQMeshRenderer::~CQMeshRenderer()
{

}

void CQMeshRenderer::setup(CQMesh * _mesh, CQLight * _light, std::vector<CQMaterial*> & _materials)
{
#define VERTEX_POS_SIZE			3
#define VERTEX_NORMAL_SIZE		3
#define VERTEX_TANGENT_SIZE 	3
#define VERTEX_UV_SIZE			2	

	// TODO:
	// * for each _mesh->sharedMesh 
	// * GL_STATIC_DRAW
	//   tmp process:
	auto mesh = _mesh->sharedMesh()[0];

	GLuint VAO, VBO, EBO;

	CQ_GLCHECK(glGenVertexArrays(1, &VAO));
	CQ_GLCHECK(glGenBuffers(1, &VBO));
	CQ_GLCHECK(glGenBuffers(1, &EBO));

	// bind buffer
	CQ_GLCHECK(glBindVertexArray(VAO));
	{
		// trans data to buffer.
		CQ_GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		CQ_GLCHECK(glBufferData(GL_ARRAY_BUFFER, mesh->vBuff_.size() * sizeof(Vertex), &(mesh->vBuff_[0]), GL_STATIC_DRAW));

		CQ_GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		CQ_GLCHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->iBuff_.size() * sizeof(unsigned int), &(mesh->iBuff_[0]), GL_STATIC_DRAW));
		
		// set data(vertex) attribute:
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, VERTEX_NORMAL_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal_));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, VERTEX_TANGENT_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent_));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, VERTEX_UV_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv_));

	}
	CQ_GLCHECK(glBindVertexArray(0));
}
