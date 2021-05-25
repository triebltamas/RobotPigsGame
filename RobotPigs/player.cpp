#include "player.h"
#include <iostream>

void Player::turnLeft()
{
    if((int)_dir > 0) _dir = (Direction) (_dir - 1);
    else _dir = down;

    std::cout << "turned left..." << std::endl;
}
void Player::turnRight()
{
    if((int)_dir < 3) _dir = (Direction) (_dir + 1);
    else _dir = left;
    std::cout << "turned right..." << std::endl;
}
