#ifndef SHARED_CPP
#define SHARED_CPP

#include "raylib.h"
#include "math.h"
#include <string>

static const int screenHeight = 480;
static const int screenWidth = 800;
static const int  CELL_SIZE= 32;
Vector2 offset = {
    screenWidth%CELL_SIZE,
    screenHeight%CELL_SIZE
};
static const int targetFPS = 60;

typedef enum State {
    GamePlay,
    Pause,
    TitleScreen,
    Settings,
    GeneratingWorld
} State;

class Entity{
    public: 
        Color color;
        int posX;
        int posY;

        Entity(int posX, int posY, Color color)
        {
            this->posX = posX;
            this->posY = posY;
            this->color = color;
        }

        void Update()
        {
        }

        void Draw()
        {
            DrawRectangle( 
                (float) posX * CELL_SIZE,
                (float) posY * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE,
                this->color);
        }
};

#endif
