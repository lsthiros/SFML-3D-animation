#include "Mesh.h"


Mesh::Mesh(aiMesh *mesh, aiNode* node, aiMatrix4x4* transform) : m_node(node), m_mesh(mesh), m_transform(transform)
{
	//find out how many vertices there are in this mesh
	//this is probably going to come in handy later
	m_numVertices=m_mesh->mNumVertices;
	m_vertices=new Vertex[m_numVertices];
	for(unsigned int i=0;i<m_numVertices;i++) {
		//deal with the model space coordinates first
		m_vertices[i].modelSpace[0]=m_mesh->mVertices[i][0];
		m_vertices[i].modelSpace[1]=m_mesh->mVertices[i][1];
		m_vertices[i].modelSpace[2]=m_mesh->mVertices[i][2];

		//then put the normals in there as well
		m_vertices[i].normal[0]=m_mesh->mNormals[i][0];
		m_vertices[i].normal[1]=m_mesh->mNormals[i][1];
		m_vertices[i].normal[2]=m_mesh->mNormals[i][2];
	};
	//These vertices are NOT COMPLETE. They only contain
	//normals and modelspace coordinates.
}

//TODO make sure all memory is unallocated
Mesh::~Mesh(void)
{
}
