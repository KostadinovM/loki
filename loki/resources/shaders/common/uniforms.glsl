
//global uniform buffer for shared uniforms amongst shader programs
layout (std140) uniform global
{
    //transformations
    mat4 model;
    mat4 view;
    mat4 project;
};