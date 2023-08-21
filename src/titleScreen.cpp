#include "./shared.cpp"
#include "./raylib.h"

namespace TitleScreen
{
    int selected = 0;
    static const int nOptions = 4; 
    const char* options[] = {"Start New Game","Custom Seed","Settings","Exit"};

    State::State Update(State::State in)
    {
        if ( IsKeyPressed(KEY_S) ){
            selected ++;
            if(selected >= nOptions)
                selected=0;
        }
        if ( IsKeyPressed(KEY_W) ){
            selected --;
            if(selected < 0)
                selected=nOptions-1;
        }

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            switch(selected){
                case 0:
                    return State::GeneratingWorld;
                    break;
                case 1:
                    return State::LoadingWorld;
                    break;
                case 2:
                    return State::Settings;
                    break;
                case 3:
                    return State::ExitGame;
                    break;
                default:
                    break;
            }
        }
        
        return in;

    }

    void Draw()
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
        DrawText("MENU SCREEN", 20, 20, 40, DARKGREEN);


        for(int i = 0; i < nOptions; i++)
        {
            DrawText(options[i],screenWidth*0.7 + 10,10 + i*45,35,selected == i ? WHITE : BLACK);
        }

    }
}

