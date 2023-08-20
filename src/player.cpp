#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "./shared.cpp"
#include "./raylib.h"
#include "./graphics.cpp"

class Player : public Entity 
{
public:
    Camera2D camera;
    int frameCounter;
    bool allowMove;

    Player() : Entity( 0,0, YELLOW)
    {
        this->camera = { 0 };
        camera.target = {
            (float) this->posX * CELL_SIZE ,
            (float) this->posY * CELL_SIZE
        };
        camera.offset = 
        (Vector2){ 
            screenWidth/2.0f - CELL_SIZE/2.0f, 
            screenHeight/2.0f - CELL_SIZE/2.0f 
        }; 
        camera.rotation = 0.0f;
        camera.zoom = 1.5f;
    }
    
    void Reset()
    {
    }

    ~Player()
    {
        delete this;
    }

    void Update()
    {
        if(frameCounter == 25)
        {
            frameCounter = 0;
            allowMove = true;
        }

        if (IsKeyDown(KEY_W) && allowMove)
        {
            this->posY -= 1;
            allowMove = false;
        }
        
        if (IsKeyDown(KEY_S) && allowMove)
        {
            this->posY += 1;
            allowMove = false;
        }

        if (IsKeyDown(KEY_A) && allowMove){
            this->posX -= 1;
            allowMove = false;
        }

        if (IsKeyDown(KEY_D) && allowMove){
            this->posX += 1;
            allowMove = false;
        }

        camera.target = {
            (float) this->posX * CELL_SIZE ,
            (float) this->posY * CELL_SIZE
        };

        frameCounter++;
    }

    void DrawMenu()
    {
        DrawRectangle(0, 0, screenWidth*0.15, 120, DARKGRAY);
        std::string s;

        s = std::to_string(posX) + ", " + std::to_string(posY);
        DrawText(s.c_str(),10,70,20,BLACK);
    }

};


#endif
