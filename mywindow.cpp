#include "mywindow.h"
int modInverse(int a, int m);
int bin_to_dec(QString str);

MyWindow::MyWindow(QWidget *parent) : QDialog(parent)
{
    publicKeyLabel = new QLabel("public key");
    privateKeyLabel = new QLabel("private key");
    nL = new QLabel("n"); mL = new QLabel("m");
    encL = new QLabel("Encrypted text"); decL = new QLabel("Decrypted text");

    const QRegExp *reg = new QRegExp("(\\d{1,3},)+\\d{1,3}"); const QRegExpValidator *keyReg = new QRegExpValidator(*reg);
    publicKey = new QLineEdit; publicKey->setValidator(keyReg);
    privateKey = new QLineEdit; privateKey->setValidator(keyReg);

    QValidator *val = new QIntValidator(1,300);
    n = new QLineEdit; n->setValidator(val);
    m = new QLineEdit; m->setValidator(val);

    decText = new QTextEdit;
    encText = new QTextEdit;
    encryptB = new QPushButton("Encrypt");
    decryptB = new QPushButton("Decrypt");
    getPublicKeyB = new QPushButton("Get public key");
    getPublicKeyB->setEnabled(false); //encryptB->setEnabled(false);decryptB->setEnabled(false);



    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(publicKeyLabel);
    right->addWidget(publicKey);
    right->addWidget(decL);
    right->addWidget(decText);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(privateKeyLabel);
    left->addWidget(privateKey);
    QHBoxLayout *sideU = new QHBoxLayout, *sideD = new QHBoxLayout;
    sideU->addWidget(nL); sideU->addWidget(mL);
    sideD->addWidget(n); sideD->addWidget(m);
    left->addLayout(sideU);left->addLayout(sideD);
    left->addWidget(encL);
    left->addWidget(encText);

    QVBoxLayout *sideBox = new QVBoxLayout;
    sideBox->addWidget(getPublicKeyB);
    sideBox->addWidget(encryptB);
    sideBox->addWidget(decryptB);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left); main->addLayout(right); main->addLayout(sideBox);

    this->setLayout(main);

    connect(privateKey, SIGNAL(textEdited(QString)), this, SLOT(getPublicKeyEnable(QString)));
    connect(n, SIGNAL(textEdited(QString)), this, SLOT(getPublicKeyEnable(QString)));
    connect(m, SIGNAL(textEdited(QString)), this, SLOT(getPublicKeyEnable(QString)));
    connect(getPublicKeyB, SIGNAL(clicked()), this, SLOT(getPublicKeyClicked()));
    connect(encryptB, SIGNAL(clicked()), this, SLOT(encryptClicked()));
    connect(decryptB, SIGNAL(clicked()), this, SLOT(decryptClicked()));
}

void MyWindow::getPublicKeyEnable(QString str){
    if(str.isEmpty()){
        getPublicKeyB->setEnabled(false);
        encryptB->setEnabled(false);
        decryptB->setEnabled(false);
    }
    else if(!privateKey->text().isEmpty() && !n->text().isEmpty() && !m->text().isEmpty()){
        getPublicKeyB->setEnabled(true);
        encryptB->setEnabled(true);
        decryptB->setEnabled(true);
    }
}

void MyWindow::getPublicKeyClicked(){
    encVec.clear();
    //get line text and assign
    QString privateKeyStr = privateKey->text();
    nInt = n->text().toInt(); mInt = m->text().toInt();

    //Split string and write down nums of private and public key into vectors
    QStringList prKeyStrList = privateKeyStr.split(',', QString::SkipEmptyParts);
    for(const auto &i : prKeyStrList)
        privateVec.push_back(i.toInt());
    for(const auto &i : privateVec)
        publicVec.push_back((i*nInt)%mInt);

    //Write down public key into string, then into LineEdit
    std::string publicKeyStr;
    auto beg = publicVec.begin();
    for(auto end = publicVec.end()-1; beg != end; ++beg)
        publicKeyStr.append(std::to_string(*beg) + ',');
    publicKeyStr.append(std::to_string(*beg));

    publicKey->setText(QString::fromStdString(publicKeyStr));
}

void MyWindow::encryptClicked(){
    encVec.clear();
    QByteArray ba = decText->toPlainText().toLatin1();
    size_t size = publicVec.size();
    for(const auto &i : ba){
        int num(i), encNum = 0;
        QString str=QString("%1").arg(num, size, 2, QChar('0'));
        for(size_t indexCh = 0; indexCh != str.size(); ++indexCh)
            if(str.at(indexCh) == '1')
              encNum += publicVec.at(indexCh);

        encVec.push_back(encNum);
    }

    std::string encTextStr;
    auto beg = encVec.begin();
    for(auto end = encVec.end()-1; beg != end; ++beg)
        encTextStr.append(std::to_string(*beg) + ',');
    encTextStr.append(std::to_string(*beg));

    encText->setText(QString::fromStdString(encTextStr));
}

void MyWindow::decryptClicked(){
    //Update vars
    decVec.clear();
    nInt = n->text().toInt(); mInt = m->text().toInt();
    int inverseN = modInverse(nInt, mInt);

    //Update privateKey
    QString privateKeyStr = privateKey->text();
    QStringList prKeyStrList = privateKeyStr.split(',', QString::SkipEmptyParts);
    privateVec.clear();
    for(const auto &i : prKeyStrList)
        privateVec.push_back(i.toInt());

    //Write down crypted text into vector
    QString encStr = encText->toPlainText();
    QStringList encStrList = encStr.split(',', QString::SkipEmptyParts);
    for(const auto &i : encStrList)
        decVec.push_back(i.toInt());

    //decrypt nums in vector
    for(auto &i : decVec)
        i = (i * inverseN) % mInt;


    std::vector<QString> binaryText(decVec.size());
    for(size_t i = 0; i != decVec.size(); ++i)
        for(auto beg = privateVec.crbegin(), end = privateVec.crend(); beg != end && decVec.at(i) != 0; ++beg){
            if(decVec.at(i) - *beg >= 0){
                decVec.at(i) -= *beg;
                binaryText.at(i).prepend('1');
            }
            else
                binaryText.at(i).prepend('0');
        }

    QString decStr;
    for(const auto &i : binaryText)
        decStr.append(static_cast<char>(bin_to_dec(i)));
    decText->setText(decStr);
}

int modInverse(int a, int m)
{
    a = a%m;
    for (int x=1; x!=m; ++x)
       if ((a*x) % m == 1)
          return x;
}

int bin_to_dec(QString str) {
    int value = 0;
    int base = 1;
    for(int i = str.size();  i != 0; --i) {
        value += (str[i - 1] == '1' ? 1 : 0) * base;
        base *= 2;
    }
    return value;
}
