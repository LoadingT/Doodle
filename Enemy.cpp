#include "Enemy.h"
namespace DoodleJumpV1
{
    void Enemy::Stay()
    {
        canMove = false; dx = 0;
    }
    void Enemy::Left()
    {
        canMove = true; dx = -5;
        if (!is_fleeped) Fleep();

    }
    void Enemy::Right()
    {
        canMove = true; dx = 5;
        if (is_fleeped) Fleep();
    }
    Enemy::Enemy(Sprite sprite)
    {
        this->sprite = sprite;
    }

    bool Enemy::CheckOnJump(Platform *tile[10])
    {
        int w = 9 * 6, h = 16 * 6, pw = 24 * 4, ph = 12 * 4;
        Vector2f pos = this->position;
        if (is_fleeped) pos.x -= w;
        for (int i = 0; i < 10; i++)
        {
            Vector2f platPos = tile[i]->sprite->getPosition();
            if ((pos.x + w > platPos.x) && (pos.x + pw < platPos.x + pw + w) && (pos.y + h > platPos.y) && (pos.y < platPos.y) && dy)
            {
                if (tile[i]->type == PlatformType::Rotted)
                {
                    RotPlatform* p = dynamic_cast<RotPlatform*>(tile[i]);
                    if (p->destroyed) return false;
                    else
                    {
                        p->jumped = true;
                    }
                }
                return true;
            }
        }
        return false;
    }

    Enemy::Enemy() {}

    void Enemy::Move(Vector2f position)
    {
        this->position += position;
        if (this->position.x < 0)
            this->position.x = 512 - position.x;
        else if (this->position.x > 512)
            this->position.x = 0 + position.x;
    }
    void Enemy::Set_Sprite_Scale(float x, float y) { this->sprite.setScale(x, y); }

    void Enemy::Fleep()
    {
        if (!is_fleeped)
        {
            Set_Sprite_Scale(-6, 6);
            Move(Vector2f(9 * 6, 0));
        }
        else
        {
            Set_Sprite_Scale(6, 6);
            Move(Vector2f(-9 * 6, 0));
        }
        is_fleeped = !is_fleeped;
    }
    Vector2f Enemy::Get_Position() { return this->position; }
    void Enemy::Set_Position(Vector2f pos) { this->position = pos;  }
    void Enemy::Draw(RenderWindow* window)
    {
        sprite.setPosition(position);
        window->draw(this->sprite);
    }
    Doodle::Doodle(Sprite sprite):Enemy(sprite)
    {
        this->sprite.setScale(6, 6); position.x = 256; position.y = 128;
        this->sprite.setTextureRect(IntRect(0, 0, 9, 16));
    }
    void Doodle::Physics()
    {
        dy += 0.2;
        this->position.y += dy;
        if (this->canMove)
        {
            if (this->position.x < 0)
            {
                this->position.x = 512 + dx;
            }
            else if (this->position.x > 512)
            {
                this->position.x = 0 + dx;
            }
            else
                this->position.x += dx;
        }

        if (this->position.y > 512 + 128)
        {
            if (GodMode) dy = -8;
            else
                WantStopGame = true;
        }
    } 
}