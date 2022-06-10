#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TField.h"
using namespace sf;
namespace DoodleJumpV1
{
	struct Info
	{
		std::string Name = "NoName";
		int count = 0;
	};
	class Score
	{
	public:
		int score = 0;
		Text text;
		Font font;
		TextField f;
		Score();
		bool Check();
		void Draw(RenderWindow* window);
		void update();
		void Presentation(RenderWindow* window);
		void SaveAll(std::string Name);
	};
}

