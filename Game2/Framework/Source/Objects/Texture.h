#pragma once

namespace fw {

class Texture
{
public:
    Texture();
    virtual ~Texture();

protected:
    GLuint m_TextureID;
};

} // namespace fw
