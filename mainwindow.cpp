#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qlineedit.h"
#include "cmath"
#include "qlistwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,qIntValidator(2,9999,this)
{
    ui->setupUi(this);
    ui->task1->findChild<QLineEdit*>("InputCount")->setValidator(&qIntValidator);
    connect(ui->task1->findChild<QLineEdit*>("InputCount"),SIGNAL(textChanged(QString)),this,SLOT(on_changed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//ForTask1
int count=0;
void MainWindow::on_changed()
{
    count=ui->task1->findChild<QLineEdit*>("InputCount")->text().toInt();
}
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

