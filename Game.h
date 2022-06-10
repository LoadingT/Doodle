#pragma once
#include "Platforms.h"
#include "Enemy.h"
#include "TileManager.h"
#include "Inteface.h"
#include "Score.h"
namespace DoodleJumpV1
{
    class Game
    {
        TileManager tilemanager;
        RenderWindow *window = new RenderWindow(VideoMode(512,512+128),"Doodle Jump!");
        Doodle *player = new Doodle(tilemanager.tilemap);
        Platforms* platforms = new Platforms(tilemanager.tilemap);
        Interface GameInterface;
        Score score;
        int h = 150;
        void Analyzer(Event event);
    public:
        void Controller();
        Game();
    };
}

