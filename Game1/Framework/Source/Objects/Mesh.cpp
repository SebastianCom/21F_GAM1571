
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace fw {

	Mesh::Mesh(ObjectType a)
	{
		m_VBO = 0;
		if (a == ObjectType::Player)
		{
			CreateMesh(ObjectType::Player);
		}
		if (a == ObjectType::Enemny)
		{
			CreateMesh(ObjectType::Enemny);
		}
		
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::Draw(ShaderProgram* pShader)
	{
		// Draw the mesh.
		{
			// Set this VBO to be the currently active one.
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			// Get the attribute variable’s location from the shader.
			GLint a_Position = glGetAttribLocation(pShader->GetProgram(), "a_Position");
			if (a_Position != -1) 
			{
				glEnableVertexAttribArray(a_Position);
				glVertexAttribPointer(a_Position, 2, GL_FLOAT, GL_FALSE, 24, (void*)0);  // Describe the attributes in the VBO to OpenGL.
			}
			
			GLint a_Color = glGetAttribLocation(pShader->GetProgram(), "a_Color");
			if (a_Color != -1)
			{
				glEnableVertexAttribArray(a_Color);
				glVertexAttribPointer(a_Color, 4, GL_FLOAT, GL_FALSE, 24, (void*)8);
			}


			// Draw the primitive.
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	void Mesh::CreateMesh(ObjectType a)
	{
		if (a == ObjectType::Player)
		{
			const int numVerts = 3;
			const int numAttributeComponentsPerVertex = 6; // x & y & a for each vertex.
			float playerVerts[numVerts * numAttributeComponentsPerVertex] = { 0.0f,0.0f,1.0f,0.0f,0.0f,0.2f,   0.5f,0.5f,0.0f,0.9f,0.0f,0.5f,   -0.5f,0.5f,0.0f, 0.0f,1.0f,0.9f };
			// Create the mesh.
			{
				// Generate a buffer for our vertex attributes.
				glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

				// Set this VBO to be the currently active one.
				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

				// Copy our attribute data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * numVerts, playerVerts, GL_STATIC_DRAW);
			}
		}
		if (a == ObjectType::Enemny)
		{
			const int numVerts = 3;
			const int numAttributeComponentsPerVertex = 6; // x & y & a for each vertex.
			float playerVerts[numVerts * numAttributeComponentsPerVertex] = { 0.5f,0.0f,1.0f,0.0f,0.0f,0.2f,   0.2f,0.5f,0.0f,0.9f,0.0f,0.5f,   -0.7f,0.5f,0.0f, 0.0f,1.0f,0.9f };
			// Create the mesh.
			{
				// Generate a buffer for our vertex attributes.
				glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

				// Set this VBO to be the currently active one.
				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

				// Copy our attribute data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * numVerts, playerVerts, GL_STATIC_DRAW);
			}
		}
	}



} // namespace fw
