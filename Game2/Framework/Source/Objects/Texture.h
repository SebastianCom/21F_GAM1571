#pragma once

namespace fw {

class Texture
{
public:
    Texture();
    Texture(char* filename);
    virtual ~Texture();

protected:
    GLuint m_TextureID;
};

} // namespace fw
