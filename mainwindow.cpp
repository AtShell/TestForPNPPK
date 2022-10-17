#include "mainwindow.h"
#include "qlineedit.h"
#include "cmath"
#include "qlistwidget.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>

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

//#region Task1
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
//endregion

//#region Task2
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
//#endregion

//#region Task3
struct Node
{
    Node* next;
    int data;
    Node(int value){
        data=value;
        next=nullptr;
    }
};
class List
{
    Node* first;
    Node* last;
public:
    List(){
        first=nullptr;
        last=nullptr;
    }
    bool isEmpty()
    {
        return first == nullptr;
    }
    void pushBack(int value)
    {
        Node *node=new Node(value);
        if(isEmpty())
        {
            first=node;
            last=node;
            return;
        }
        last->next=node;
        last=node;
    }
    QStringList printList()
    {
        int i=1;
        QStringList temp;
        if(isEmpty())
            return temp;
        Node *current=first;
        while(current)
        {
            temp.append("["+QString::number(i)+"] "+QString::number(current->data));
            current = current->next;
            i++;
        }
        return temp;
    }
    QStringList printList(int param)
    {
        int i=1;
        QStringList temp;
        if(isEmpty())
            return temp;
        Node *current=first;
        while(current)
        {
            if(i%param==0)
            {
                temp.append("---deleted--- ("+QString::number(current->data)+")");
            }
            else
                temp.append("["+QString::number(i)+"] "+QString::number(current->data));
            current = current->next;
            i++;
        }
        return temp;
    }
    List DeleteEveryFifthElement()
    {
        int i=1;
        List temp;
        if(isEmpty())
            return temp;
        Node *current=first;
        while(current)
        {
            if(i!=5)
            {
                temp.pushBack(current->data);
                current = current->next;
                i++;
            }
            else
            {
                current = current->next;
                i=1;
            }
        }
        return temp;
    }
};
List task3List;
void Rand(int count)
{
    task3List={};
    while(count>0)
    {
        task3List.pushBack(qrand());
        count--;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->task3->findChild<QListWidget*>("listWidget_3")->clear();
    int countElements=ui->task3->findChild<QSpinBox*>("spinBox")->value();
    Rand(countElements);
    ui->task3->findChild<QListWidget*>("listWidget_3")->addItems(task3List.printList());
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!task3List.isEmpty())
    {
        ui->task3->findChild<QListWidget*>("listWidget_4")->clear();
        ui->task3->findChild<QListWidget*>("listWidget_4")->addItems(task3List.printList(5));
        task3List=task3List.DeleteEveryFifthElement();
        ui->task3->findChild<QListWidget*>("listWidget_3")->clear();
        ui->task3->findChild<QListWidget*>("listWidget_3")->addItems(task3List.printList());
    }
}
//#endregion

//#region Task4
template <typename T>
T bit_count (T input) {
    T res = 0;
    static const unsigned shift_size = ((sizeof(T) * 8)-1);
    if(input < 0) {
        res ++;
        input &= ( (1 << shift_size) - 1 );
    }
    while( input ) {
        res += (input & 1);
        input >>= 1;
    }
    return res;
}
ulong maxNumber(int count)
{
    return std::pow(2,count)-1;
}
void MainWindow::on_pushButton_4_clicked()
{
    ulong value=0;
    if(ui->task4->findChild<QLineEdit*>("lineEdit")->text().toUInt()>=0&&ui->task4->findChild<QLineEdit*>("lineEdit")->text().toUInt()<=UINT_MAX)
    {
        ui->task4->findChild<QLineEdit*>("lineEdit_2")->clear();
        ui->task4->findChild<QLineEdit*>("lineEdit_3")->clear();
        ui->task4->findChild<QLineEdit*>("lineEdit_4")->clear();
        value= ui->task4->findChild<QLineEdit*>("lineEdit")->text().toUInt();
        ui->task4->findChild<QLineEdit*>("lineEdit_2")->insert(QString::number(bit_count(value)));
        ui->task4->findChild<QLineEdit*>("lineEdit_3")->insert("0");
        ui->task4->findChild<QLineEdit*>("lineEdit_4")->insert(QString::number(maxNumber(bit_count(value))));
    }
}
//#endregion

//#region Task5
struct TreeNode
{
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(int value)
    {
        data=value;
        leftChild=nullptr;
        rightChild=nullptr;
    }
    TreeNode()
    {

    }
};
class BinaryTree
{
public:
    TreeNode* root;
    BinaryTree();
    BinaryTree(int);
    void insert(int);
    void print(TreeNode*);
private:
    int size;
};
QStringList TreeList;
BinaryTree::BinaryTree(int value)
{
    root=new TreeNode(value);
    size=1;
}
void BinaryTree::print(TreeNode* current)
{
    if(current)
    {
        print(current->leftChild);
        TreeList.append(QString::number(current->data)+" ");
        print(current->rightChild);

    }
}
void BinaryTree::insert(int value)
{
   TreeNode* current=root;
   while(current&&current->data!=value)
   {
       if(current->data>value&&current->leftChild==NULL)
       {
           current->leftChild=new TreeNode(value);
           size++;
           return;
       }
       if(current->data<value&&current->rightChild==NULL)
       {
           current->rightChild=new TreeNode(value);
           size++;
           return;
       }
       if(current->data>value)
           current=current->leftChild;
       else
           current=current->rightChild;
   }
}
int maxDepth(TreeNode* Tree)
{
if (Tree==NULL) return 0;
return std::max(maxDepth(Tree->leftChild),maxDepth(Tree->rightChild))+1;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->task5->findChild<QListWidget*>("listWidget_5")->clear();
    ui->task5->findChild<QLineEdit*>("lineEdit_5")->clear();
    BinaryTree Tree(qrand());
    int countOfElements=ui->task5->findChild<QSpinBox*>("spinBox_2")->value();
    for(int i=1;i<=countOfElements;i++)
    {
        Tree.insert(qrand());
    }
    Tree.print(Tree.root);
    ui->task5->findChild<QListWidget*>("listWidget_5")->addItems(TreeList);
    TreeList.clear();
    ui->task5->findChild<QLineEdit*>("lineEdit_5")->insert(QString::number(maxDepth(Tree.root)));
    Tree.root=NULL;
}
//#endregion
