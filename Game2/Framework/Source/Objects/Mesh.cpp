#include "CoreHeaders.h"
#include "Mesh.h"
#include "ShaderProgram.h"

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

void Mesh::SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex)
{
    GLint location = glGetAttribLocation( pShader->GetProgram(), name );
    if( location != -1 )
    {
        glEnableVertexAttribArray( location );
        glVertexAttribPointer( location, size, type, normalize, stride, (void*)startIndex );
    }
}

void Mesh::Draw(ShaderProgram* pShader, float scale, vec2 pos, float time, vec2 camPos, vec2 projScale)
{
    // Setup uniforms.
    glUseProgram( pShader->GetProgram() );

     //GLint u_ViewTranslation = glGetUniformLocation(pShader->GetProgram(), "u_ViewTranslation");
    //glUniform2f(u_ViewTranslation, view.x, view.y);

    //GLint u_ProjScale = glGetUniformLocation(pShader->GetProgram(), "u_ProjScale");
    //glUniform2f(u_ProjScale, proj.x, proj.y);
    
    SetupUniform(pShader, "u_ObjectScale", scale);
    SetupUniform(pShader, "u_Offset", pos);
    SetupUniform(pShader, "u_CamPos", camPos);
    SetupUniform(pShader, "u_ProjScale", projScale);
    SetupUniform(pShader, "u_Time", time);
    
    //GLint u_ObjectScale = glGetUniformLocation( pShader->GetProgram(), "u_ObjectScale" );
    //glUniform1f( u_ObjectScale, scale );

    //GLint u_Offset = glGetUniformLocation( pShader->GetProgram(), "u_Offset" );
    //glUniform2f( u_Offset, pos.x, pos.y );



    //GLint u_Time = glGetUniformLocation( pShader->GetProgram(), "u_Time" );
    //glUniform1f( u_Time, time );

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

void Mesh::SetupUniform(ShaderProgram* pShader, GLchar* name, float uValue)
{
    GLint location = glGetUniformLocation(pShader->GetProgram(), name);
    glUniform1f(location, uValue);
}

void Mesh::SetupUniform(ShaderProgram* pShader, GLchar* name, vec2 uValue)
{
    GLint location = glGetUniformLocation(pShader->GetProgram(), name);
    glUniform2f(location, uValue.x, uValue.y);
}

} // namespace fw
