#include <iostream>
#include <raylib.h>
#include "shaderman.hpp"
#include "tui.hpp"
#include "SImage.hpp"



int main() {
    std::cout << "hello world\n";
    InitWindow(1080, 720, "MY SHADERTOY");
    Shader ppfx = LoadShader(0, "shader/pp.fs");

    int iTimeLoc = GetShaderLocation(ppfx, "iTime");
    int limiterLoc = GetShaderLocation(ppfx, "limiter");
    RenderTexture ppLayer = LoadRenderTexture(1080, 720);
    u_int8_t padding = 15;
    std::string imgPath = "";
    bool was_focused = false;
    ShaderToyImage si;
    
    SetWindowState(FLAG_VSYNC_HINT);
    float iTime = 0;
    while (!WindowShouldClose()) {
        iTime+=GetFrameTime();
        SetShaderValue(ppfx, iTimeLoc, &iTime, SHADER_UNIFORM_FLOAT);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float mS = (float)GetMouseX()/(float)GetScreenWidth();
            std::clog << mS << "\n";
            SetShaderValue(ppfx, limiterLoc, &mS, SHADER_UNIFORM_FLOAT);
        }
        //Actual drawing content
        BeginTextureMode(ppLayer);
            ClearBackground(BLACK);
            //DrawCircle(100, 100, 10, WHITE);//Test Circle
            //DrawRectangleLines(padding, 10, GetScreenWidth()-padding*2, 500, WHITE);
            si.draw();
        EndTextureMode();
        si.switchImage();
        //if (IsKeyPressed(KEY_R) || was_focused!=IsWindowFocused())  {
        if (IsKeyPressed(KEY_R))  {
            std::clog << "Reloading shader" << "\n";
            ShaderToyManager::reloadShader(&ppfx);
            iTimeLoc = GetShaderLocation(ppfx, "iTime");
        }
        if (IsKeyPressed(KEY_SPACE)) {
            TakeScreenshot("shader_screenshot.png");
        }
        //was_focused = IsWindowFocused();
        

        BeginDrawing();//present it to the scren
            ClearBackground((Color){10, 10, 18});
            BeginShaderMode(ppfx);
                DrawTextureRec(ppLayer.texture, (Rectangle){ 0, 0, (float)ppLayer.texture.width, (float)-ppLayer.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
            DrawFPS(10, 10);
        EndDrawing();
    }
    UnloadShader(ppfx);
    UnloadRenderTexture(ppLayer);
    CloseWindow();
    return 0;
}

