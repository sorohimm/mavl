#include "Layer.h"

std::vector<sf::Sprite> Layer::GetTilesVector() const
{
    return tiles;
}

void Layer::SetOpacity(const int op)
{
    opacity = op;
}

void Layer::SetSprite(const sf::Sprite &inputSprite)
{
    tiles.push_back(inputSprite);
}

int Layer::GetOpacity() const
{
    return opacity;
}

