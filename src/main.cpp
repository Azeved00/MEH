#include "./shared.cpp"
#include "./player.cpp"
#include "./world.cpp"
#include "./raylib.h"
#include "./titleScreen.cpp"


State::State state = State::TitleScreen;
Settings* settings;
Player* player;
World* world; 

void Update()
{
    switch(state)
    {
        case State::TitleScreen:
            state = TitleScreen::Update(state);
            break;
        case State::GamePlay:
            state = player->Update();

            if(state == State::TitleScreen){
                delete world;
                delete player;
                state = State::TitleScreen;
            }

            if(IsKeyPressed(KEY_P))
            {
                state = State::Pause;
            }
            if(IsKeyPressed(KEY_ESCAPE))
            {
                player->openMenu = !player->openMenu;
            }
            break;
        case State::Pause:
            if(IsKeyPressed(KEY_P))
                state = State::GamePlay;
            break;
        case State::Settings:
            break;
        default:
            break;
    }

    if(state == State::GeneratingWorld){
        world = new World(settings);
        player = new Player(settings);
        state = State::GamePlay;
    }
    else if(state == State::LoadingWorld){
        world = new World(settings,false);
        player = new Player(settings);
        state = State::GamePlay;
    }
}

void Draw()
{
    ClearBackground(BLACK);
    
    BeginDrawing();
    
    if(state == State::GamePlay)
    {
        BeginMode2D(player->camera);
            world->Draw(player->posX,player->posY);
            player->Draw();
        EndMode2D();
    }

    //draw things allways in scren;
    switch(state)
    {
        case State::TitleScreen:
            TitleScreen::Draw();
            break;
        
        case State::GamePlay:
            player->DrawHud();
            break;

        case State::Pause:
            DrawRectangle(0, 0, screenWidth, screenHeight, GOLD);
            DrawText("PAUSE SCREEN", 20, 20, 40, ORANGE);
            DrawText("PRESS P too GAMEPLAY SCREEN", 120, screenHeight-30, 20, ORANGE);
            DrawText("PRESS ENTER too GAMEPLAY SCREEN", 120, screenHeight-60, 20, ORANGE);
            break;
        
        case State::Settings:
            break;
        default:
            break;
    }
    DrawFPS(10,10);
    EndDrawing();
}

int main(void)
{
    settings = new Settings();

    SetTargetFPS(settings->getTargetFPS());
    InitWindow( screenWidth, screenHeight, "Development: pokewilds");
    SetExitKey(KEY_NULL);

    while (!WindowShouldClose() && state != State::ExitGame)
    {
        Update();
        Draw();            
    }

    CloseWindow();

    return 0;
}


