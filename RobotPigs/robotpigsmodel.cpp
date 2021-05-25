#include "robotpigsmodel.h"
#include <iostream>

RobotPigsModel::RobotPigsModel()
{
}

RobotPigsModel::~RobotPigsModel()
{
}

void RobotPigsModel::newGame()
{
    int index = _n*_n/2;

    _player1 = new Player(3, Player::Direction::right, index);
    _player2 = new Player(3, Player::Direction::left, index - 1);
}

void RobotPigsModel::stepGame(QVector<QString> steps1, QVector<QString> steps2)
{

    std::cout << "Next round..." << std::endl;
    for(int i = 0; i < 5; i++)
    {
        int oldIndex1 = _player1->_index;
        int oldIndex2 = _player2->_index;

        if(steps1[i].contains("Step") && steps2[i].contains("Step"))
        {
            Player::Direction dir1;
            Player::Direction dir2;

            if(steps1[i].contains("Left")) dir1 = Player::Direction::left;
            else if(steps1[i].contains("Up")) dir1 = Player::Direction::up;
            else if(steps1[i].contains("Right")) dir1 = Player::Direction::right;
            else dir1 = Player::Direction::down;

            if(steps2[i].contains("Left")) dir2 = Player::Direction::left;
            else if(steps2[i].contains("Up")) dir2 = Player::Direction::up;
            else if(steps2[i].contains("Right")) dir2 = Player::Direction::right;
            else dir2 = Player::Direction::down;

            carefulSteps(dir1, dir2);
        }
        else
        {
            if(steps1[i] == "Turn Left") _player1->turnLeft();
            else if(steps1[i] == "Turn Right") _player1->turnRight();
            else if(steps1[i] == "Fire!") fire(_player1, _player2);
            else if(steps1[i] == "Hit!") hit(_player1, _player2);
            else if(steps1[i] == "Step Left") _player1->_index += stepPlayer(_player1, Player::Direction::left);
            else if(steps1[i] == "Step Up") _player1->_index += stepPlayer(_player1, Player::Direction::up);
            else if(steps1[i] == "Step Right") _player1->_index += stepPlayer(_player1, Player::Direction::right);
            else if(steps1[i] == "Step Down") _player1->_index += stepPlayer(_player1, Player::Direction::down);


            if(steps2[i] == "Turn Left") _player2->turnLeft();
            else if(steps2[i] == "Turn Right") _player2->turnRight();
            else if(steps2[i] == "Fire!") fire(_player2, _player1);
            else if(steps2[i] == "Hit!") hit(_player2, _player1);
            else if(steps2[i] == "Step Left") _player2->_index += stepPlayer(_player2, Player::Direction::left);
            else if(steps2[i] == "Step Up") _player2->_index += stepPlayer(_player2, Player::Direction::up);
            else if(steps2[i] == "Step Right") _player2->_index += stepPlayer(_player2, Player::Direction::right);
            else if(steps2[i] == "Step Down") _player2->_index += stepPlayer(_player2, Player::Direction::down);


            tableChanged(oldIndex1, _player1->_index);
            tableChanged(oldIndex2, _player2->_index);
            directionsChanged();
        }



        if(checkGame()) break;


    }

}

void RobotPigsModel::fire(Player* offender, Player* victim)
{
    int off = offender->_index;
    int vic = victim->_index;
    if(off % _n == vic % _n)
    {
        if(off < vic && offender->_dir == Player::Direction::down)
        {
            victim->gotHit();
            livesChanged();
            std::cout << "That's a hit, Son!.." << std::endl;
        }
        else if(off > vic && offender->_dir == Player::Direction::up)
        {
            victim->gotHit();
            livesChanged();
            std::cout << "That's a hit, Son!.." << std::endl;
        }
        else
        {
            std::cout << "Unsuccessful Hit!.." << std::endl;
        }
    }

    else if(off/_n == vic/_n)
    {
        if(off < vic && offender->_dir == Player::Direction::right)
        {
            victim->gotHit();
            livesChanged();
            std::cout << "That's a hit, Son!.." << std::endl;
        }
        else if(off > vic && offender->_dir == Player::Direction::left)
        {
            victim->gotHit();
            livesChanged();
            std::cout << "That's a hit, Son!.." << std::endl;
        }
        else
        {
            std::cout << "Unsuccessful Hit!.." << std::endl;
        }
    }
    else
    {
        std::cout << "Unsuccessful Hit!.." << std::endl;
    }
}

void RobotPigsModel::hit(Player* offender, Player* victim)
{
    int off = offender->_index;
    int vic = victim->_index;
    int radius = _n + 1;

    if(std::abs(off - vic) <= std::abs(radius))
    {
        if(off % _n == vic % _n || ((off - 1) % _n == vic % _n && off % _n != 0) || ((off + 1) % _n == vic % _n && off % _n != _n - 1))
        {
            victim->gotHit();
            livesChanged();
            std::cout << "That's a hit, Son!.." << std::endl;
        }
        else
        {
            std::cout << "Unsuccessful Hit!.." << std::endl;
        }
    }
    else
    {
        std::cout << "Unsuccessful Hit!.." << std::endl;
    }
}


int RobotPigsModel::stepPlayer(Player *p, Player::Direction dir)
{
    if(dir == 0)
    {
        //checking if player is already on the left side, plus if player isn't stepping on the other player
        if(p->_index % _n != 0 && p->_index - 1 != _player1->_index && p->_index - 1 != _player2->_index)
        {
            std::cout << "Stepping left.." << std::endl;
            return -1;
        }
    }
    else if(dir == 2)
    {
        if(p->_index % _n != _n - 1 && p->_index + 1 != _player1->_index && p->_index + 1 != _player2->_index)
        {
            std::cout << "Stepping right.." << std::endl;
            return 1;
        }
    }
    else if(dir == 1)
    {
        if(p->_index >= _n && p->_index - _n != _player1->_index && p->_index - _n != _player2->_index)
        {
            std::cout << "Stepping up.." << std::endl;
            return -_n;
        }
    }
    else
    {
        if(p->_index < _n * (_n - 1) && p->_index + _n != _player1->_index && p->_index + _n != _player2->_index)
        {
            std::cout << "Stepping down.." << std::endl;
            return _n;
        }
    }
    std::cout << "Stepping is unsuccessful.." << std::endl;
    return 0;
}

void RobotPigsModel::carefulSteps(Player::Direction dir1, Player::Direction dir2)
{
    if(_player1->_index + stepPlayer(_player1, dir1) != _player2->_index + stepPlayer(_player2, dir2))
    {
        int oldIndex1 = _player1->_index;
        int oldIndex2 = _player2->_index;

        if(stepPlayer(_player1, dir1) == 0)
        {
            _player2->_index += stepPlayer(_player2, dir2);
            _player1->_index += stepPlayer(_player1, dir1);

            tableChanged(oldIndex2, _player2->_index);
            tableChanged(oldIndex1, _player1->_index);
        }
        else
        {
            _player1->_index += stepPlayer(_player1, dir1);
            _player2->_index += stepPlayer(_player2, dir2);

            tableChanged(oldIndex1, _player1->_index);
            tableChanged(oldIndex2, _player2->_index);
        }


    }
}

bool RobotPigsModel::checkGame()
{
    if(_player1->_lives <= 0 && _player2->_lives <= 0)
    {
        gameOver();
        return true;
    }
    else if(_player1->_lives <= 0 )
    {
        gameWon(2);
        return true;
    } else if (_player2->_lives <= 0)
    {
        gameWon(1);
        return true;
    }
    return false;
}

bool RobotPigsModel::loadGame(int gameIndex)
{
    QVector<int> saveGameData;

    if (!_dataAccess.loadGame(gameIndex, saveGameData)) // az adatelérés végzi a tevékenységeket
        return false;

    _player1->_index = saveGameData[0];
    _player1->_dir = (Player::Direction)saveGameData[1];
    _player1->_lives = saveGameData[2];
    _player2->_index = saveGameData[3];
    _player2->_dir = (Player::Direction)saveGameData[4];
    _player2->_lives = saveGameData[5];

    _n = saveGameData[6];

    return true;
}

bool RobotPigsModel::saveGame(int gameIndex)
{
    QVector<int> saveGameData;

    // összerakjuk a megfelelő tartalmat
    saveGameData.push_back(_player1->_index);
    saveGameData.push_back((int)_player1->_dir);
    saveGameData.push_back(_player1->_lives);

    saveGameData.push_back(_player2->_index);
    saveGameData.push_back((int)_player2->_dir);
    saveGameData.push_back(_player2->_lives);


    saveGameData.push_back(_n);

    return _dataAccess.saveGame(gameIndex, saveGameData); // az adatelérés végzi a tevékenységeket

}

QVector<QString> RobotPigsModel::saveGameList() const
{
    return _dataAccess.saveGameList(); // az adatelérés végzi a tevékenységeket
}
