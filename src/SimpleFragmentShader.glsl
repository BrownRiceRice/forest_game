#version 330 core

in vec3 fragmentColor;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec3 color;

uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

// Runs on every fragment.
void main() {

  // Light emission properties, probably as uniforms.
  vec3 LightColor = vec3(1, 1, 1);
  float LightPower = 50.0f;

  // Material properties
  vec3 MaterialDiffuseColor = fragmentColor;
  vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
  vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

  // Distance to the light
  float distance = length( LightPosition_worldspace - Position_worldspace );

  // Normal of the computed fragment, in camera space.
  vec3 n = normalize( Normal_cameraspace );
  // Direction of the light (from the fragment to the light)
  vec3 l = normalize( LightDirection_cameraspace );
  // Cosine of the angle b/t the normal and light direction clamped above 0.
  float cosTheta = clamp( dot( n,l ), 0,1 );

  // Eye vector (towardl the camera)
  vec3 E = normalize( EyeDirection_cameraspace );
  // Direction in which the triangle reflects the light
  vec3 R = reflect( -l, n );
  // Cosine of the angle b/t the Eye vector and Reflect vector clamped to 0.
  float cosAlpha = clamp( dot( E,R ), 0,1 );

  color = MaterialAmbientColor +
      MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
      MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
}
