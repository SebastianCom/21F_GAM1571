#pragma once

namespace fw {

class Texture
{
public:
    Texture();
    Texture(const char* filename);
    virtual ~Texture();

protected:
    GLuint m_TextureID;
};

} // namespace fw
