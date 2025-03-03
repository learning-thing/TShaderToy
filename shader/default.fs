#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform float iTime;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main() {
    // Texel color fetching from texture sampler

    float factor = sin(fragTexCoord.y+iTime);
    vec2 offste = vec2(-.25+factor*.1, 0);
    

    vec4 source = texture(texture0, fragTexCoord+offste);
    // Calculate final fragment color
    finalColor = source;
}