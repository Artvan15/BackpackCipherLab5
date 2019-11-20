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
    QTextEdit *decText;
    QTextEdit *encText;
    QPushButton *encryptB, *decryptB, *getPublicKeyB;


signals:

public slots:

};

#endif // MYWINDOW_H
