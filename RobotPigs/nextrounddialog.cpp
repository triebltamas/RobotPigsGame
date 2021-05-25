#include "nextrounddialog.h"
#include <QHBoxLayout>

NextRoundDialog::NextRoundDialog(QWidget *parent) :
    QDialog(parent)
{

    setFixedSize(300,300);
    setWindowTitle(tr("Következő Kör"));
    setModal(true); // pop-up window, with focus on


    _labels.resize(5);
    _comboBoxes.resize(5);
    for(int i = 0; i < 5; i++)
    {
        _labels[i] = new QLabel();
        _labels[i]->setText("Step " + QString::number(i+1) + ":");
        _comboBoxes[i] = new QComboBox();
        _comboBoxes[i]->addItem("Step Left");
        _comboBoxes[i]->addItem("Step Up");
        _comboBoxes[i]->addItem("Step Right");
        _comboBoxes[i]->addItem("Step Down");
        _comboBoxes[i]->addItem("Turn Left");
        _comboBoxes[i]->addItem("Turn Right");
        _comboBoxes[i]->addItem("Fire!");
        _comboBoxes[i]->addItem("Hit!");
    }

    _okButton = new QPushButton(tr("OK"));
    _okButton->setFixedSize(75, 23);
    _cancelButton = new QPushButton(tr("Mégse"));
    _cancelButton->setFixedSize(75, 23);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QVector<QHBoxLayout*> upperLayouts;
    upperLayouts.resize(5);
    for(int i = 0; i < 5; i++)
    {
        upperLayouts[i] = new QHBoxLayout();
        upperLayouts[i]->addWidget(_labels[i]);
        upperLayouts[i]->addWidget(_comboBoxes[i]);
    }

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);
    lowerLayout->addWidget(_cancelButton);


    QVBoxLayout *mainLayout = new QVBoxLayout();

    for(int i = 0; i < 5; i++)
    {
        mainLayout->addLayout(upperLayouts[i]);
    }
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
