#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;
namespace DoodleJumpV1
{
	enum class GameCondition
	{
		IsMenu, IsPlaying, IsDead, IsScore, IsChange, Exit, Easy, Medium, Hard
	};

	class Button
	{
	public:
		GameCondition setgc;
		RectangleShape own;
		Text text;
		Color onPressed =Color::Red, onVisit = Color::Yellow, color = Color::Blue;
		bool Pressed(RenderWindow* window);
		void Draw(RenderWindow* window);
		Button(Vector2f pos, Text text);
	};


	class Interface
	{
	public:
		GameCondition condition = GameCondition::IsMenu;
		Sprite BackGround;
		vector <Button> buttons;

		Font font;
		Text text;

		Interface();
		void Draw(RenderWindow* window);
		void Menu();
		void Change();
		void Dead(int score);
		void ScoreInfo();
		void SetButtonSettings();
		void CheckPressButton(RenderWindow* window);
	};
}

