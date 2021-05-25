#include "newgamedialog.h"
#include <QHBoxLayout>

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300,100);
    setWindowTitle(tr("Új játék"));
    setModal(true); // pop-up window, with focus on

    _label_n = new QLabel(tr("Tábla sorainak/oszlopainak száma: "));
    _comboBox_n = new QComboBox();
    _comboBox_n->addItem("4");
    _comboBox_n->addItem("6");
    _comboBox_n->addItem("8");


    _okButton = new QPushButton(tr("OK"));
    _okButton->setFixedSize(75, 23);
    _cancelButton = new QPushButton(tr("Mégse"));
    _cancelButton->setFixedSize(75, 23);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label_n);
    upperLayout->addWidget(_comboBox_n);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);
    lowerLayout->addWidget(_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
