#include "robotpigsdataaccess.h"
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>




QVector<QString> RobotPigsDataAccess::saveGameList() const
{
    QVector<QString> result(5);

    // végigmegyünk az 5 helyen
    for (int i = 0; i < 5; i++)
    {
        if (QFile::exists("game" + QString::number(i) + ".sav")) // ha az adott mentés létezik
        {
            QFileInfo info("game"+ QString::number(i) + ".sav");
            result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
            // akkor betöltjük a fájl módosítás időpontját
        }
    }

    return result;
}

bool RobotPigsDataAccess::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    saveGameData.resize(7);

    // soronként beolvassuk az adatokat a fájlból
    for (int i = 0; i < 7; i++)
        saveGameData[i] = stream.readLine().toInt();

    file.close();

    return true;
}

bool RobotPigsDataAccess::saveGame(int gameIndex, const QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);

    // soronként egy adatot írunk ki
    for (int i = 0; i < 7; i++)
        stream << saveGameData[i] << endl;

    file.close();

    return true;
}

