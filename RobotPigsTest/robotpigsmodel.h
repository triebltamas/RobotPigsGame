#ifndef ROBOTPIGSMODEL_H
#define ROBOTPIGSMODEL_H

#include <QObject>
#include <QVector>
#include <QString>

#include "player.h"
#include "robotpigsdataaccess.h"

class RobotPigsModel : public QObject
{
    Q_OBJECT
public:
    RobotPigsModel(RobotPigsDataAccess* dataAccess, int n);
    ~RobotPigsModel();
    void newGame(); // új játék kezdése
    void stepGame(QVector<QString> steps1, QVector<QString> steps2); // játék léptetése
    bool loadGame(int gameIndex); // játék betöltése
    bool saveGame(int gameIndex); // játék mentése
    QVector<QString> saveGameList() const; // mentett játékok lekérdezése
    int getPlayer1Index() { return _player1->_index; }
    int getPlayer2Index() { return _player2->_index; }
    int getPlayer1Lives() { return _player1->_lives; }
    int getPlayer2Lives() { return _player2->_lives; }
    int getPlayer1Directions() { return (int) _player1->_dir; }
    int getPlayer2Directions() { return (int) _player2->_dir; }



    void fire(Player* offender, Player* victim);
    void hit(Player* offender, Player* victim);
    int stepPlayer(Player* p, Player::Direction dir);
    void carefulSteps(Player::Direction dir1, Player::Direction dir2);

    int _n;
signals:
    void gameWon(int player);
    void gameOver();
    void tableChanged(int oldIndex, int newIndex);
    void livesChanged();
    void directionsChanged();

private:
    bool checkGame();

    Player *_player1;
    Player *_player2;
    RobotPigsDataAccess* _dataAccess;
};

#endif // ROBOTPIGSMODEL_H
