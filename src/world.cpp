#ifndef WORLD_CPP
#define WORLD_CPP

#include "./shared.cpp"
#include "rlgl.h"


bool loaded = false;
static const int TEXTURE_SIZE= 16;
Texture2D grass;

void GenWorld(long);
void DrawWorld(int, int);
void DrawTexture(Texture2D,int,int);
void LoadTextures(); 
void DrawMatrix();

//-----------------------------------------------------------------

void DrawTextureAt(Texture2D texture, int textureX, int textureY, float posX, float posY){
    
    DrawTextureRec(grass, 
            (Rectangle){(float)TEXTURE_SIZE*textureX, 
            (float)TEXTURE_SIZE*textureY,TEXTURE_SIZE,TEXTURE_SIZE}, 
            (Vector2) {posY, posX},
            WHITE);
}

void LoadTextures(){
    Image grassImage = LoadImage("./assets/Miniworld/Ground/Grass.png");
    if(!IsImageReady(grassImage)){
        printf("Image Grass.png is not ready\n");
        return;
    }

    loaded = true;
    grass = LoadTextureFromImage(grassImage);
}

void DrawMatrix(){
    rlPushMatrix();
        rlTranslatef(0, 25*CELL_SIZE, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, CELL_SIZE);
    rlPopMatrix();
}

void DrawWorld(int posY, int posX){
    if(!loaded)
        LoadTextures();

    ClearBackground(BLACK);

    // Draw repeating background texture
    for (int y = 0; y < screenHeight *1.5 ; y += TEXTURE_SIZE) {
        for (int x = 0; x < screenWidth * 1.5; x += TEXTURE_SIZE) {
            float halfW = (screenWidth/2);
            float halfH = (screenHeight/2);
            DrawTextureAt(grass,1,0, x-halfW,y-halfH);
        }
    }

}

#endif
