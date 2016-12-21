#version 330 core
// vertex shader
// vec3 is a vector of 3 components in GLSL.  Similiar but different to glm::vec3.
//   (both just need 3 components)
// layout(location = 0) is the buffer we use to feed the vertexPosition_modelspace
//   attribute. We have to tell OpenGL which buffer corresponds to which input, by
//   setting the layout to the same value as the 1st param to glVertexAttribPointer (0 doesn't matter,
//   just has to be the same).
// vertexPosition_modelspace could have any other name, but it contains the positino of the vertex
//   for each run of the shader.
// in means that this is input data.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;


// This is called for each vertex.
void main() {
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

  fragmentColor = vertexColor;
}
