#version 330 core

out vec4 FragColor;

uniform vec4 uOurColor;

void main()
{
    //FragColor = vec4(0.0, 0.0, 1.0, 1.0f); // Red color
    FragColor = uOurColor;
}
