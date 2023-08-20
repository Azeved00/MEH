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
    exitGame,
    battle,
    Pokedex,
    Save
} State;


static const int TEXTURE_SIZE= 16;
static const int screenHeight = 480;
static const int screenWidth = 800;
static const int CELL_SIZE= 16;
static const int targetFPS = 60;

class Entity{
    public: 
        int posX;
        int posY;
        Color color;
        bool loaded;
        Texture2D texture;

        Entity(int posX, int posY, const char* path,Color color = BLACK)
        {
            this->posX = posX;
            this->posY = posY;
            this->color = color;

            Image image = LoadImage(path);
            if(!IsImageReady(image))
            {
                printf("Image %s is not ready\n",path);
                loaded = false;
            }
            else
            {
                texture = LoadTextureFromImage(image);
                loaded = true;
            }
        }

        void Update()
        {
        }

        void Draw()
        {
            if(!loaded)
            {
                DrawRectangle( 
                    (float) posX * CELL_SIZE,
                    (float) posY * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE,
                    this->color);
            }
            else
            {
                DrawTextureRec(texture, 
                        (Rectangle){
                            (float)TEXTURE_SIZE*0, 
                            (float)TEXTURE_SIZE*0,
                            TEXTURE_SIZE,
                            TEXTURE_SIZE
                        }, 
                        (Vector2) {posX * CELL_SIZE, posY * CELL_SIZE},
                        WHITE);
            }
        }
};

#endif
