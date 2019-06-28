#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
  vec2 TexCoordFlippedHorizontal = vec2(-TexCoord.x, TexCoord.y);
  FragColor= mix(texture(texture1, TexCoord), texture(texture2, TexCoordFlippedHorizontal), 0.4);
}
