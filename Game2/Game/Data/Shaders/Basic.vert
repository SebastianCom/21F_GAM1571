#version 120

attribute vec2 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

uniform float u_ObjectScale;
uniform vec2 u_Offset;

varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
    vec2 objectScale = vec2(1,1);
    vec2 objectTranslation = vec2(0,0);
    vec2 cameraPos = vec2(0,0);
    vec2 viewTranslation = cameraPos * -1;
    vec2 projScale = vec2(1/20.0, 1/20.0);

    vec2 objectSpacePosition = a_Position;
    vec2 worldSpacePosition = objectSpacePosition * objectScale + objectTranslation;
    vec2 viewSpacePosition = worldSpacePosition + viewTranslation;
    vec2 clipSpacePosition = viewSpacePosition * projScale;

    gl_Position = vec4(clipSpacePosition, 0.0, 1.0);
    

//    vec2 pos = a_Position*u_ObjectScale + u_Offset;
//    gl_Position = vec4( pos/50.0, 0.0, 1.0 );

    v_Color = a_Color;
    
    vec2 uvScale = vec2( 0.1, 1.0 );
    vec2 uvOffset = vec2( 0.2, 0.0 );
    v_UVCoord = a_UVCoord*uvScale + uvOffset;
}
