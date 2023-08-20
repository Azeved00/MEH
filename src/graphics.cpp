#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "shared.cpp"
#include "raylib.h"
#include <string>

Texture roadTexture;

void InitiateGraphics()
{
    InitWindow( screenWidth, screenHeight, "Some Racing Game");
    
    Image roadImage = LoadImage("./assets/road.png");
    if(!IsImageReady(roadImage)){
        printf("Image ../assets/road.png is not ready\n");
        return;
    }

    roadTexture = LoadTextureFromImage(roadImage);
}


void DrawRoad()
{
    for(int i = 0; i < 5; i++)
    {
        DrawTexture(roadTexture, 0, -screenHeight*i, WHITE);
    }
}

#endif
