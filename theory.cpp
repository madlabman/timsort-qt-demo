#include "theory.h"
#include "ui_theory.h"

Theory::Theory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theory)
{
    ui->setupUi(this);
    ui->webView->setHtml("<html><body><center><h3 align=\"center\">Нажмите одну из кнопок наверху для получения теоретического материала по выбранному алогоритму.</h3></center></body><html>");
    //нажатие на кнопку сортировки вставками
    connect(ui->insBtn, SIGNAL(clicked()), this, SLOT(insertBtn_Clicked()));
    //нажатие на кнопку сортировки слияниями
    connect(ui->mergeBtn, SIGNAL(clicked()), this, SLOT(mergeBtn_Clicked()));
    //нажатие на кнопку алогоритм сортировки
    connect(ui->timSortBtn, SIGNAL(clicked()), this, SLOT(timSortBtn_Clicked()));
}

Theory::~Theory()
{
    delete ui;
}

void Theory::insertBtn_Clicked()
{
    //ui->webView->setEnabled(true);
    QFile file(QDir::current().absoluteFilePath("insert_sort.html"));   //веб-страница документации
    if(!file.open(QFile::ReadOnly))
    {
        qDebug("Файл не найден");
    }
    else
    {
        //ui->textBrowser->setHtml(file.readAll());   //чтение содержимого
        ui->webView->setHtml(file.readAll());
        file.close();
    }
}

void Theory::mergeBtn_Clicked()
{
    //ui->webView->setEnabled(true);
    QString fileName = QDir::current().absoluteFilePath("merge_sort.html");
    QFile file(fileName);   //веб-страница документации
    if(!file.open(QFile::ReadOnly))
    {
        qDebug("Файл не найден");
    }
    else
    {
        //ui->textBrowser->setHtml(file.readAll());   //чтение содержимого
        QUrl baseUrl = QUrl::fromLocalFile(fileName);
        ui->webView->setHtml(file.readAll(), baseUrl);
        file.close();
    }
}

void Theory::timSortBtn_Clicked()
{
    //ui->textBrowser->setEnabled(true);  //активировать браузер
    ui->webView->setEnabled(true);
    QString fileName = QDir::current().absoluteFilePath("tim_sort.html");
    QFile file(fileName);   //веб-страница документации
    if(!file.open(QFile::ReadOnly))
    {
        qDebug("Файл не найден");
    }
    else
    {
        //ui->textBrowser->setHtml(file.readAll());   //чтение содержимого
        QUrl baseUrl = QUrl::fromLocalFile(fileName);
        ui->webView->setHtml(file.readAll(), baseUrl);
        file.close();
    }
}
