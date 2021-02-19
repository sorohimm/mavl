#ifndef GAYENGINE_LAYER_H
#define GAYENGINE_LAYER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Layer: public Player
{
private:
    int opacity;
    std::vector<sf::Sprite> tiles;

public:
    [[nodiscard]] std::vector<sf::Sprite> GetTilesVector() const;
    [[nodiscard]] int GetOpacity() const;
    void SetOpacity(const int);
    void SetSprite(const sf::Sprite&);
};


#endif //GAYENGINE_LAYER_H
