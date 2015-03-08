attribute vec3 Position;
attribute vec2 TexCoord;
attribute vec3 Normal;

uniform mat4 viewProjection;
uniform mat4 modelMatrix;

out vec3 WorldPos;

void main()
{
    vec4 Pos4 = vec4(Position, 1.0);
    gl_Position = viewProjection * modelMatrix * Pos4;
    WorldPos = (modelMatrix * Pos4).xyz; 
}