#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "./shared.cpp"
#include "./raylib.h"
#include "./graphics.cpp"

class Player : public Entity 
{
public:
    Camera2D camera;
    Vector2 initial;

    Player() : Entity( screenWidth*0.5*0.88, screenHeight*0.7, YELLOW)
    {
        this->camera = { 0 };
        camera.target = {hitbox.x,hitbox.y};
        camera.offset = (Vector2){ screenWidth/2.0f - hitbox.width/2.0f, 
            screenHeight/2.0f - hitbox.height/2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        initial = { hitbox.x, hitbox.y };
    }
    
    void Reset()
    {

        hitbox.x = initial.x;
        hitbox.y = initial.y;
        camera.target = {hitbox.x, hitbox.y};
    }

    ~Player()
    {
        delete this;
    }

    void Update()
    {
        if (IsKeyDown(KEY_W))
            this->hitbox.y -= 1;
        
        if (IsKeyDown(KEY_S))
            this->hitbox.y += 1;

        if (IsKeyDown(KEY_A))
            this->hitbox.x -= 1;

        if (IsKeyDown(KEY_D))
            this->hitbox.x += 1;
    
        camera.target = {hitbox.x,hitbox.y};

        //gameTime = GetTime() - gameTime;
    }

    void DrawCar()
    {
        this->Draw();
    }

    void DrawHud()
    {
    }

};


#endif
