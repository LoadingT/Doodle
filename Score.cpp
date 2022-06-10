#include "Score.h"
#include <fstream>
using namespace std;
namespace DoodleJumpV1
{
	Score::Score()
	{
		if (this->font.loadFromFile("Resources\\Veles-Regular.0.9.2.otf"))
		{
			printf("font loaded\n");
		}
		this->text.setFont(this->font);
		this->text.setString("Score: 0");
		this->text.setFillColor(Color::Yellow);
		this->text.setPosition(0, 0);
	}
	void Score::update()
	{
		this->score++;
		printf("\n%d", score);
		std::string text = "Score: " + std::to_string(score);
		this->text.setString(text);
	}
	void Score::Draw(RenderWindow* window)
	{
		window->draw(text);
	}

	void Score::Presentation(RenderWindow* window)
	{
		ifstream file("score.txt");
		Info info;
		if (file.is_open())
		{
			for (int i = 0; i < 3; i++)
			{
				file >> info.Name;
				file >> info.count;
				text.setString(to_string(i + 1) + ". " + info.Name + " : " + to_string(info.count));
				text.setPosition(175, 100 + i*35);
				window->draw(text);
			}
		}
		text.setString("");
		text.setPosition(0, 0);
	}

	bool Score::Check()
	{
		ifstream file("score.txt");
		Info info[3];
		if (file.is_open())
		{
			for (int i = 0; i < 3; i++)
			{
				file >> info[i].Name;
				file >> info[i].count;
			}
			for (int i = 0; i < 3; i++)
			{

				if (info[i].count < this->score)
				{
					return true;
				}
			}
			return false;
		}
		return true;
	}

	void Score::SaveAll(std::string Name)
	{
		ifstream file("score.txt");
		Info info[3];
		if (file.is_open())
		{
			for (int i = 0; i < 3; i++)
			{
				file >> info[i].Name;
				file >> info[i].count;
			}
			for (int i = 0; i < 3; i++)
			{
				
				if (info[i].count < this->score)
				{
					for (int j = 1; j >= i; j--)
					{
						info[j + 1] = info[j];
					}
					info[i].count = this->score;
					info[i].Name = Name;
					break;
				}
				
			
			}
			file.close();
			ofstream fout("score.txt");
			for (int i = 0; i < 3; i++)
			{
				fout << info[i].Name << " " << info[i].count << endl;
			}
		}
		else
		{
			ofstream fout("score.txt");
			fout << Name << " " << score << endl;
			for (int i = 1; i < 3; i++)
			{
				fout << info[i].Name << " " << info[i].count << endl;
			}
			
		}
	}
}