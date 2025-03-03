#pragma once
#include <raylib.h>

class ShaderToyManager {
    private:

    public:
        static void reloadShader(Shader *shaders);
};


void ShaderToyManager::reloadShader(Shader *shaders) {
    UnloadShader(*shaders);
    *shaders = LoadShader(0, "shader/pp.fs");
}


