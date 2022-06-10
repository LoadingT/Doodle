#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
namespace DoodleJumpV1
{
	class TileManager
	{
	public:
		Texture back, tiles;
		Sprite background, tilemap;
		TileManager();
	};
}

