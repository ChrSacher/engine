#version 120
 
attribute vec3 coord;
 
void main(void) 
{
  gl_Position = vec4(coord, 1);
  
}