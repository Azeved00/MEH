#ifndef WORLD_CPP
#define WORLD_CPP

#include "./shared.cpp"
#include <time.h>
#include "./FastNoiseLite.h"
#include "rlgl.h"
#include <vector>


class World 
{

public:
    World(Settings*,bool);
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


    int GeneratePoint(int,int);
    void DrawMatrix();
    void LoadTextures(); 
    void DrawTextureAt(Texture2D,int,int,float,float);
};

//-----------------------------------------------------------------

World::World(Settings* s, bool genNew = true)
{
    loaded = false;
    LoadTextures();
    
    if(genNew)
        seed = (unsigned long)  (time(NULL) * 10000);
    else 
        seed = s->getSeed();
    
    // Create and configure FastNoise object
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(0.005f);

    noiseData.resize(s->getMaxMapSize());
    this->debug = s->isDebug();
}

World::~World()
{
    //delete noise;
    //delete noiseData;
    //delete this;
}

int World::GeneratePoint(int posX, int posY)
{
    float v = noise.GetNoise((float)posX, (float)posY);
    if(v < -0.5)
        return 0;
    else if(v > 0.5)
        return 3;
    else
        return 1;
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
    loaded = true;
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
    for (int y = 0; y < screenHeight *1.5 ; y += TEXTURE_SIZE) 
    {
        for (int x = 0; x < screenWidth * 1.5; x += TEXTURE_SIZE) 
        {
            float px = x-(screenWidth/2);
            float py = y-(screenHeight/2);

            int texture = GeneratePoint(px, py);
            DrawTextureAt(grass,texture,0, px, py);
        }
    }
}

#endif
