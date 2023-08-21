#ifndef WORLD_CPP
#define WORLD_CPP

#include <iostream>
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
    int size;
    int renderDistance;

    Texture2D grass;
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

    size = s->getMaxMapSize();
    renderDistance = s->getRenderDistance();
    noiseData.clear();
    noiseData.resize(size*size,-1);
    this->debug = s->isDebug();
}

World::~World()
{
    if(loaded)
        UnloadTexture(grassTexture);
    
    //delete noise;
    //delete noiseData;
    //delete this;
}

int World::GeneratePoint(int posX, int posY)
{
    int index = (posY+size/2) * size + posX+size/2;
    if(noiseData[index] != -1)
        return noiseData[index];

    std::cout << "Generating point: x=" << posX << " y=" << posY << "\n";
    float v = noise.GetNoise((float)posX, (float)posY);
    if(v < -0.5)
        noiseData[index] = 0;
    else if(v > 0.5)
        noiseData[index] = 3;
    else
        noiseData[index] = 1;

    return noiseData[index];
}

void World::DrawTextureAt(Texture2D texture, int textureX, int textureY, float posX, float posY)
{
    DrawTextureRec(grass, 
            (Rectangle){
                (float)TEXTURE_SIZE*textureX, 
                (float)TEXTURE_SIZE*textureY,
                TEXTURE_SIZE,
                TEXTURE_SIZE
            }, 
            (Vector2) {posX*CELL_SIZE, posY*CELL_SIZE},
            WHITE);
}

void World::LoadTextures()
{
    if(loaded) return;

    texture = LoadTexture("./assets/Miniworld/Ground/Grass.png");
    if(!IsTextureReady(texture)){
        printf("Texture Grass.png is not ready\n");
        return;
    }
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

void World::Draw(int posX, int posY)
{
    if(!loaded)
        LoadTextures();
    if(debug)
        DrawMatrix();


    for(int i = 1-renderDistance; i < renderDistance; i++)
    {
        for(int k = 1-renderDistance; k < renderDistance; k++)
        {
            float px = i + posX;
            float py = k + posY;
            
            int texture = GeneratePoint(px, py);
            DrawTextureAt(grass, texture, 0, px, py);
        }
    }
    


    // Draw repeating background texture
    /*for (int y = 0; y < screenHeight *1.5 ; y += TEXTURE_SIZE) 
    {
        for (int x = 0; x < screenWidth * 1.5; x += TEXTURE_SIZE) 
        {
            float px = x-(screenWidth/2);
            float py = y-(screenHeight/2);

        }
    }*/
}

#endif
