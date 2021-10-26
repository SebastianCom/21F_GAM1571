
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace fw {

	Mesh::Mesh(GLenum primitiveType, const std::vector<float>& verts)
		: m_VBO(0)
	{
		const int numAttributeComponentsPerVertex = 6; // x,y & a for each vertex.

		m_PrimitiveType = primitiveType;
		m_NumVerts = (int)verts.size() / numAttributeComponentsPerVertex;
		
		// Generate a buffer for our vertex attributes.
		glGenBuffers(1, &m_VBO);

		// Set this VBO to be the currently active one.
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		// Copy our attribute data into the VBO.
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * m_NumVerts, &verts[0], GL_STATIC_DRAW);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::Draw(ShaderProgram* pShader, vec2 pos, float time, float scale)
	{
		// Draw the mesh.
		{
			glUseProgram(pShader->GetProgram());

			GLint u_Offset = glGetUniformLocation(pShader->GetProgram(), "u_Offset");
			glUniform2f(u_Offset, pos.x, pos.y);

			GLint u_Time = glGetUniformLocation(pShader->GetProgram(), "u_Time");
			glUniform1f(u_Time, time);
			
			GLint u_Scale = glGetUniformLocation(pShader->GetProgram(), "u_Scale");
			glUniform1f(u_Scale, scale);

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
			glDrawArrays(m_PrimitiveType, 0, m_NumVerts);
			
		}
	}




} // namespace fw
