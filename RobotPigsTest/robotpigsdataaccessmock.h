#ifndef ROBOTPIGSDATAACCESSMOCK_H
#define ROBOTPIGSDATAACCESSMOCK_H

#include "robotpigsdataaccess.h"

class RobotPigsDataAccessMock : public RobotPigsDataAccess // mock object, csak teszteléshez
{
public:
    bool isAvailable() const { return true; } // rendelkezésre állás lekérdezése
    QVector<QString> saveGameList() const // mentett játékok lekérdezése
    {
        return QVector<QString>(5); // üres listát adunk vissza
    }

    bool loadGame(int gameIndex, QVector<int> &saveGameData) // játék betöltése
    {
        saveGameData.resize(7); // minden érték 0 lesz
        saveGameData[0] = 8;
        saveGameData[1] = 2;
        saveGameData[2] = 3;
        saveGameData[3] = 7;
        saveGameData[4] = 0;
        saveGameData[5] = 3;
        saveGameData[6] = 4; // kivéve a mátrix mérete

        qDebug() << "game loaded to slot (" << gameIndex << ") with values: ";
        for (int i = 0; i < 7; i++)
            qDebug() << saveGameData[i] << " ";
        qDebug() << endl;

        return true;
    }

    bool saveGame(int gameIndex, const QVector<int> &saveGameData) // játék mentése
    {
        qDebug() << "game saved to slot (" << gameIndex << ") with values: ";
        for (int i = 0; i < 7; i++)
            qDebug() << saveGameData[i] << " ";
        qDebug() << endl;

        return true;
    }
};

#endif // ROBOTPIGSDATAACCESSMOCK_H
