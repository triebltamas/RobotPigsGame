#include "robotpigswidget.h"
#include <QApplication>
#include <QMessageBox>
#include <QFont>
#include <iostream>

RobotPigsWidget::RobotPigsWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 600);
    setBaseSize(400,600);
    setWindowTitle(tr("RobotPigs"));

    _loadGameWidget = NULL;
    _saveGameWidget = NULL;

    _newGameButton = new QPushButton(tr("Új játék"));
    _nextRoundButton = new QPushButton(tr("Következő Kör"));




    //Adding labels to indicate the Player's health
    _label1 = new QLabel(tr("Player1's lives: 3"));
    _label2 = new QLabel(tr("Player2's lives: 3"));
    _label1->setFont(QFont("Comic Sans MS", 15, QFont::Bold));
    _label2->setFont(QFont("Comic Sans MS", 15, QFont::Bold));


    _lives = new QHBoxLayout();
    _lives->addWidget(_label1);
    _lives->addWidget(_label2);

    //Adding labels to indicate the Player's direction
    _directions_label1 = new QLabel(tr("Player1's direction: right"));
    _directions_label2 = new QLabel(tr("Player2's direction: left"));
    _directions_label1->setFont(QFont("Comic Sans MS", 15, QFont::Bold));
    _directions_label2->setFont(QFont("Comic Sans MS", 15, QFont::Bold));


    _directions = new QHBoxLayout();
    _directions->addWidget(_directions_label1);
    _directions->addWidget(_directions_label2);



    _newGameDialog = new NewGameDialog();
    _nextRoundDialog_p1 = new NextRoundDialog();
    _nextRoundDialog_p2 = new NextRoundDialog();

    connect(_newGameButton, SIGNAL(clicked()), _newGameDialog, SLOT(exec()));
    connect(_newGameDialog, SIGNAL(accepted()), this, SLOT(newGameButtonClicked()));

    connect(_nextRoundButton, SIGNAL(clicked()), _nextRoundDialog_p1, SLOT(exec()));
    connect(_nextRoundDialog_p1, SIGNAL(accepted()), this, SLOT(nextRoundPlayer1()));

    connect(_nextRoundDialog_p1, SIGNAL(accepted()), _nextRoundDialog_p2, SLOT(exec()));
    connect(_nextRoundDialog_p2, SIGNAL(accepted()), this, SLOT(nextRoundPlayer2()));

    connect(&_model, &RobotPigsModel::gameWon, this, &RobotPigsWidget::model_gameWon);
    connect(&_model, SIGNAL(gameOver()), this, SLOT(model_gameOver()));

    connect(&_model, SIGNAL(livesChanged()), this, SLOT(model_livesChanged()));
    connect(&_model, SIGNAL(directionsChanged()), this, SLOT(model_directionsChanged()));

    connect(&_model, &RobotPigsModel::tableChanged, this, &RobotPigsWidget::tableChanged);


    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_newGameButton);

    setLayout(_mainLayout);


}

RobotPigsWidget::~RobotPigsWidget()
{
    if (_loadGameWidget != NULL) delete _loadGameWidget;
    if (_saveGameWidget != NULL) delete _saveGameWidget;
}

void RobotPigsWidget::newGame()
{
    //handling the old layouts
    _mainLayout->removeItem(_tableLayout);
    _mainLayout->removeWidget(_nextRoundButton);
    _mainLayout->addWidget(_nextRoundButton);
    _mainLayout->removeItem(_lives);
    _mainLayout->addLayout(_lives);
    _mainLayout->removeItem(_directions);
    _mainLayout->addLayout(_directions);

    _tableLayout = new QGridLayout();
    _mainLayout->addLayout(_tableLayout);

    generateTable(_model._n);
    _model.newGame();

    _label1->setText(tr("Player1's lives: %1").arg(_model.getPlayer1Lives()));
    _label2->setText(tr("Player2's lives: %1").arg(_model.getPlayer2Lives()));

    _directions_label1->setText(tr("Player1's direction: right"));
    _directions_label2->setText(tr("Player2's direction: left"));
}

void RobotPigsWidget::generateTable(int N)
{
    //std::cout << "\nGenerating Table\nN = " << N << "\n\n";
    //deleting the previous buttons
    for(int i = 0; i < _textBrowserTable.size(); ++i)
    {
        for(int j = 0; j < _textBrowserTable[i].size(); ++j)
        {
            //_tableLayout->removeWidget(_textBrowserTable[i][j]);
            delete _textBrowserTable[i][j];
        }
    }

    int fontSize = 30;
    if(_model._n == 4) fontSize = 55;
    if(_model._n == 6) fontSize = 40;

    _textBrowserTable.resize(N);

    for (int i = 0; i < N; ++i)
    {
        _textBrowserTable[i].resize(N);
        for (int j = 0; j < N; ++j)
        {
            _textBrowserTable[i][j]= new QTextBrowser(this);
            _textBrowserTable[i][j]->setFont(QFont("Comic Sans MS", fontSize, QFont::Bold));
            _textBrowserTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
            _textBrowserTable[i][j]->setReadOnly(true);
            _tableLayout->addWidget(_textBrowserTable[i][j], i, j);
        }
    }
    _textBrowserTable[N/2][0]->setText("P1");
    _textBrowserTable[N/2 - 1][N-1]->setText("P2");
}

void RobotPigsWidget::nextRoundButtonClicked(bool player)
{
    if(player)
    {
        steps1.clear();
        steps1.resize(5);
        for(int i = 0; i < 5; i++)
        {
            steps1[i] = (_nextRoundDialog_p1->getComboBoxes()[i]->currentText());
        }
    }
    else
    {
        steps2.clear();
        steps2.resize(5);
        for(int i = 0; i < 5; i++)
        {
            steps2[i] = (_nextRoundDialog_p2->getComboBoxes()[i]->currentText());
        }
    }
    if(!(steps1.isEmpty() || steps2.isEmpty()))
    {
        _model.stepGame(steps1, steps2);
        steps1.clear();
        steps2.clear();
    }


}


void RobotPigsWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_N && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        // lekezeljük a Ctrl+N kombinációt
        _newGameButton->clicked();
        update();
    }

    // játék betöltése
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_loadGameWidget == NULL) // ha még egyszer sem nyitották meg az ablakot
        {
            _loadGameWidget = new LoadGameWidget();
            connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _loadGameWidget->setGameList(_model.saveGameList());
        _loadGameWidget->open();
    }

    // játék mentése
    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_saveGameWidget == NULL) // ha még egyszer sem nyitották meg az ablakot
        {
            _saveGameWidget = new SaveGameWidget();
            connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _saveGameWidget->setGameList(_model.saveGameList());
        _saveGameWidget->open();
    }
}


void RobotPigsWidget::newGameButtonClicked()
{
    _model._n = _newGameDialog->gameSize_n();

    if(_model._n == 8)
    {
        this->setMinimumSize(650, 720);
        this->setBaseSize(650,720);
    }
    else if(_model._n == 6)
    {
        this->setMinimumSize(600, 700);
        this->setBaseSize(600,700);
    }
    else
    {
        this->setMinimumSize(550, 680);
        this->setBaseSize(550,680);
    }

    newGame();
}

void RobotPigsWidget::updateTable()
{

    _mainLayout->removeItem(_tableLayout);
    _mainLayout->removeWidget(_nextRoundButton);
    _mainLayout->addWidget(_nextRoundButton);
    _mainLayout->removeItem(_lives);
    _mainLayout->addLayout(_lives);
    _mainLayout->removeItem(_directions);
    _mainLayout->addLayout(_directions);

    _label1->setText(tr("Player1's lives: %1").arg(_model.getPlayer1Lives()));
    _label2->setText(tr("Player2's lives: %1").arg(_model.getPlayer2Lives()));

    model_directionsChanged();

    _tableLayout = new QGridLayout();
    _mainLayout->addLayout(_tableLayout);
    _newGameDialog->setGameSize_n(_model._n);



    if(_model._n == 8)
    {
        this->setMinimumSize(650, 720);
        this->setBaseSize(650,720);
    }
    else if(_model._n == 6)
    {
        this->setMinimumSize(600, 700);
        this->setBaseSize(600,700);
    }
    else
    {
        this->setMinimumSize(550, 680);
        this->setBaseSize(550,680);
    }


    generateTable(_model._n);

    tableChanged(_model._n*_model._n/2, _model.getPlayer1Index());
    tableChanged(_model._n*_model._n/2 - 1, _model.getPlayer2Index());
}

void RobotPigsWidget::nextRoundPlayer1()
{
    nextRoundButtonClicked(true);
}


void RobotPigsWidget::nextRoundPlayer2()
{
    nextRoundButtonClicked(false);
}


void RobotPigsWidget::model_gameWon(int player)
{

    if(player == 1) QMessageBox::information(this, tr("RobotPigs"), QString("Játék vége! Player1 nyerte a játékot!"));

    else QMessageBox::information(this, tr("RobotPigs"), QString("Játék vége! Player2 nyerte a játékot!"));


    newGame();
}

void RobotPigsWidget::model_gameOver()
{

    QMessageBox::information(this, tr("RobotPigs"), QString("Játék vége! Döntetlen!"));
    newGame();
}

void RobotPigsWidget::tableChanged(int oldIndex, int newIndex)
{
    if (oldIndex != newIndex)
    {
        QString text = _textBrowserTable[oldIndex / _model._n][oldIndex % _model._n]->toPlainText();
        _textBrowserTable[newIndex / _model._n][newIndex % _model._n]->setText(text);
        _textBrowserTable[oldIndex / _model._n][oldIndex % _model._n]->setText("");
    }
}
void RobotPigsWidget::model_livesChanged()
{
    _label1->setText(tr("Player1's lives: %1").arg(_model.getPlayer1Lives()));
    _label2->setText(tr("Player2's lives: %1").arg(_model.getPlayer2Lives()));
}

void RobotPigsWidget::model_directionsChanged()
{
    int dir1 = _model.getPlayer1Directions();
    int dir2 = _model.getPlayer2Directions();
    if(dir1 == 0)
    {
        _directions_label1->setText(tr("Player1's direction: left"));
    }
    else if(dir1 == 1)
    {
        _directions_label1->setText(tr("Player1's direction: up"));
    }
    else if(dir1 == 2)
    {
        _directions_label1->setText(tr("Player1's direction: right"));
    }
    else if(dir1 == 3)
    {
        _directions_label1->setText(tr("Player1's direction: down"));
    }
    if(dir2 == 0)
    {
        _directions_label2->setText(tr("Player2's direction: left"));
    }
    else if(dir2 == 1)
    {
        _directions_label2->setText(tr("Player2's direction: up"));
    }
    else if(dir2 == 2)
    {
        _directions_label2->setText(tr("Player2's direction: right"));
    }
    else if(dir2 == 3)
    {
        _directions_label2->setText(tr("Player2's direction: down"));
    }
}


void RobotPigsWidget::loadGame()
{
    // betöltjük a kiválasztott játékot
    if (_model.loadGame(_loadGameWidget->selectedGame()))
    {
        updateTable();
        QMessageBox::information(this, tr("Robot-Pigs"), tr("Játék betöltve!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Robot-Pigs"), tr("A játék betöltése sikertelen!"));
    }
}

void RobotPigsWidget::saveGame()
{
    // elmentjük a kiválasztott játékot

    if (_model.saveGame(_saveGameWidget->selectedGame()))
    {
        QMessageBox::information(this, tr("Robot-Pigs"), tr("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Robot-Pigs"), tr("A játék mentése sikertelen!"));
    }
}

