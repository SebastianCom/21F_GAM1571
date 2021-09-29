#pragma once

namespace fw {

	class ShaderProgram;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void Draw(ShaderProgram* pShader);

protected:
	GLuint m_VBO;
 
};

} // namespace fw
