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

    void SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex);
    void Draw(ShaderProgram* pShader, float scale, vec2 pos, float time, vec2 camPos, vec2 projScale);
    void SetupUniform(ShaderProgram* pShader, GLchar* name, float uValue);
    void SetupUniform(ShaderProgram* pShader, GLchar* name, vec2 uValue);

protected:
    GLuint m_VBO;

    GLenum m_PrimitiveType;
    int m_NumVerts;
};

} // namespace fw
