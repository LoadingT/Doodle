#pragma once
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "Inteface.h"
using namespace sf;
namespace DoodleJumpV1
{
    enum class PlatformType
    {
        DefaultPlatform=0, MovedPlatform, Rotted
    };
    class Platform
    {
    public:
        Platform(Sprite sprite);
        Platform() {}
        PlatformType type = PlatformType::DefaultPlatform;
        Sprite *sprite = nullptr;
        void Draw(RenderWindow* window);
        virtual void Action(){ };
    };
    class RotPlatform : public Platform
    {
    public:
        int dy = 5;
        Sprite* left=nullptr, * right=nullptr;
        RotPlatform(Sprite sprite);
        virtual void Action() override;
        bool destroyed = false, jumped = false;
    };
    class MobilePlatform : public Platform
    {
    public:
        MobilePlatform(Sprite sprite) :Platform(sprite) { this->type = PlatformType::MovedPlatform; };
        float dx = 5;
        virtual void Action() override;
    };
    class Platforms
    {
    public:
        const int pcount = 10;
        float MaxY;
        GameCondition type = GameCondition::Easy;
        Platform *tile[10];
        Sprite map;
        Platforms(Sprite Tilemap);
        void SetRandomPlatform(int ind);
        void Move_Down(float dx,Score& score);
        void Draw(RenderWindow * window);
    };
}
