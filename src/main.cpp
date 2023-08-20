#include "./shared.cpp"
#include "./player.cpp"
#include "./world.cpp"
#include "./raylib.h"
#include "./titleScreen.cpp"


State state = titleScreen;
Player* player;
World* world; 

void Update()
{
    switch(state)
    {
        case titleScreen:
            state = TitleScreen::Update(state);
            break;
        case gamePlay:
            player->Update();

            if(IsKeyPressed(KEY_P))
            {
                state = pause;
            }
            if(IsKeyPressed(KEY_ENTER))
            {
                player->openMenu = !player->openMenu;
            }
            break;
        case pause:
            if(IsKeyPressed(KEY_P))
                state = gamePlay;
            break;
        case settings:
            break;
        default:
            break;
    }
}

void Draw()
{
    ClearBackground(GREEN);
    
    BeginDrawing();
    
    if(state == gamePlay)
    {
        BeginMode2D(player->camera);
            world->Draw(player->posX,player->posY);
            player->Draw();
        EndMode2D();
    }

    //draw things allways in scren;
    switch(state)
    {
        case titleScreen:
            TitleScreen::Draw();
            break;
        
        case gamePlay:
            player->DrawHud();
            break;

        case pause:
            DrawRectangle(0, 0, screenWidth, screenHeight, GOLD);
            DrawText("PAUSE SCREEN", 20, 20, 40, ORANGE);
            DrawText("PRESS P too GAMEPLAY SCREEN", 120, screenHeight-30, 20, ORANGE);
            DrawText("PRESS ENTER too GAMEPLAY SCREEN", 120, screenHeight-60, 20, ORANGE);
            break;
        
        case settings:
            break;
        default:
            break;
    }
    DrawFPS(10,10);
    EndDrawing();
}

int main(void)
{
    SetTargetFPS(targetFPS);
    InitWindow( screenWidth, screenHeight, "Development: pokewilds");
    
    while (!WindowShouldClose() && state != exitGame)
    {
        Update();
        Draw();            
    }

    delete world;
    delete player;
    CloseWindow();

    return 0;
}


