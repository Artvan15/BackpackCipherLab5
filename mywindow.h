#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QDebug>
#include <vector>
#include <string>


class MyWindow : public QDialog
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = nullptr);
private:
    QLabel *publicKeyLabel;
    QLabel *privateKeyLabel;
    QLabel *nL, *mL;
    QLineEdit *publicKey;
    QLineEdit *privateKey;
    QLineEdit *n, *m;
    QTextEdit *decText; QLabel *decL;
    QTextEdit *encText; QLabel *encL;
    QPushButton *encryptB, *decryptB, *getPublicKeyB;

    int nInt, mInt;
    std::vector<int> privateVec, publicVec;
    std::vector<int> encVec, decVec;

signals:

private slots:
    void getPublicKeyEnable(QString);
    void getPublicKeyClicked();
    void encryptClicked();
    void decryptClicked();
};

#endif // MYWINDOW_H
