#pragma once

namespace fw {

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void Draw();

protected:
	GLuint m_VBO;
 
};

} // namespace fw
