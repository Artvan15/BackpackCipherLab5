#include "mywindow.h"
#include <QIntValidator>

MyWindow::MyWindow(QWidget *parent) : QDialog(parent)
{
    publicKeyLabel = new QLabel("public key");
    privateKeyLabel = new QLabel("private key");
    nL = new QLabel("n"); mL = new QLabel("m");
    publicKey = new QLineEdit; publicKey->setInputMask("9,9,9");
    privateKey = new QLineEdit; privateKey->setInputMask("999");
    QIntValidator *val = new QIntValidator(0,300);
    n = new QLineEdit; n->setValidator(val);
    m = new QLineEdit; m->setValidator(val);
    decText = new QTextEdit;
    encText = new QTextEdit;
    encryptB = new QPushButton("Encrypt");
    decryptB = new QPushButton("Decrypt");
    getPublicKeyB = new QPushButton("Get public key");


    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(publicKeyLabel);
    left->addWidget(publicKey);
    left->addWidget(decText);

    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(privateKeyLabel);
    right->addWidget(privateKey);
    right->addWidget(encText);

    QVBoxLayout *sideBox = new QVBoxLayout;
    QHBoxLayout *sideU = new QHBoxLayout, *sideD = new QHBoxLayout;
    sideU->addWidget(nL); sideU->addWidget(mL);
    sideD->addWidget(n); sideD->addWidget(m);
    sideBox->addLayout(sideU); sideBox->addLayout(sideD);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left); main->addLayout(right); main->addLayout(sideBox);

    this->setLayout(main);

}
