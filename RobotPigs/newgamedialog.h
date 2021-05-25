#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class NewGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameDialog(QWidget *parent = nullptr);
    int gameSize_n() { return _comboBox_n->currentText().toInt(); }
    void setGameSize_n(int n) { _comboBox_n->setCurrentText(QString::number(n)); }
private:
    QLabel *_label_n;
    QComboBox *_comboBox_n;
    QPushButton *_okButton;
    QPushButton *_cancelButton;
};

#endif // NEWGAMEDIALOG_H
