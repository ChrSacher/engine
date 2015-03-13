#version 330                                                                        
                                                                                    
attribute vec3 position;                                             
                                                                                    
uniform mat4 WVP;                                                                  
                                                                                    
out vec3 TexCoord0;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    vec4 WVP_Pos = WVP * vec4(position, 1.0);                                      
    gl_Position = WVP_Pos.xyzw;                                                     
    TexCoord0   = position;                                                         
}