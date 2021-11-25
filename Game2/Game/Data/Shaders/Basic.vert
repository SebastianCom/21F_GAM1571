#version 120

attribute vec2 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

uniform vec2 u_ObjectScale;
uniform vec2 u_Offset;

uniform vec2 u_CameraPosition;
uniform vec2 u_ProjectionScale;

uniform float u_SpriteSheetWidth;
uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

varying vec4 v_Color;
varying vec2 v_UVCoord;





void main()
{
    vec2 objectScale = u_ObjectScale;
    vec2 objectTranslation = u_Offset;
    vec2 cameraPos = u_CameraPosition;
    vec2 viewTranslation = cameraPos * -1;
    vec2 projScale = u_ProjectionScale;

    vec2 objectSpacePosition = a_Position;
    vec2 worldSpacePosition = objectSpacePosition * objectScale + objectTranslation;
    vec2 viewSpacePosition = worldSpacePosition + viewTranslation;
    vec2 clipSpacePosition = viewSpacePosition * projScale;

    gl_Position = vec4( clipSpacePosition, 0.0, 10.0 );

//    vec2 pos = a_Position*u_ObjectScale + u_Offset;
//    gl_Position = vec4( pos/50.0, 0.0, 1.0 );

    v_Color = a_Color;
    
	//"Width":	512,
	//"Height":	512,
    //"Name":	"ground_05",
    //    "X":	195,
    //    "Y":	448,
    //    "W":	64,
    //    "H":	64
    //vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // bl
//
//    vec2 uvScale = vec2( 64.0/512.0, 64.0/512.0 );
//    vec2 uvOffset = vec2( 195.0/512.0, 448.0/512.0 );
    vec2 uvScale = vec2( u_UVScale.x/u_SpriteSheetWidth, u_UVScale.y/u_SpriteSheetWidth );
    vec2 uvOffset = vec2(u_UVOffset.x/u_SpriteSheetWidth,u_UVOffset.y/u_SpriteSheetWidth );

    v_UVCoord = a_UVCoord*uvScale + uvOffset;
}
