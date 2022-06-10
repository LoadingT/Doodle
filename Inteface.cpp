#include "Inteface.h"

namespace DoodleJumpV1
{
	Interface::Interface()
	{

		if (this->font.loadFromFile("Resources\\20443.otf"))
		{
			printf("interface font loaded\n");
		}
		this->text.setFont(this->font);
		this->text.setString("Choose what do you want =)");
		this->text.setPosition(64, 512);
		this->text.setFillColor(Color::Blue);
		this->text.setCharacterSize(24);
		this->condition = GameCondition::IsMenu;
		SetButtonSettings();
	}

	void Interface::CheckPressButton(RenderWindow* window)
	{
		switch (this->condition)
		{
		case(GameCondition::IsMenu):
			for (int i = 0; i < 3; i++)
			{
				if (this->buttons[i].Pressed(window))
				{
					this->condition = this->buttons[i].setgc;
					break;
				}
			}
			break;
		case(GameCondition::IsDead):
			if (this->buttons[3].Pressed(window))
			{
				this->condition = this->buttons[3].setgc;
				break;
			}
			break;
		case(GameCondition::IsChange):
			for (int i = 4; i < 7; i++)
			{
				if (this->buttons[i].Pressed(window))
				{
					this->condition = this->buttons[i].setgc;
					break;
				}
			}
			break;
		case(GameCondition::IsScore):
		{
			if (this->buttons[3].Pressed(window))
			{
				this->condition = this->buttons[3].setgc;
				break;
			}
		}
		break;
		}
	}
	void Interface::Menu()
	{
		text.setString("Choose what do you want!");
	}
	void Interface::Change()
	{
		text.setString("Choose complexity!");
	}

	void Interface::ScoreInfo()
	{
		text.setString("Enter name and press enter!");
	}

	void Interface::Dead(int score)
	{
		text.setString("You're died! Your score : " + std::to_string(score));
	}
	void Interface::SetButtonSettings()
	{
		this->buttons.push_back(Button(Vector2f(175,150),Text(String("Start"),this->font)));
		this->buttons.push_back(Button(Vector2f(175, 250), Text(String("Score"), this->font)));
		this->buttons.push_back(Button(Vector2f(175, 350), Text(String("Exit"), this->font)));
		this->buttons.push_back(Button(Vector2f(175, 350), Text(String("Menu"), this->font)));
		this->buttons.push_back(Button(Vector2f(175, 150), Text(String("Easy"), this->font)));
		this->buttons.push_back(Button(Vector2f(175, 250), Text(String("Medium"), this->font)));
		this->buttons.push_back(Button(Vector2f(175, 350), Text(String("Hard"), this->font)));
		this->buttons[0].setgc = GameCondition::IsChange;
		this->buttons[1].setgc = GameCondition::IsScore;
		this->buttons[2].setgc = GameCondition::Exit;
		this->buttons[3].setgc = GameCondition::IsMenu;
		this->buttons[4].setgc = GameCondition::Easy;
		this->buttons[5].setgc = GameCondition::Medium;
		this->buttons[6].setgc = GameCondition::Hard;
	}

	void Interface::Draw(RenderWindow *window)
	{
		window->draw(BackGround);
		window->draw(this->text);

		switch (this->condition)
		{
		case(GameCondition::IsMenu):
			for (int i = 0; i < 3; i++)
				buttons[i].Draw(window);
			break;
		case(GameCondition::IsScore):
			buttons[3].Draw(window);
			break;
		case(GameCondition::IsDead):
			buttons[3].Draw(window);
			break;
		case(GameCondition::IsChange):
			for (int i = 4; i < 7; i++)
				buttons[i].Draw(window);
			break;
		default:
			break;
		}
	}
	bool Button::Pressed(RenderWindow* window)
	{
		return own.getGlobalBounds().contains((Vector2f)sf::Mouse::getPosition(*window));

	}
	void Button::Draw(RenderWindow* window)
	{
		if (own.getGlobalBounds().contains((Vector2f)sf::Mouse::getPosition(*window)))
		{
			own.setFillColor(onVisit);
			this->text.setFillColor(sf::Color::Red);
		}
		else
		{
			own.setFillColor(color);
			this->text.setFillColor(sf::Color::White);
		}
		window->draw(own);
		window->draw(text);
	}
	Button::Button(Vector2f pos, Text text)
	{
		this->text = text;
		this->text.setPosition(pos + Vector2f(50, 10));
		this->text.setFillColor(sf::Color::White);
		own.setOutlineColor(sf::Color::Cyan);
		own.setOutlineThickness(3);
		own.setPosition(pos);
		own.setSize(Vector2f(200, 50));
		this->text.setCharacterSize(24);
	}
}
