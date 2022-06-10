#include "Platforms.h"
#include <iostream>

namespace DoodleJumpV1
{

	Platforms::Platforms(Sprite map)
	{
		this->map = map;
		Sprite buff = this->map;
		buff.setScale(4, 4);
		buff.setTextureRect(IntRect(0, 16, 24, 12));
		this->tile[0] = new Platform(buff);
		this->tile[0]->sprite->setPosition(Vector2f(256, 512));
		for (int i = 1; i < 10; i++)
		{
			this->SetRandomPlatform(i);
			this->tile[i]->sprite->setPosition(Vector2f(5+ rand() % (512 - 24 * 4 - 5), this->tile[i - 1]->sprite->getPosition().y - 128));
		}

		this->MaxY = this->tile[9]->sprite->getPosition().y;
	}

	Platform::Platform(Sprite sprite)
	{
		this->sprite = new Sprite(sprite);
	}

	void Platform::Draw(RenderWindow* window)
	{
		window->draw(*this->sprite);
	}

	void Platforms::Draw(RenderWindow* window)
	{

		for (int i = 0; i < pcount; i++)
		{
			this->tile[i]->Action();
			
			if (this->tile[i]->type == PlatformType::Rotted ) 
			{
				RotPlatform* p = dynamic_cast<RotPlatform*>(tile[i]);
				if (p->destroyed) 
				{
					window->draw(*p->left);
					window->draw(*p->right);
				}
				else this->tile[i]->Draw(window);
			}
			else this->tile[i]->Draw(window);

		}
	}

	
	
	void Platforms::Move_Down(float dx,Score &score)
	{
		for (int i = 0; i < pcount; i++)
		{
			this->tile[i]->sprite->move(Vector2f(0, dx));
			if (this->tile[i]->type == PlatformType::Rotted)
			{
				RotPlatform* p = dynamic_cast<RotPlatform*>(tile[i]);
				if (p->destroyed)
				{
					p->left->move(0, dx);
					p->right->move(0, dx);
				}
			}
			if (this->tile[i]->sprite->getPosition().y > 512 + 128)
			{
				score.update();
				this->SetRandomPlatform(i);
				
				this->tile[i]->sprite->setPosition(Vector2f(5 + rand() % (512 - 24 * 4 - 5), this->MaxY));
			}
		}

	}

	void MobilePlatform::Action()
	{
		if (this->sprite->getPosition().x > 512-49) dx = -1*abs(dx);
		else if (this->sprite->getPosition().x < 1) dx = abs(dx);
		this->sprite->move(Vector2f(dx, 0));
	}

	RotPlatform::RotPlatform(Sprite sprite):Platform(sprite)
	{
		this->type = PlatformType::Rotted;
		left = new Sprite(sprite);
		right = new Sprite(sprite);
		left->setTextureRect(IntRect(24, 16, 12, 12));
		right->setTextureRect(IntRect(24+12, 16, 12, 12));
	}

	void RotPlatform::Action()
	{
		if (!destroyed && jumped)
		{
			this->destroyed = true;
			this->left->setPosition(sprite->getPosition());
			this->right->setPosition(sprite->getPosition());
			this->right->move(12, 0);
			this->left->rotate(-45);
			this->right->rotate(45);
		}
		if (destroyed && jumped && this->left->getPosition().y< 512 + 128)
		{
			this->right->move(0, this->dy);
			this->left->move(0, this->dy);
			this->left->rotate(rand()%4);
			this->right->rotate(rand() % 4);
		}
	}

	void Platforms::SetRandomPlatform(int ind)
	{
		Sprite buff = this->map; 
		buff.setScale(4, 4);
		if (this->type == GameCondition::Easy)
		{
			switch (rand() % 2)
			{
			case(0):
				buff.setTextureRect(IntRect(0, 16, 24, 12));
				this->tile[ind] = new Platform(buff);
				break;
			case(1):
				buff.setTextureRect(IntRect(24, 16, 24, 12));
				this->tile[ind] = new RotPlatform(buff);
				break;
			}
		}
		else if (this->type == GameCondition::Medium)
		{
			switch (rand() % 3)
			{
			case(0):
				buff.setTextureRect(IntRect(0, 16, 24, 12));
				this->tile[ind] = new Platform(buff);
				break;
			case(1):
				buff.setTextureRect(IntRect(24, 16, 24, 12));
				this->tile[ind] = new RotPlatform(buff);
				break;
			case(2):
				buff.setTextureRect(IntRect(48, 16, 24, 12));
				this->tile[ind] = new MobilePlatform(buff);
				break;
			default:
				break;
			}
		}
		else if (this->type == GameCondition::Hard)
		{
			switch (rand() % 2)
			{
			case(0):
				buff.setTextureRect(IntRect(24, 16, 24, 12));
				this->tile[ind] = new RotPlatform(buff);
				break;
			case(1):
			{
				buff.setTextureRect(IntRect(48, 16, 24, 12));

				MobilePlatform* plat = new MobilePlatform(buff);
				plat->dx = -5 + rand() % 11;
				this->tile[ind] = plat;
				break; }
			default:
				break;
			}
		}

	}

}