#pragma once

#include "Math/Vector.h"

namespace fw {

class ShaderProgram;
class Texture;

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

    void SetupUniform(ShaderProgram* pShader, char* name, float value);
    void SetupUniform(ShaderProgram* pShader, char* name, vec2 value);
    void SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex);
    void Draw(ShaderProgram* pShader, Texture* pTexture, fw::vec2 scale, vec2 pos, 
                float time, fw::vec2 camPos, fw::vec2 projScale,
                fw::vec2 uvScale, fw::vec2 uvOffset
            );

protected:
    GLuint m_VBO;

    GLenum m_PrimitiveType;
    int m_NumVerts;
};

} // namespace fw
