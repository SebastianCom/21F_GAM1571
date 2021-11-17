#pragma once

namespace fw {

class Texture
{
public:
    Texture();
    Texture(char* filename);
    virtual ~Texture();

    GLuint GetTextureID() { return m_TextureID; }

protected:
    GLuint m_TextureID;
};

} // namespace fw
