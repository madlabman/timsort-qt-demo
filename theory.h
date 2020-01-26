#ifndef THEORY_H
#define THEORY_H

#include <QDialog>
#include <QDir>
#include <QFile>

namespace Ui {
class Theory;
}

class Theory : public QDialog
{
    Q_OBJECT

public:
    explicit Theory(QWidget *parent = 0);
    ~Theory();

private:
    Ui::Theory *ui;

private slots:
    void insertBtn_Clicked();
    void mergeBtn_Clicked();
    void timSortBtn_Clicked();
};

#endif // THEORY_H
