#ifndef WORLD_CPP
#define WORLD_CPP

#include "./shared.cpp"
#include "rlgl.h"

void GenWorld(long seed);

void DrawWorld(int posY, int posX);


void DrawMatrix(){
    rlPushMatrix();
        rlTranslatef(0, 25*50, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, 50);
    rlPopMatrix();
}

void DrawWorld(int posY, int posX){
    ClearBackground(GREEN);
}

#endif
