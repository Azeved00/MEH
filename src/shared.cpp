#ifndef SHARED_CPP
#define SHARED_CPP

#include <math.h>
#include <string>

#include "../libs/raylib.h"

namespace  State
{
    typedef enum State {
        GamePlay,
        Pause,
        TitleScreen,
        Settings,
        GeneratingWorld,
        LoadingWorld,
        ExitGame,
        Battle,
        Pokedex,
        Save
    } State;
}

static const int TEXTURE_SIZE= 16;
static const int screenHeight = 480;
static const int screenWidth = 800;
static const int CELL_SIZE= 16;
bool debug = false;

//--------------------------- Entity ----------------------------
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
                UnloadImage(image);
            }

        }

        ~Entity()
        {
            UnloadTexture(texture);
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
                        (Vector2) {(float) posX * CELL_SIZE, (float) posY * CELL_SIZE},
                        WHITE);
            }
        }
};

//--------------------------- Settings ----------------------------
class Settings 
{

public:
    Settings();
    void Save();
    //Settings Load();

    int getTargetFPS();
    int getRenderDistance();
    float getZoom();
    
    unsigned long getSeed();
    bool isDebug();
    int getMaxMapSize();

private:
    static const char* path;
    
    int targetFPS;
    int render;
    float zoom;

    unsigned long seed;
    bool debug;
    int maxSize;
};

Settings::Settings()
{
    this->targetFPS = 70;
    this->render = 7;
    this->zoom = 2.5f;

    this->seed = 2;
    this->debug = true;
    this->maxSize = 200;
}

int Settings::getTargetFPS(){ return this->targetFPS; };
int Settings::getRenderDistance(){ return this->render; };
float Settings::getZoom(){ return this->zoom; };

unsigned long Settings::getSeed(){ return this->seed; };
bool Settings::isDebug(){ return this->debug; };
int Settings::getMaxMapSize(){ return this->maxSize; };

const char* Settings::path = "$HOME/.config/meh/settings.txt";
void Settings::Save(){}
//Settings Settings::Load(){}
#endif
