#include "Game.h"
namespace DoodleJumpV1
{
    void Game::Analyzer(Event event)
    {
        if (this->GameInterface.condition == GameCondition::IsPlaying)
        {
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case(Keyboard::Left):
                    player->Left();
                    break;
                case(Keyboard::Right):
                    player->Right();
                    break;
                case(Keyboard::Escape):
                    this->GameInterface.condition = GameCondition::IsMenu;
                    break;
                default:
                    break;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case(Keyboard::Left):
                    player->Stay();
                    break;
                case(Keyboard::Right):
                    player->Stay();
                    break;
                default:
                    break;
                }
            }
        }
        if (this->GameInterface.condition == GameCondition::IsDead)
        {
                this->score.f.handleInput(event);
                if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter)
                {
                    this->score.SaveAll(this->score.f.m_text);
                    this->score.score = -1;
                    this->GameInterface.condition = GameCondition::IsMenu;
                    this->score.f.m_text = "";
                }
            
            
        }
        if (event.type == Event::MouseButtonPressed)
        {

            this->GameInterface.CheckPressButton(this->window);
            if (this->GameInterface.condition == GameCondition::IsChange)
            {
                this->GameInterface.Change();
            }
            else if (this->GameInterface.condition == GameCondition::Easy || this->GameInterface.condition == GameCondition::Medium || this->GameInterface.condition == GameCondition::Hard)
            {
                
                this->platforms = new Platforms(this->tilemanager.tilemap);
                this->platforms->type = this->GameInterface.condition;
                this->player = new Doodle(this->tilemanager.tilemap);
                this->score.score = -1;
                this->score.update();
                
                this->GameInterface.condition = GameCondition::IsPlaying;
            }
            else if (this->GameInterface.condition == GameCondition::Exit)
            {
                window->close();
            }
        }

    }

    void Game::Controller()
    {
        this->window->setFramerateLimit(60);
        while (this->window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window->close();
                Analyzer(event);

            }
            switch (this->GameInterface.condition)
            {
            case(GameCondition::IsPlaying):

                if (player->WantStopGame)
                {
                    this->GameInterface.condition = GameCondition::IsDead;
                    player->WantStopGame = false;
                    break;
                }

                player->Physics();

                if (player->position.y < h)
                {
                    platforms->Move_Down(6.5,this->score);
                }
                else if (player->CheckOnJump(this->platforms->tile))
                {
                    player->dy = -8;
                }
                
                window->draw(this->tilemanager.background);
                platforms->Draw(this->window);
                player->Draw(this->window);
                score.Draw(window);
                window->display();

                break;
            case(GameCondition::IsMenu):
                this->GameInterface.Menu();
                this->GameInterface.Draw(this->window);
                window->display();
                break;
            case(GameCondition::IsDead):
                this->GameInterface.Draw(this->window);
                if (score.Check())
                {
                    this->score.f.Draw(window); this->GameInterface.ScoreInfo();
                }
                else
                {
                    this->GameInterface.Dead(score.score);
                }
                window->display();
                break;
            case(GameCondition::IsChange):
                this->GameInterface.Draw(this->window);
                window->display();
                break;
            case(GameCondition::IsScore):
                this->GameInterface.Draw(this->window);
                this->score.Presentation(this->window);
                window->display();
                break;
            }
            
        }
    }

    Game::Game()
    {
        window->setKeyRepeatEnabled(false);
        Sprite buff;
        buff = this->tilemanager.tilemap;
        buff.setTextureRect(IntRect(0, 0, 9, 16));
        this->player = new Doodle(buff);
        this->platforms = new Platforms(this->tilemanager.tilemap);

        this->GameInterface.BackGround = tilemanager.background;

    }
}