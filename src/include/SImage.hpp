#pragma once
#include <raylib.h>
#include <string>
#include <fstream>

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
        }

        ~ShaderToyImage() {
            std::ofstream last(".last.txt");
            if (last.is_open()) {
                last<<imgPath;
                std::cout << imgPath << " saved" << "\n";
            } else {
                std::cerr << "Error opening file\n";
            }
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
                    ImageResize(&img, 500*aspect, 500);
                    imgText = LoadTextureFromImage(img);
                    first = false;
                }
                UnloadDroppedFiles(droppedFiles);
            }
        }
        
        void draw() {
            DrawTexture(imgText, 0, 0, WHITE);
        }
};