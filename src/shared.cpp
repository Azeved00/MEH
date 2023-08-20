#ifndef SHARED_CPP
#define SHARED_CPP

#include "raylib.h"
#include "math.h"
#include <string>

static const int screenHeight = 450;
static const int screenWidth = 800;

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
        Rectangle hitbox;

        Entity(int posX, int posY, Color color)
        {
            this->hitbox = {(float) posX, (float) posY, screenWidth*0.12, screenHeight*0.20};
            this->color = color;
        }

        void Update(){
        }

        void Draw()
        {
            DrawRectangleRec( hitbox, this->color);
            /*DrawRectanglePro(
                    hitbox,
                    {},
                    0,
                this->color);*/
            //DrawText(std::to_string(speed).c_str(),this->posX,this->posY,10,BLACK);
        }
};

#endif
