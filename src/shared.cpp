#ifndef SHARED_CPP
#define SHARED_CPP

#include "raylib.h"
#include "math.h"
#include <string>


typedef enum State {
    gamePlay,
    pause,
    titleScreen,
    settings,
    generatingWorld,
    exitGame
} State;


static const int screenHeight = 480;
static const int screenWidth = 800;
static const int CELL_SIZE= 16;
static const int targetFPS = 60;

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
