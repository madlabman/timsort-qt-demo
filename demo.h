#ifndef DEMO_H
#define DEMO_H

#include <QDialog>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QtMath>

namespace Ui {
class Demo;
}

class Demo : public QDialog
{
    Q_OBJECT

public:
    int *Array;
    std::vector<int> arr;
    int size;   // размер массива
    int currElem;   //текущий элемент
    QTimer *timer;  //таймер
    int typeOfSort; //выбранная сортировка 0-вставками/1-слияниями/2-тимсорт
    explicit Demo(QWidget *parent = 0);
    ~Demo();

private:
    Ui::Demo *ui;
    void showMerge(int p, QGraphicsScene *scene);   //отобразить слияния
    void showTimsort(); //демонстрация Тимсорт
    bool inputIsValid();    //проверка на соответствие ввода

private slots:
    void Update();
    void sortBtn_Clicked();
    void demoInsertSortBtn_Clicked();
    void demoMergeSortBtn_Clicked();
    void demoTimSortBtn_Clicked();
};

#endif // DEMO_H
