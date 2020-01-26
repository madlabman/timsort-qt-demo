#ifndef TEST_H
#define TEST_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

namespace Ui {
class Test;
}

class Test : public QDialog
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    bool loadTest(QString filename);
    void showAnswers();
    ~Test();

private:
    Ui::Test *ui;
    QString kEncryptorString;   //ключ шифрования файла
    int keyIndex(int index);
    QString cryptString(QString toCrypt);

private slots:
    void nextBtn_Cliked();
};

#endif // TEST_H
