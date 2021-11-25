#include "CoreHeaders.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace fw {

Mesh::Mesh(GLenum primitiveType, std::vector<VertexFormat>& verts)
    : m_VBO( 0 )
{
    m_PrimitiveType = primitiveType;
    m_NumVerts = (int)verts.size();

    // Generate a buffer for our vertex attributes.
    glGenBuffers( 1, &m_VBO );

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Copy our attribute data into the VBO.
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*m_NumVerts, &verts[0], GL_STATIC_DRAW );
}

Mesh::~Mesh()
{
    // Release the memory.
    glDeleteBuffers( 1, &m_VBO );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, float value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform1f( location, value );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, vec2 value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform2f( location, value.x, value.y );
}

void Mesh::SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex)
{
    GLint location = glGetAttribLocation( pShader->GetProgram(), name );
    if( location != -1 )
    {
        glEnableVertexAttribArray( location );
        glVertexAttribPointer( location, size, type, normalize, stride, (void*)startIndex );
    }
}

void Mesh::Draw(ShaderProgram* pShader, Texture* pTexture, fw::vec2 scale, vec2 pos, float time, 
                fw::vec2 camPos, fw::vec2 projScale, float sheetWidth, fw::vec2 uvScale, 
                fw::vec2 uvOffset)
{
    // Setup uniforms.
    glUseProgram( pShader->GetProgram() );

    SetupUniform( pShader, "u_ObjectScale", scale );
    SetupUniform( pShader, "u_Offset", pos );
    SetupUniform( pShader, "u_Time", time );
    SetupUniform( pShader, "u_CameraPosition", camPos );
    SetupUniform( pShader, "u_ProjectionScale", projScale );
    SetupUniform( pShader, "u_SpriteSheetWidth", sheetWidth );
    SetupUniform( pShader, "u_UVScale", uvScale );
    SetupUniform( pShader, "u_UVOffset", uvOffset );

    // Setup and program the texture uniform.
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
    GLint location = glGetUniformLocation( pShader->GetProgram(), "u_Texture" );
    glUniform1i( location, 0 );

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Get the attribute variable’s location from the shader.
    // Describe the attributes in the VBO to OpenGL.
    SetupAttribute( pShader, "a_Position", 2, GL_FLOAT, GL_FALSE, 20, 0 );
    SetupAttribute( pShader, "a_Color", 4, GL_UNSIGNED_BYTE, GL_TRUE, 20, 8 );
    SetupAttribute( pShader, "a_UVCoord", 2, GL_FLOAT, GL_FALSE, 20, 12 );

    // Draw the primitive.
    glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
}

} // namespace fw
