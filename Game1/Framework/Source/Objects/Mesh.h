#pragma once

namespace fw {

	class ShaderProgram;



class Mesh
{
public:
	Mesh(ObjectType);
	virtual ~Mesh();

	virtual void Draw(ShaderProgram* pShader);

	void CreateMesh(ObjectType);

protected:
	GLuint m_VBO;

};

} // namespace fw
