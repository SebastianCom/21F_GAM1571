#pragma once

#include "Math/Vector.h"

namespace fw {

class ShaderProgram;

struct VertexFormat
{
    vec2 pos;
    unsigned char color[4];
    vec2 uv;
};

class Mesh
{
public:
    Mesh(GLenum primitiveType, std::vector<VertexFormat>& verts);
    virtual ~Mesh();

    void Draw(ShaderProgram* pShader, float scale, vec2 pos, float time);

protected:
    GLuint m_VBO;

    GLenum m_PrimitiveType;
    int m_NumVerts;
};

} // namespace fw
