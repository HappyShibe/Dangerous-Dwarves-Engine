#version 330

varying vec2 textureCo0;

uniform sampler2D diffuse;

void main()
{
  gl_FragColor = texture2D(diffuse, textureCo0);
}