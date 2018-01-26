#version 330 core
layout (location =0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

// TODO: uncomment after text is working
//uniform mat4 projection;

void main()
{
    // TODO: uncomment after text is working
    //gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}