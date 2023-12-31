#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../libs/raylib.h"

#include "./shared.cpp"

const int playerMenuOptions = 6;
const char* playerMenuList[] = {"Pokemon","Pokedex","Bag","Settings","Save","Quit"};

class Player : public Entity 
{
public:
    Camera2D camera;
    int frameCounter;
    bool allowMove;
    bool openMenu;
    int selectedMenu;

    Player(Settings* s) : Entity( 0,0, "./assets/Miniworld/Characters/Champions/Gangblanc.png")
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
        camera.zoom = s->getZoom();

        selectedMenu = 0;
        openMenu = false;
    }
    
    ~Player()
    {
        //delete this;
    }

    State::State Update()
    {
        if(frameCounter >= 15)
        {
            frameCounter = 0;
            allowMove = true;
        }

        if(!openMenu)
        {
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
        else
        {
            if(IsKeyPressed(KEY_S))
            {
                selectedMenu++;
                if(selectedMenu >= playerMenuOptions)
                    selectedMenu=0;
            }
            if(IsKeyPressed(KEY_W))
            {
                selectedMenu--;
                if(selectedMenu < 0)
                    selectedMenu=playerMenuOptions-1;
            }
            if(IsKeyPressed(KEY_ENTER))
            {
                if(selectedMenu == 5){
                    return State::TitleScreen;
                }
                
            }
        }
        return State::GamePlay;
    }


    void DrawMenu()
    {
        if(!openMenu) return;

        DrawRectangle(screenWidth*0.7, 0, screenWidth*0.30, 6*45+20, DARKGRAY);


        for(int i = 0; i < playerMenuOptions; i++)
        {
            DrawText(playerMenuList[i],screenWidth*0.7 + 10,10 + i*45,35,selectedMenu == i ? WHITE : BLACK);
        }
    }

    void DrawHud()
    {
        DrawRectangle(0, 0, screenWidth*0.15, 120, DARKGRAY);
        std::string s;

        s = std::to_string(posX) + ", " + std::to_string(posY);
        DrawText(s.c_str(),10,70,20,BLACK);

        DrawMenu();
    }
};


#endif
