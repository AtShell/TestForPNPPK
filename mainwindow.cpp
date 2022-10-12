#include "mainwindow.h"
//#include "./ui_mainwindow.h"
#include "qlineedit.h"
#include "cmath"
#include "qlistwidget.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <vector>
#include <map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,qIntValidator(1,100000,this)
{
    ui->setupUi(this);
    ui->task1->findChild<QLineEdit*>("InputCount")->setValidator(&qIntValidator);
    connect(ui->task1->findChild<QLineEdit*>("InputCount"),SIGNAL(textChanged(QString)),this,SLOT(on_changed()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
int count=0; //for task1

//ForTask1
bool is_prime(uint n)
{
    if (n == 2)
        return true;
    if (n == 1)
        return false;
    for (uint i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
QStringList GetPrimeNumbers(int count,QStringList primelist){
    uint temp=1;
    int counter=1;
    for(int i=1;i<=count;i++){
        while (true)
        {
            if (is_prime(temp) == false)
                temp++;
            else
                break;
        }
        primelist.append("["+QString::number(counter)+"] "+QString::number(temp));
        temp++;
        counter++;
    }
    return primelist;
}
void MainWindow::on_changed()
{
    count=ui->task1->findChild<QLineEdit*>("InputCount")->text().toInt();
}

void MainWindow::on_getButton_clicked()
{
    if(count>0)
    {
        ui->task1->findChild<QListWidget*>("listWidget")->clear();
        QListWidgetItem *item = new QListWidgetItem;
        QStringList primelist;
        primelist=GetPrimeNumbers(count,primelist);
        ui->task1->findChild<QListWidget*>("listWidget")->addItems(primelist);
    }
}

//Task2
QStringList GetCountWordAndLength(QString str,QStringList list)
{
    std::map<int,int> sizeAndCount;
    std::map<int,int> ::iterator it;
    int currentLength=0;
    for(int i=0;i<str.size();i++)
    {
        if (str[i] != ' ' && str[i] != '!' && str[i] != '.' && str[i] != ',' && str[i] != '?' && str[i] != ':'&&i!=str.size())
        {
            currentLength++;
        }
        else if(currentLength!=0)
        {
            it=sizeAndCount.find(currentLength);
            if(it!=sizeAndCount.end())
            {
                sizeAndCount[currentLength]+=1;
            }
            else
            {
                sizeAndCount[currentLength]=1;
            }
            currentLength=0;
        }

    }
    int countWord=0;
    for(it=sizeAndCount.begin();it!=sizeAndCount.end();it++)
        countWord+=it->second;
    list.append("----Кол-во слов в предложении: "+QString::number(countWord)+"----");
    for(it=sizeAndCount.begin();it!=sizeAndCount.end();it++)
    {
        list.append("Длиной "+QString::number(it->first)+" = "+QString::number(it->second)+" слов");
    }
    return list;
}
void MainWindow::on_pushButton_clicked()
{
    if(!(ui->task2->findChild<QLineEdit*>("lineEditTask2")->text().isEmpty()))
    {
        ui->task2->findChild<QListWidget*>("listWidget_2")->clear();
        QStringList wordList;
        wordList=GetCountWordAndLength(ui->task2->findChild<QLineEdit*>("lineEditTask2")->text()+" ",wordList);
        ui->task2->findChild<QListWidget*>("listWidget_2")->addItems(wordList);
    }
}

