#ifndef ROBOTPIGSDATAACCESS_H
#define ROBOTPIGSDATAACCESS_H

#include <QString>
#include <QVector>

class RobotPigsDataAccess // az adatelérés típusa (absztrakt osztály)
{
public:
    RobotPigsDataAccess() { }
    virtual ~RobotPigsDataAccess() { }

    virtual bool isAvailable() const { return false; } // rendelkezésre állás lekérdezése
    virtual QVector<QString> saveGameList() const = 0; // mentett játékok lekérdezése

    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0; // játék betöltése
    virtual bool saveGame(int gameIndex, const QVector<int> &saveGameData) = 0; // játék mentése
};

#endif // ROBOTPIGSDATAACCESS_H
