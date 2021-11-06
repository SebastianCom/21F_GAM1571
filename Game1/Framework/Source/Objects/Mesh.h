#pragma once

namespace fw {

	class ShaderProgram;



class Mesh
{
public:
	Mesh(GLenum primitiveType, const std::vector<float>& verts);
	virtual ~Mesh();

	virtual void Draw(ShaderProgram* pShader, vec2 pos, float time, float scale, float colorShift);


protected:
	GLuint m_VBO;
	

	GLenum m_PrimitiveType;
	int m_NumVerts;

};

} // namespace fw
