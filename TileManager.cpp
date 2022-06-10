#include "TileManager.h"
namespace DoodleJumpV1
{
	TileManager::TileManager()
	{
		this->back.loadFromFile("Resources\\background2.png");
		this->tiles.loadFromFile("Resources\\PERSOBILITIES.png");
		this->background.setTexture(this->back);
		this->tilemap.setTexture(this->tiles);
	}
}