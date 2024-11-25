#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

layout(std140) uniform ModelTransform {
    mat4 modelTransform;
};

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
   gl_Position = projectionMatrix * viewMatrix * modelTransform * position;
};


#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
   //vec4 color = vec4(1.0,1.0,1.0,1.0) * (1.0 - gl_FragCoord.z);  // Colore più scuro se lontano
   float linearDepth = (2.0 * 1.0) / (10.0 + 1.0 - gl_FragCoord.z * (10.0 - 1.0)); // Normalizza la profondità
   FragColor = vec4(1.0, 1.0, 1.0, 1.0) * (1.0 - linearDepth); // Regola il colore
};