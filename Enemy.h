#pragma once
#include <SFML/Graphics.hpp>
#include "Platforms.h"
using namespace sf;

namespace DoodleJumpV1
{
    class Enemy
    {
    public:
        float speed = 1;
        float dy = 3, dx = 0;
        bool is_fleeped = false;
        bool canMove = false;
        Vector2f position;
        Sprite sprite;
        Enemy(Sprite sprite);
        Enemy();
        void Move(Vector2f position);
        void Set_Sprite_Scale(float x, float y);
        void Fleep();
        Vector2f Get_Position();
        void Set_Position(Vector2f pos);
        void Draw(RenderWindow* window);
        void Left();
        void Right();
        void Stay();
        bool CheckOnJump(Platform* tile[10]);
    };
    class Doodle : public Enemy
    {
    public:
        bool GodMode = false;
        bool move_to = false;
        bool WantStopGame = false;
        Doodle(Sprite sprite);
        void Physics();
        Doodle() {};
    };
}