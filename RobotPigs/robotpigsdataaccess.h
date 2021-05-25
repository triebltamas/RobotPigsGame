#ifndef ROBOTPIGSDATAACCESS_H
#define ROBOTPIGSDATAACCESS_H

#include <QString>
#include <QVector>

class RobotPigsDataAccess
{
public:
    explicit RobotPigsDataAccess() {}

    QVector<QString> saveGameList() const; // mentett játékok lekérdezése

    bool loadGame(int gameIndex, QVector<int> &saveGameData); // játék betöltése
    bool saveGame(int gameIndex, const QVector<int> &saveGameData); // játék mentése
};

#endif // ROBOTPIGSDATAACCESS_H
