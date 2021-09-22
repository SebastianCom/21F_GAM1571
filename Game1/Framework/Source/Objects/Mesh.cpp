
#include "Framework.h"
#include "Mesh.h"

namespace fw {



	Mesh::Mesh()
	{
		const int numVerts = 3;
		const int numAttributeComponentsPerVertex = 2; // x & y for each vertex.
		float verts[numVerts * numAttributeComponentsPerVertex] = { 0.0f,0.0f,   0.5f,0.5f,   -0.5f,0.5f, };
		m_VBO = 0;
		// Create the mesh.
		{
			// Generate a buffer for our vertex attributes.
			glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

			// Set this VBO to be the currently active one.
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			// Copy our attribute data into the VBO.
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * numVerts, verts, GL_STATIC_DRAW);
		}
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::Draw()
	{
		// Draw the mesh.
		{
			// Set this VBO to be the currently active one.
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			// Get the attribute variable’s location from the shader.
			GLint loc = 0;
			glEnableVertexAttribArray(loc);

			// Describe the attributes in the VBO to OpenGL.
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);

			// Draw the primitive.
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

} // namespace fw
