#version 330 core

in vec3 fragmentColor;
out vec3 color;

// Runs on every fragment.
void main() {
  color = fragmentColor;
}
