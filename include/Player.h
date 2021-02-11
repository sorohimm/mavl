//
//  Copyright © 2020 Vladimir Mashir.
//
#ifndef GAYENGINE_P_H
#define GAYENGINE_P_H

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Vector2f Position;
    sf::Sprite sprite;
    sf::Texture texture;

    bool isOnGround;
    bool LeftPressed;
    bool RightPressed;
    bool isSelect;
    bool isMove;
    sf::Rect<int> rect;

public:
    void moveLeft();
    void moveRight();
    void Jump();
    void stopLeft();
    void stopRight();
    void stopJump();
    void toBegin();
    void update();
    void SetRect(sf::Rect<int> &inputRect);
    sf::Rect<int> GetRect() const;
    sf::Sprite GetSprite();

    Player();
};

#endif //GAMEENGINE_P_H
