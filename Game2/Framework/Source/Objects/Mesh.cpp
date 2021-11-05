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

void Mesh::Draw(ShaderProgram* pShader, float scale, vec2 pos, float time)
{
    // Setup uniforms.
    glUseProgram( pShader->GetProgram() );

    GLint u_ObjectScale = glGetUniformLocation( pShader->GetProgram(), "u_ObjectScale" );
    glUniform1f( u_ObjectScale, scale );

    GLint u_Offset = glGetUniformLocation( pShader->GetProgram(), "u_Offset" );
    glUniform2f( u_Offset, pos.x, pos.y );

    GLint u_Time = glGetUniformLocation( pShader->GetProgram(), "u_Time" );
    glUniform1f( u_Time, time );

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    //{ vec2(  0.0f, 0.0f),  255,255,255,255,  vec2(0.0f,0.0f) },
    //{ vec2( 10.0f,10.0f),  255,255,255,255,  vec2(1.0f,1.0f) },
    //{ vec2(-10.0f,10.0f),  255,255,255,255,  vec2(0.0f,1.0f) },

    // Get the attribute variable’s location from the shader.
    // Describe the attributes in the VBO to OpenGL.
    GLint a_Position = glGetAttribLocation( pShader->GetProgram(), "a_Position" );
    if( a_Position != -1 )
    {
        glEnableVertexAttribArray( a_Position );
        glVertexAttribPointer( a_Position, 2, GL_FLOAT, GL_FALSE, 20, (void*)0 );
    }

    //GLint a_Alpha = glGetAttribLocation( pShader->GetProgram(), "a_Alpha" );
    //if( a_Alpha != -1 )
    //{
    //    glEnableVertexAttribArray( a_Alpha );
    //    glVertexAttribPointer( a_Alpha, 1, GL_FLOAT, GL_FALSE, 12, (void*)8 );
    //}

    GLint a_UVCoord = glGetAttribLocation( pShader->GetProgram(), "a_UVCoord" );
    if( a_UVCoord != -1 )
    {
        glEnableVertexAttribArray( a_UVCoord );
        glVertexAttribPointer( a_UVCoord, 2, GL_FLOAT, GL_FALSE, 20, (void*)0 );
    }

    // Draw the primitive.
    glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
}

} // namespace fw
