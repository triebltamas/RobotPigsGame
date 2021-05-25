#ifndef ROBOTPIGSWIDGET_H
#define ROBOTPIGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QKeyEvent>
#include "robotpigsmodel.h"
#include "newgamedialog.h"
#include "nextrounddialog.h"
#include "savegamewidget.h"
#include "loadgamewidget.h"

class RobotPigsWidget : public QWidget
{
    Q_OBJECT

public:
    RobotPigsWidget(QWidget *parent = nullptr);
    ~RobotPigsWidget();

protected:
    void keyPressEvent(QKeyEvent *event);
    void generateTable(int N);
    void newGame();

private slots:
    void model_gameWon(int player);
    void model_gameOver();
    void loadGame();
    void saveGame();
    void newGameButtonClicked();
    void tableChanged(int oldIndex, int newIndex);
    void nextRoundPlayer1();
    void nextRoundPlayer2();
    void model_livesChanged();
    void model_directionsChanged();

private:


    void nextRoundButtonClicked(bool player);
    void updateTable();


    QVector<QString> steps1;
    QVector<QString> steps2;
    QPushButton* _newGameButton;
    QPushButton* _nextRoundButton;
    QLabel* _label1;
    QLabel* _label2;
    QLabel* _directions_label1;
    QLabel* _directions_label2;

    RobotPigsModel _model;
    NewGameDialog* _newGameDialog;
    NextRoundDialog* _nextRoundDialog_p1;
    NextRoundDialog* _nextRoundDialog_p2;
    SaveGameWidget* _saveGameWidget;
    LoadGameWidget* _loadGameWidget;

    QHBoxLayout* _lives;
    QHBoxLayout* _directions;
    QGridLayout* _tableLayout;
    QVBoxLayout* _mainLayout;
    QVector<QVector<QTextBrowser*>> _textBrowserTable;

};
#endif // ROBOTPIGSWIDGET_H
