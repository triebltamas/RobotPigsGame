#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QVector>

class Player
{
public:
    enum Direction {left, up, right, down};

    Player(int _l, Direction _d, int _i) : _lives(_l),
        _dir(_d), _index(_i) {};

    void turnLeft();
    void turnRight();
    void gotHit() { _lives--; };

    int _lives;
    Direction _dir;
    int _index;
};

#endif // PLAYER_H
