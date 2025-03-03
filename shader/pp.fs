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
    

    vec4 source = texture(texture0, fragTexCoord);

    if (length(source)<=1.5+sin(iTime)*.15) {
        source = vec4(0);
    }

    // Calculate final fragment color
    finalColor = source;
}