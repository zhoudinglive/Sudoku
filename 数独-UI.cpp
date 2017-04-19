#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "sudoku.h"
#include<QMessageBox>
#include<QString>
#include<QDialog>
#include<QLabel>
#include<QDebug>
#include<QTextStream>
#include<stdio.h>
#include<QDesktopWidget>
#include<iomanip>
#include<QTableWidgetItem>
bool is_go=false;
bool is_go2;
bool is_go3;
bool is_go4;
int score;
MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    this->ui->tableWidget->setAlternatingRowColors(true);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::on_pushButton_4_clicked()
{
    QMessageBox::about(this,tr("About"),
         tr("                   About Sudoku2.0\n"
            "      This program may have some bugs,so     \t\n"
            "      if you find one,please send an email to    \t\n"
            "      me,my email address is:                \t\n"
            "              zhoudinglive@foxmail.com.               \t\n\n"
            "              Thanks for your support!"));
}

void MyMainWindow::on_pushButton_3_clicked()
{
    close();
}

void MyMainWindow::on_pushButton_clicked()
{
    QString str;
    str=ui->comboBox->currentText();
    maincreat(str);
    is_go2=false;
    is_go3=true;
    is_go4=true;
    this_count++;
    if(this_count>1)
        ui->tableWidget->clear();

    score=100;
    ui->label_4->setText(QString::number(score));
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            if(question_array[i][j]!=0)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(question_array[i][j])));
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->item(i,j)->setFlags(Qt::NoItemFlags);
                ui->tableWidget->item(i,j)->setTextColor(QColor(0,0,0));
            }
    is_go=true;
    is_go2=true;
}

void MyMainWindow::on_pushButton_2_clicked()
{
    if(!is_go)
        QMessageBox::information(this,tr("Information"),
           tr("Sorry, you'd better start the game at first!"));
    else
    {
        ui->tableWidget->clear();
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(answer_array[i][j])));
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->item(i,j)->setFlags(Qt::NoItemFlags);
                ui->tableWidget->item(i,j)->setTextColor(QColor(0,0,0));
            }
        if(is_go4)
            ui->label_4->setText("100");
    }
}


void MyMainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
   if(is_go2&&is_go3)
   {
       QString num=item->data(Qt::DisplayRole).toString();
       if(num!=""&&num!="1"&&num!="2"&&num!="3"&&num!="4"&&num!="5"&&num!="6"&&num!="7"&&num!="8"&&num!="9")
       {
           QMessageBox::warning(this,tr("Warning"),
                                tr("Sorry,input error,please\n"
                                    "input a num between 1 to 9."));
           item->setText("");
       }
       else
       {
           int row=item->row();
           int column=item->column();
           if(num.toInt()!=answer_array[row][column]&&num!="")
           {
               QMessageBox::warning(this,tr("Warning"),
                                    tr("Sorry,wrong answer!"));
               item->setText("");

               score-=5;
               ui->label_4->setText(QString::number(score));
               if(score==0)
               {
                   QMessageBox::warning(this,tr("Warning"),
                                        tr("Game over ,you lose!"));
                   is_go3=false;
                   is_go4=false;
                   on_pushButton_2_clicked();

               }
           }
           else if(num.toInt()==answer_array[row][column]&&num!="")
           {
               item->setTextAlignment(Qt::AlignCenter);
               item->setTextColor(QColor(255,0,0));
               score+=1;
               ui->label_4->setText(QString::number(score));
           }
       }
   }
}

void MyMainWindow::on_pushButton_5_clicked()
{
    QMessageBox::information(this,tr("Hint"),
                             tr("1)Click an empty slot...\n"
                                "2)...then input an number\n"
                                "3)At the first of the game,you have 100 points...\n"
                                "4)...answer right will add 3 points,else minus 5 points\n"
                                "5)...if your current score is 0,game over,you lose"));
}
