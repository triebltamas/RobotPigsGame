#include <QString>
#include <QtTest>
#include "robotpigsmodel.h"
#include "robotpigsdataaccessmock.h"

class RobotPigsModelTest : public QObject // tesztkörnyezet
{
    Q_OBJECT
private:
    RobotPigsModel* _model;
    RobotPigsDataAccess *_dataAccess;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testStepGame();
    void testStepGameErrors();

    void testLoadGame();
    void testSaveGame();
};

// tesztkörnyezet inicializálása
void RobotPigsModelTest::initTestCase()
{
    _dataAccess = new RobotPigsDataAccessMock();
    //4x4es táblán tesztelünk
    _model = new RobotPigsModel(_dataAccess, 4);
}

// tesztkörnyezet megsemmisítése
void RobotPigsModelTest::cleanupTestCase()
{
    delete _dataAccess;
    delete _model;
}

// tesztesetek
void RobotPigsModelTest::testNewGame()
{
    _model->newGame();


    int index = _model->_n * _model->_n / 2;
    // ellenőrizzük, hogy kezdetben minden adat helyes-e
    QCOMPARE(_model->_n, 4);
    QCOMPARE(_model->getPlayer1Directions(), Player::Direction::right);
    QCOMPARE(_model->getPlayer2Directions(), Player::Direction::left);
    QCOMPARE(_model->getPlayer1Lives(), 3);
    QCOMPARE(_model->getPlayer2Lives(), 3);
    QCOMPARE(_model->getPlayer1Index(), index);
    QCOMPARE(_model->getPlayer2Index(), index - 1);
}

void RobotPigsModelTest::testStepGame()
{
    int index = _model->_n * _model->_n / 2;

    QVector<QString> steps1;
    QVector<QString> steps2;
    steps1.clear();
    steps1.resize(5);
    steps2.clear();
    steps2.resize(5);
    for(int i = 0; i < 5; i++)
    {
        steps1[i] = "Step Left";
        steps2[i] = "Step Left";
    }

    _model->newGame();
    _model->stepGame(steps1, steps2);

    // ellenőrizzük, hogy a Player1 a helyén maradt, és Player2 pont felette van
    QCOMPARE(_model->getPlayer1Index(), index);
    QCOMPARE(_model->getPlayer2Index(), index - _model->_n);

    // ellenőrizzük, hogy a forgés, az ököl, és a lézerágyú is működik

    steps1.clear();
    steps1.resize(5);
    steps2.clear();
    steps2.resize(5);
    for(int i = 0; i < 5; i++)
    {
        steps1[i] = "Step Left";
        steps2[i] = "Step Left";
    }
    steps1[0] = "Hit!";
    steps2[0] = "Turn Left";
    steps2[1] = "Fire!";
    steps2[2] = "Fire!";

    _model->stepGame(steps1, steps2);
    QCOMPARE(_model->getPlayer2Lives(), 2);
    QCOMPARE(_model->getPlayer2Directions(), Player::Direction::down);
    QCOMPARE(_model->getPlayer1Lives(), 1);
}

void RobotPigsModelTest::testStepGameErrors()
{
    _model->newGame();

    //Ellenőrizzük, hogy, ha mindkét játékos ugyanoda akar lépni, akkor mindkettőnek megmarad a helye
    //4 x 4es táblán tesztelünk
    int index = _model->_n * _model->_n / 2;

    QVector<QString> steps1;
    QVector<QString> steps2;
    steps1.clear();
    steps1.resize(5);
    steps2.clear();
    steps2.resize(5);
    steps1[0] = "Step Down";
    steps1[1] = "Step Right";
    steps1[2] = "Step Right";
    steps1[3] = "Step Right";
    steps1[4] = "Step Right";
    steps2[0] = "Step Down";
    steps2[1] = "Step Down";
    steps2[2] = "Step Left";
    steps2[3] = "Step Left";
    steps2[4] = "Step Left";

    _model->stepGame(steps1, steps2);
    QCOMPARE(_model->getPlayer1Index(), 13);
    QCOMPARE(_model->getPlayer2Index(), 15);
}

void RobotPigsModelTest::testLoadGame()
{
    _model->newGame();

    QVector<QString> steps1;
    QVector<QString> steps2;

    steps1.clear();
    steps1.resize(5);
    steps2.clear();
    steps2.resize(5);
    for(int i = 0; i < 5; i++)
    {
        steps1[i] = "Step Left";
        steps2[i] = "Step Left";
    }
    steps1[0] = "Hit!";
    steps2[0] = "Turn Left";
    steps2[1] = "Fire!";
    steps2[2] = "Fire!";

    _model->stepGame(steps1, steps2);


    _model->loadGame(0);

    // ellenőrizzük, hogy a lépésszám 0, még senki sem lépett, és az X jön

    int index = _model->_n * _model->_n / 2;
    // ellenőrizzük, hogy kezdetben minden adat helyes-e
    QCOMPARE(_model->_n, 4);
    QCOMPARE(_model->getPlayer1Directions(), Player::Direction::right);
    QCOMPARE(_model->getPlayer2Directions(), Player::Direction::left);
    QCOMPARE(_model->getPlayer1Lives(), 3);
    QCOMPARE(_model->getPlayer2Lives(), 3);
    QCOMPARE(_model->getPlayer1Index(), index);
    QCOMPARE(_model->getPlayer2Index(), index - 1);


}

void RobotPigsModelTest::testSaveGame()
{
    _model->newGame();


    QVector<QString> steps1;
    QVector<QString> steps2;

    steps1.clear();
    steps1.resize(5);
    steps2.clear();
    steps2.resize(5);
    for(int i = 0; i < 5; i++)
    {
        steps1[i] = "Step Left";
        steps2[i] = "Step Left";
    }
    steps1[0] = "Hit!";
    steps2[0] = "Turn Left";
    steps2[1] = "Fire!";
    steps2[2] = "Fire!";

    _model->stepGame(steps1, steps2);


    _model->saveGame(0);
}


QTEST_APPLESS_MAIN(RobotPigsModelTest)

#include "robotpigsmodeltest.moc"
