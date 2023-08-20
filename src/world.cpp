#ifndef WORLD_CPP
#define WORLD_CPP

#include "./shared.cpp"
#include <time.h>
#include "./FastNoiseLite.h"
#include "rlgl.h"
#include <vector>

static const int TEXTURE_SIZE= 16;

class World 
{

public:
    World(int,unsigned long,bool);
    ~World();
    void Draw(int, int);
    
    
private:
    bool loaded;
    bool debug;
    unsigned long seed;
    Texture2D grass;
    Texture2D rocks;
    Texture2D water;
    std::vector<int> noiseData;
    FastNoiseLite noise;


    void Generate(unsigned long,int);
    void DrawMatrix();
    void LoadTextures(); 
    void DrawTextureAt(Texture2D,int,int,float,float);
};

//-----------------------------------------------------------------

World::World(int size,unsigned long pseed=0, bool debug = 0)
{
    loaded = false;
    if(pseed == 0)
        seed = (unsigned long)  (time(NULL) * 10000);
    else 
        seed = pseed;
    
    // Create and configure FastNoise object
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

    noiseData.resize(size*size);
}

World::~World()
{
    //delete this;
}

void World::Generate(unsigned long seed = 0, int mapSize = 200)
{
    for (int y = 0; y < 128; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            float v = noise.GetNoise((float)x, (float)y);
            if(v < -0.5)
                noiseData[y*mapSize + x] = 0;
            else if(v > 0.5)
                noiseData[y*mapSize + x] = 2;
            else
                noiseData[y*mapSize + x] = 1;
        }
    }
}

void World::DrawTextureAt(Texture2D texture, int textureX, int textureY, float posX, float posY)
{
    DrawTextureRec(grass, 
            (Rectangle){(float)TEXTURE_SIZE*textureX, 
            (float)TEXTURE_SIZE*textureY,TEXTURE_SIZE,TEXTURE_SIZE}, 
            (Vector2) {posY, posX},
            WHITE);
}

void World::LoadTextures()
{
    Image grassImage = LoadImage("./assets/Miniworld/Ground/Grass.png");
    if(!IsImageReady(grassImage)){
        printf("Image Grass.png is not ready\n");
        return;
    }
    grass = LoadTextureFromImage(grassImage);
}

void World::DrawMatrix()
{
    rlPushMatrix();
        rlTranslatef(0, 25*CELL_SIZE, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, CELL_SIZE);
    rlPopMatrix();
}

void World::Draw(int posY, int posX)
{
    if(!loaded)
        LoadTextures();
    if(debug)
        DrawMatrix();

    // Draw repeating background texture
    for (int y = 0; y < screenHeight *1.5 ; y += TEXTURE_SIZE) {
        for (int x = 0; x < screenWidth * 1.5; x += TEXTURE_SIZE) {
            float halfW = (screenWidth/2);
            float halfH = (screenHeight/2);
            DrawTextureAt(grass,1,0, x-halfW,y-halfH);
        }
    }
}

#endif
