#include "demo.h"
#include "ui_demo.h"
#include "sorts.h"

Demo::Demo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Demo)
{
    ui->setupUi(this);
    this->setFixedSize(407, 400);

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    scene->addText("Выберите один из алгоритмов сортировки, нажав\nсоответствующие кнопки в верхней части окна.\n\nДля сортировки массива, заполненного случайным \nобразом, отметьте флажок \"Случайно\".\n\nДля сортировки массива, заданногo вручную,\nвведите числа, разделенные пробелом, в поле ввода.\n\nДля начала демонстрации нажмите кнопку Сортировать.");
    ui->graphicsView->setScene(scene);
    ui->lineEdit->setEnabled(false);
    //инициализация
    Array = nullptr;
    //arr = new std::vector<int>();
    size = 0;
    currElem = 1;
    typeOfSort = -1;
    // Таймер на обновление изображения.
    timer = new QTimer();
    timer->setInterval(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    connect(ui->sortBtn, SIGNAL(clicked()), this, SLOT(sortBtn_Clicked()));
    connect(ui->demoInsertSortBtn, SIGNAL(clicked()), this, SLOT(demoInsertSortBtn_Clicked()));
    connect(ui->demoMergeSortBtn, SIGNAL(clicked()), this, SLOT(demoMergeSortBtn_Clicked()));
    connect(ui->demoTimSortbtn, SIGNAL(clicked()), this, SLOT(demoTimSortBtn_Clicked()));
}

void Demo::showMerge(int p, QGraphicsScene *scene)
{
    //вывод на экран
    static bool color = false;
    QPen *pen;
    if (!color)
        pen = new QPen(Qt::blue);
    else
        pen = new QPen(Qt::red);

    int start = 0;
    while(start < size)
    {
        scene->addText(QString::number(Array[start]))->setPos(start * 15, 25 * (qLn(p)/qLn(2)));
        start++;
    }
    //рисуем рамки
    if (size % 2 != 0)
    {
        for (int n = 0; n < size; n+=p)
        {
            if (n + p < size)
            {
                scene->addRect( n * 15, 25 * (qLn(p)/qLn(2)), 15 * p, 17, *pen);
            }
            else if (n + p > size)
            {
                scene->addRect( n * 15, 25 * (qLn(p)/qLn(2)), 15 * (size - n) , 17, *pen);
            }
            else if (n + p == size)
            {
                scene->addRect( n * 15, 25 * (qLn(p)/qLn(2)), 15 , 17, *pen);
            }
        }
    }
    else
    {
        for(int n = 0; n < size; n+=p)
        {
            if (n + p <= size)
            {
                scene->addRect( n * 15, 25 * (qLn(p)/qLn(2)), 15 * p, 17, *pen);
            }
            else if (n + p > size)
            {
                scene->addRect( n * 15, 25 * (qLn(p)/qLn(2)), 15 * (size - n) , 17, *pen);
            }
        }
    }
    color = color ? false : true;
}

// Собственно обновление по тику.
void Demo::Update()
{

    if (typeOfSort == 0 && Array != nullptr)    //если выбрана сортировка вставками
    {
        int shift = Array[size];
        // Нужно вывести массив на экран в том состоянии, в котором он сейчас.

        // Инициализруем сцену.
        QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);

        // пока не пройден весь массив
        if (currElem < size)
        {
            for(int i = 0; i < size; i++)
            {
                // обводим кругом элемент, который обрабатываем
                if(i == shift)
                {
                    scene->addEllipse(15 * i - 0.5, 0 + 3.5, 15, 15, QPen(Qt::red, 2));
                }
                scene->addText(QString::number(Array[i]))->setPos(15 * i, 0);
                ui->graphicsView->setScene(scene);
            }
            if (Array[shift - 1] > Array[shift] && shift > 0)
            {
                std::swap(Array[shift - 1], Array[shift]);
                Array[size]--;
            }
            else
            {
                currElem++;
                Array[size] = currElem;
            }
        }
        else
        {
            // распечатать массив
            for(int i = 0; i < size; i++)
            {
                scene->addText(QString::number(Array[i]))->setPos(15 * i, 0);
                ui->graphicsView->setScene(scene);
            }
            Array[size] = 1;
            timer->stop();

        }
    }
    else if (typeOfSort == 1 && Array != nullptr)   //сортировка слиянием
    {
        //получаем сцену
        QGraphicsScene *scene = ui->graphicsView->scene();
        //перебираем все размеры кусочков для слияния
        if(Array[size] != 0 && Array[size] < size)
        {
            int p = Array[size];    //размер куска
            int start = 0; //начало первого кусочка пары
            //временный массив
            int* tmp( new int[size]);
            //вывод на экран
            showMerge(p, scene);

            for(; (start + p) < size; start+=p*2)
            {
                //Перебираем все пары кусочков, и выполняем попарное
                //  слияние. (start+size)<n означает, что начало
                //  следующего кусочка лежит внутри массива

                sort::Merge(Array + start, p,
                            Array + start + p, std::min(p, size - start - p),
                            tmp + start);
            }
            //Если последний кусочек остался без пары, просто
            //копируем его из A в B:
            for(; start<size; ++start) tmp[start]=Array[start];
            //обновляем массив
            //вывод очередного куска на экран
            for (int i = 0; i < size; ++i)
            {
                Array[i] = tmp[i];
            }
            //удаляем временный массив
            delete [] tmp;
            if((Array[size] *= 2) >= size)
            {
                showMerge(p * 2, scene);
            }

        }
    }
}

QString retMass(std::vector<int> arr, int b, int l)
{
    QString mass = "";
    for (int i = b; i < l; i++)
    {
        mass += QString::number(arr[i]);
        if(i != l - 1)
        {
            mass += "   ";
        }
        else
        {
            mass += "→";
        }
    }
    return mass;
}

void Demo::showTimsort()
{
    //создаем сцену
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    //шаг0minrun
    int minrun = Timsort::get_min_size(arr.size());

    scene->addText("Шаг 0: вычисляем minrun: " + QString::number(minrun))->setPos(0, 0);
    scene->addText("Шаг 1: Входные данные разбиваются на подмассивы\nдлиной minrun или более, если массив полностью упорядочен")->setPos(0, 20);
    //вывод сокращенной записи входного массива
    QString mass = "";
    for (int i = 0, n = 1; i < 14; i++)
    {
        mass += QString::number(arr[n]);
        if(i != 13)
        {
            mass += " ... ";
        }
        n += size / 14;
    }
    scene->addText(mass)->setPos(0, 65);
    scene->addRect(0, 65, 325, 17);
    //вывести подмассив
    mass = retMass(arr, 0, 7);
    scene->addText(mass)->setPos(0, 85);
    scene->addRect(0, 85, 15 * (7 + 1) + 5, 17);

    scene->addText("Шаг 2: Подмассивы упорядочиваются сортировкой вставками")->setPos(0, 110);
    Timsort::insertSort(arr, 0, 7);
    mass = retMass(arr, 0, 7);
    scene->addText(mass)->setPos(0, 130);
    scene->addRect(0, 130, 15 * (7 + 1) + 5, 17);

    scene->addText("Шаг 3: Отсортированные подмассивы сливаются")->setPos(0, 150);
    Timsort::insertSort(arr, 7, 14);
    scene->addText(retMass(arr, 0, 7))->setPos(0, 170);
    scene->addText(retMass(arr, 7, 14))->setPos(15 * (7 + 1) + 5, 170);
    scene->addRect(0, 170, 15 * (7 + 1) + 3, 17);
    scene->addRect(15 * (7 + 1) + 5, 170, 15 * (7 + 1) + 5, 17);
    Timsort::insertSort(arr, 0, 14);
    scene->addText(retMass(arr, 0, 14))->setPos(0, 190);
    scene->addRect(0, 190, 15 * 16, 17);
    scene->addText("до тех пор, пока не будет получен единый упорядоченный массив.\nКонец.")->setPos(0, 210);

    ui->graphicsView->setScene(scene);

}

bool Demo::inputIsValid()
{
    QString in = ui->lineEdit->text();
    for (int n = 0; n < in.length(); ++n)
    {
        if ((in[n] >= '0' && in[n] <= '9') || in[n] == ' ')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Demo::sortBtn_Clicked()
{
    // если не тимсорт, пользоватлеь ничего не вводит и не генерит
    if (typeOfSort == 0 || typeOfSort == 1)
    {
        // если стоит галка рандом, заполняем массив случайным образом
        if (ui->randomBox->isChecked())
        {
            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));

            size = 15;
            Array = new int[size + 1];
            // рандомно забиваем массив
            for (int i = 0; i < size; ++i)
            {
                Array[i] = qrand() % 10;
            }
            //индекс сдвига
            Array[size] = 1;
            currElem = 1;
        }
        else if(inputIsValid())
        {
            //иначе читаем из строки
            QStringList list = ui->lineEdit->text().split(" ", QString::SkipEmptyParts);
            if (list.size() != 0)
            {
                Array = new int[list.size() + 1];
                for (int i = 0; i < list.size(); ++i)
                {
                    Array[i] = list[i].toInt();
                }
                size = list.size();
                Array[size] = 1;
                currElem = 1;
            }
            else
            {
                //выводим предупреждение
                QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
                scene->addText("Введите массив или поставьте флажок \"Случайно\"!");
                ui->graphicsView->setScene(scene);
                return;
            }
        }
        else
        {
            //выводим предупреждение
            QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
            scene->addText("Неверно задан массив, проверьте ввод!\nДопустимы цифры 0-9 и пробел.");
            ui->graphicsView->setScene(scene);
            return;
        }
        // создаем новую сцену
        QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
        ui->graphicsView->setScene(scene);

        timer->start();
    }
    else if(typeOfSort == 2)
    {
        //тимсорт
        //данные читаем из файла
        //результат будет возвращаться также в файл
        arr.clear();
        QFile file("data.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug("Cannot open a file");
            QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
            scene->addText("Входной файл не найден!");
            ui->graphicsView->setScene(scene);
        }
        else
        {
            QTextStream in(&file);
            QString data = in.readAll();
            QStringList list = data.split(" ", QString::SkipEmptyParts);
            //заполнить массив
            for (int i = 0; i < list.size(); ++i)
            {
                arr.push_back(list[i].toInt());
            }
            size = list.size();
            showTimsort();
        }
    }
}

void Demo::demoInsertSortBtn_Clicked()
{
    if (timer->isActive())
        timer->stop();
    typeOfSort = 0;
    setFixedSize(407, 170);
    ui->lineEdit->setEnabled(true);
    ui->randomBox->setEnabled(true);
    ui->lineEdit->setText("");
    /*// очистить экран, если что-то нарисовано
    if (ui->graphicsView->scene())
    ui->graphicsView->scene()->clear();*/
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    scene->addText("Для начала демонстрации нажмите Сортировать")->setPos(0, 0);
    ui->graphicsView->setScene(scene);
}

void Demo::demoMergeSortBtn_Clicked()
{
    if (timer->isActive())
        timer->stop();
    typeOfSort = 1;
    setFixedSize(407, 320);
    ui->lineEdit->setEnabled(true);
    ui->randomBox->setEnabled(true);
    ui->lineEdit->setText("");
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    scene->addText("Для начала демонстрации нажмите Сортировать")->setPos(0, 0);
    ui->graphicsView->setScene(scene);
}

void Demo::demoTimSortBtn_Clicked()
{
    if (timer->isActive())
        timer->stop();
    typeOfSort = 2;
    setFixedSize(407, 400);
    ui->lineEdit->setText("");
    ui->lineEdit->setEnabled(false);
    ui->randomBox->setEnabled(false);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    scene->addText("Для начала демонстрации нажмите Сортировать")->setPos(0, 0);
    ui->graphicsView->setScene(scene);
}

Demo::~Demo()
{
    delete ui;
}
