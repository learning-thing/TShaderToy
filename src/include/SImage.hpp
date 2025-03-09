#pragma once
#include <raylib.h>
#include <string>
#include <fstream>
#include <iostream>

class ShaderToyImage {
    public:
        std::string imgPath;
        Image img;
        Texture imgText;
        float aspect = 1;
        FilePathList droppedFiles;
        bool first = true;

        ShaderToyImage() {
            std::ifstream last(".last.txt");
            if (last.is_open()) {
                last>>imgPath;
                std::cout << imgPath << " loaded" << "\n";
                
                img = LoadImage(imgPath.c_str());
                aspect = img.height/img.width;
                ImageResize(&img, 500*aspect, 500);
                imgText = LoadTextureFromImage(img);
                first = false;
            }
            last.close();

        }

        ~ShaderToyImage() {
            std::ofstream last(".last.txt");
            if (last.is_open()) {
                last<<imgPath;
                std::cout << imgPath << " saved" << "\n";
            } else {
                std::cerr << "Error opening file\n";
            }
            last.close();
        }

        void switchImage() {
            if (IsFileDropped()) {
                droppedFiles = LoadDroppedFiles();
                imgPath = droppedFiles.paths[0];
                if (imgPath.length()>1) {
                    if (!first) UnloadImage(img);
                    if (!first) UnloadTexture(imgText);
                    img = LoadImage(imgPath.c_str());
                    aspect = img.height/img.width;
                    //ImageResize(&img, 500, 500*aspect);
                    imgText = LoadTextureFromImage(img);
                    first = false;
                }
                UnloadDroppedFiles(droppedFiles);
            }
        }
        
        void draw() {
            DrawTexturePro(imgText, (Rectangle){0, 0, (float)img.width, (float)img.height}, (Rectangle){0, 0, (float)500, 500*aspect}, (Vector2){0, 0}, 0, WHITE);
        }
};