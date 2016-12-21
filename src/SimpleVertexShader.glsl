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
layout(location = 2) in vec3 vertexNormal_modelspace;

// output data
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 fragmentColor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;

// This is called for each vertex.
void main() {

  // Output position of the vertex, in clip space
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

  // Position of the vertex, in worldspace
  Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

  // Vector that goes from the vertex to the camera, in camera space.
  // In camera space, the camera is at the origin (0, 0, 0).
  vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace,1)).xyz;
  EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

  // Vector that goes from the vertex to the light, in camera space. M is
  // ommited because it's identity.
  vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace,1)).xyz;
  LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

  // Normal of the vertex. No special space for this one.
  Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace,0)).xyz;
  // only correct if Model Matrix does not scale model! Use its inverse transpose if not.

  fragmentColor = vertexColor;
}
