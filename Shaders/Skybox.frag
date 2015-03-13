#version 330                                                                        
                                                                                    
in vec3 TexCoord0;                                                                  
                                                                                    
out vec4 FragColor;                                                                 
                                                                                    
uniform samplerCube gCubemapTexture;                                                
uniform vec4 baseColor;                                                                                   
void main()                                                                         
{                                                                                   
    FragColor = baseColor + texture(gCubemapTexture, TexCoord0);                                
}
