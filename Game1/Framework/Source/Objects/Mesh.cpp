
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
		if (a == ObjectType::PickUp)
		{
			CreateMesh(ObjectType::PickUp);
		}
		m_eCurrentObject = a;
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

			if (m_eCurrentObject == ObjectType::Player)
			{

				glDrawArrays(GL_TRIANGLES, 0, 72);
			}
			else if (m_eCurrentObject == ObjectType::Enemny)
			{
				glDrawArrays(GL_TRIANGLES, 0, 54);
			}
			else if (m_eCurrentObject == ObjectType::PickUp)
			{
				glDrawArrays(GL_TRIANGLES, 0, 30);
			}
		}
	}

	void Mesh::CreateMesh(ObjectType a)
	{
		if (a == ObjectType::Player)
		{
			const int numVerts = 72;
			const int numAttributeComponentsPerVertex = 6;
			float playerVerts[numVerts * numAttributeComponentsPerVertex] = {
				-0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,-0.60f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.20f, 0.81f, 0.61f, 0.48f, 1.0f,
				-0.60f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,-0.40f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.20f, 0.81f, 0.61f, 0.48f, 1.0f,0.20f, 0.20f, 0.81f, 0.61f, 0.48f, 1.0f,0.40f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,
				0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,0.60f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,0.40f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.00f, 0.39f, 0.81f, 0.61f, 0.48f, 1.0f,-0.06f, 0.41f, 0.81f, 0.61f, 0.48f, 1.0f,
				-0.06f, 0.41f, 0.81f, 0.61f, 0.48f, 1.0f,-0.12f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,-0.12f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,-0.15f, 0.51f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
				-0.15f, 0.51f, 0.81f, 0.61f, 0.48f, 1.0f,-0.17f, 0.60f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,-0.17f, 0.60f, 0.81f, 0.61f, 0.48f, 1.0f,-0.15f, 0.68f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
				-0.15f, 0.68f, 0.81f, 0.61f, 0.48f, 1.0f,-0.08f, 0.73f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,-0.08f, 0.73f, 0.81f, 0.61f, 0.48f, 1.0f,-0.02f, 0.74f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
				-0.02f, 0.74f, 0.81f, 0.61f, 0.48f, 1.0f,0.04f, 0.72f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.04f, 0.72f, 0.81f, 0.61f, 0.48f, 1.0f,0.11f, 0.66f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
				0.11f, 0.66f, 0.81f, 0.61f, 0.48f, 1.0f,0.12f, 0.58f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.12f, 0.58f, 0.81f, 0.61f, 0.48f, 1.0f,0.11f, 0.50f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
				0.11f, 0.50f, 0.81f, 0.61f, 0.48f, 1.0f,0.09f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.09f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,0.00f, 0.39f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
				-0.20f, 0.40f, 1.0f, 0.0f, 0.0f, 1.0f,0.20f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,-0.20f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,0.20f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,0.20f, 0.40f, 1.0f, 0.0f, 0.0f, 1.0f,-0.20f, 0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
				-0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,-0.40f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,
				0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,0.40f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f
			};

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
			const int numVerts = 54;
			const int numAttributeComponentsPerVertex = 6;
			float enemyverts[numVerts * numAttributeComponentsPerVertex] = {
				-0.40f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,-0.20f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,-0.40f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,-0.20f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
				0.20f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,0.20f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,0.40f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,0.40f, -0.40f, 0.0f, 1.0f, 0.0f, 1.0f,0.40f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,0.40f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,-0.40f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,-0.40f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
				0.40f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,-0.40f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,0.40f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,0.40f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,0.20f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,0.40f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,0.20f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,
				0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,0.20f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.40f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,
				-0.20f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,-0.40f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,-0.40f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, 0.0f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.40f, -0.20f, 0.45f, 0.0f, 0.55f, 1.0f,-0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
				-0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.60f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.60f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.60f, 0.50f, 0.50f, 0.50f, 1.0f,
				-0.00f, 0.45f, 0.0f, 0.0f, 0.0f, 1.0f,0.05f, 0.39f, 0.0f, 0.0f, 0.0f, 1.0f,0.00f, 0.31f, 0.0f, 0.0f, 0.0f, 1.0f,-0.00f, 0.45f, 0.0f, 0.0f, 0.0f, 1.0f,0.00f, 0.31f, 0.0f, 0.0f, 0.0f, 1.0f,-0.04f, 0.40f, 0.0f, 0.0f, 0.0f, 1.0f
			};

			// Create the mesh.
			{
				// Generate a buffer for our vertex attributes.
				glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

				// Set this VBO to be the currently active one.
				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

				// Copy our attribute data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * numVerts, enemyverts, GL_STATIC_DRAW);
			}
		}
		if (a == ObjectType::PickUp)
		{

			const int numVerts = 30;
			const int numAttributeComponentsPerVertex = 6;
			float pickUpverts[numVerts * numAttributeComponentsPerVertex] = {
				0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.40f, 1.0f, 0.0f, 1.0f, 1.0f,-0.40f, -0.20f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,-0.40f, 0.20f, 1.0f, 0.0f, 1.0f, 1.0f,-0.20f, 0.40f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0.20f, 0.40f, 1.0f, 0.0f, 1.0f, 1.0f,
				0.40f, 0.20f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0.40f, -0.20f, 1.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.40f, 1.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.40f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, -0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
				0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
				0.40f, -0.20f, 1.0f, 1.0f, 0.0f, 1.0f,0.60f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,0.40f, 0.20f, 1.0f, 1.0f, 0.0f, 1.0f,-0.40f, 0.20f, 1.0f, 1.0f, 0.0f, 1.0f,-0.60f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,-0.40f, -0.20f, 1.0f, 1.0f, 0.0f, 1.0f
			};

			// Create the mesh.
			{
				// Generate a buffer for our vertex attributes.
				glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

				// Set this VBO to be the currently active one.
				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

				// Copy our attribute data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * numVerts, pickUpverts, GL_STATIC_DRAW);
			}
		}

	}



} // namespace fw
