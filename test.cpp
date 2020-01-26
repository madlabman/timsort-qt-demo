#include "test.h"
#include "ui_test.h"

int Test::keyIndex(int index)
    {
        int len = kEncryptorString.length();
        int multiple = index / len;
        if ( index >=  len ) {
            return index - (len * multiple);
        }
        return index;
    }

QString Test::cryptString(QString toCrypt)
    {
        QString resultString = "";
        for ( int i = 0; i < toCrypt.length(); i++)
        {
            resultString.append(QString(QChar(toCrypt[i]).unicode()^QChar(kEncryptorString[keyIndex(i)]).unicode()));
        }
        return resultString;
    }

// массив кнопок для ответов
QRadioButton* AnswLabel[5];

Test::Test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(nextBtn_Cliked()));
    //иницаиализация
    AnswLabel[0] = ui->rbAnsw1;
    AnswLabel[1] = ui->rbAnsw2;
    AnswLabel[2] = ui->rbAnsw3;
    AnswLabel[3] = ui->rbAnsw4;
    AnswLabel[4] = ui->rbAnsw5;
    //сокрытие
    //вопроса
    ui->lbQuestion->hide();
    //ответов
    for(int i=0;i<5; i++)
        AnswLabel[i]->hide();
    kEncryptorString = QString("timsort");
    //загрузка теста
    if(loadTest("test.txt"))
    {
        //начать тест
        showAnswers();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка!", "Файл теста не найден!");
        ui->nextBtn->hide();
        ui->lbQuestion->setText("Файл теста не найден!");
        ui->lbQuestion->show();
    }
}

struct Testing
{
    QString* answer;
    QString question;
    int countAnswer;
    int trueAnswer;
};

Testing* test;
int CountTests;
int* Answers;
int CountAnswers()
{
    int count = 0;
    for(int i=0;i<CountTests; i++)
        if(Answers[i])
            count++;
    return count;
}

bool Test::loadTest(QString filename)
{
    int n;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() <<  "Cannot open a file";
        return false;
    }

    QTextStream in(&file);
    n = in.readLine().toInt();
    CountTests = n;
    test = new Testing[n];
    for(int i=0; i<n; i++)
    {
       test[i].countAnswer = in.readLine().toInt();
       test[i].question = in.readLine();
       test[i].answer = new QString[test[i].countAnswer];
       for(int j=0; j<test[i].countAnswer; j++)
       {
           test[i].answer[j] = in.readLine();
       }
       test[i].trueAnswer = in.readLine().toInt();
    }

    Answers = new int[CountTests];
    for(int i=0;i<CountTests; i++)
        Answers[i] = 0;

    return true;
}

//текущий вопрос из файла
int currentQuestion;
//счетчик вопросов
int T=1;

void Test::showAnswers()
{
    qsrand (QDateTime::currentMSecsSinceEpoch());
    int n;
    do
    {
        n = qrand()%CountTests;
    }
    while(Answers[n]!=0);
    currentQuestion = n;
    QString str="Вопрос № ";
    str +=QString::number(T);
    str +=" : ";
    T++;
    str += test[n].question;
    ui->lbQuestion->setText(str);
    ui->lbQuestion->show();


    for(int i=0;i<test[n].countAnswer; i++)
    {
        AnswLabel[i]->setText(test[n].answer[i]);
        AnswLabel[i]->show();
    }

    QAbstractButton* checked = ui->buttonGroup->checkedButton();
    if (checked)
    {
        ui->buttonGroup->setExclusive(false);
        checked->setChecked(false);
        ui->buttonGroup->setExclusive(true);
    }
    for(int i=test[n].countAnswer;i<5; i++)
    {
        AnswLabel[i]->hide();
    }
}

void Test::nextBtn_Cliked()
{
    bool f = true;
        for(int i=0;i<5; i++)
        {
            if(AnswLabel[i]->isChecked())
            {
                Answers[currentQuestion] = i+1;
                f = false;
                break;
            }
        }
        if(f)
            return;
        if(CountAnswers()>9)
        {
            int count = 0;
            for(int i=0;i<CountTests; i++)
                if(Answers[i] && Answers[i]==test[i].trueAnswer)
                    count++;
            for(int i=0;i<CountTests; i++)
                Answers[i] = 0;
            QString str = "Правильных ответов:  ";
            str += QString::number(count);

            for(int i=0;i<5; i++)
                AnswLabel[i]->hide();
            if(count<7)
                  str+= "\nНеудовлетворительно!";
            else if(count<8)
                  str+= "\nУдовлетворительно!";
            else if(count<9)
                 str+= "\nХорошо!";
            else
               str+= "\nОтлично!";

            //ui->lbQuestion->setText(str);
            ui->lbQuestion->setVisible(false);
            QMessageBox::information(this, "Ваш результат", str);
            ui->nextBtn->hide();
            T=1;
            this->close();
        }
        else
        {
            showAnswers();
        }
}

Test::~Test()
{
    delete ui;
}
