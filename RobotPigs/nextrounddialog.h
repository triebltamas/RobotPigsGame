#ifndef NEXTROUNDDIALOG_H
#define NEXTROUNDDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVector>


class NextRoundDialog : public QDialog
{
public:
    explicit NextRoundDialog(QWidget *parent = nullptr);
    QVector<QComboBox*> getComboBoxes() { return _comboBoxes; };
private:
    QVector<QLabel*> _labels;
    QVector<QComboBox*> _comboBoxes;
    QPushButton *_okButton;
    QPushButton *_cancelButton;
};

#endif // NEXTROUNDDIALOG_H
