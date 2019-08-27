#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <fstream>
#include <QFileDialog>
#include <QString>

#include <QSplashScreen>
#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QDateTime>
#include <QLabel>
#include <QMovie>

double BASIC_LENGTH;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inheight->setStyleSheet("color:blue");
    ui->inwid->setStyleSheet("color:green");
    ui->makePb->setValue(0);
    ui->makePb->hide();
    ui->show->setEnabled(false);
    ui->save->hide();
    ui->showRoad->hide();
    ui->show->setStyleSheet("border-image:url(:/picture/find2.jpg);");
}
void MainWindow::startCartoon(QSplashScreen *splash)
{

    splash->setPixmap(QPixmap(":/picture/gif.gif"));
    QLabel lable(splash);
    QMovie mv(":/picture/gif.gif");
    lable.setMovie(&mv);
    mv.start();
    splash->show();
    splash->setCursor(Qt::BlankCursor);
    QDateTime n=QDateTime::currentDateTime();
    QEventLoop eventloop;
    QTimer::singleShot(3000, &eventloop, SLOT(quit()));
    eventloop.exec();
    splash->setCursor(Qt::ArrowCursor);
}
void MainWindow::initWidget()
{
    if(m.getwid())
    {
        for(int i=0; i<constLong; i++)
            for(int j=0; j<constLong; j++)
            {
                 delete mazeWidget[i][j];
            }
        for(int i=0; i<constLong; i++)
            for(int j=0; j<constLong; j++)
            {
                mazeWidget[i][j] = new QWidget(this);
                mazeWidget[i][j]->hide();
            }

    }
    else
    {
        for(int i=0; i<constLong; i++)
            for(int j=0; j<constLong; j++)
            {
                mazeWidget[i][j] = new QWidget(this);
                mazeWidget[i][j]->hide();
            }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_make_clicked()
{
    ui->make->setEnabled(false);
    ui->show->setEnabled(false);
    ui->show->setStyleSheet("border-image:url(:/picture/find2.jpg);");
    ui->makePb->setValue(0);
    int jindu = 0;

    initWidget(); //初始化
    int h = ui->inheight->value();
    int w = ui->inwid->value();
    if(h <=3 || w <= 3)
    {
        QMessageBox::information(NULL, "警告", "<font color='red'>长宽必须不小于3</font>",QMessageBox::Yes);
        ui->make->setEnabled(true);
        return;
    }
    ui->makePb->show();
    while(jindu != 100)
    {
        QEventLoop eventloop;
        QTimer::singleShot(10, &eventloop, SLOT(quit()));
        eventloop.exec();
        jindu++;
        ui->makePb->setValue(jindu);
    }
    m.initMaze(w, h);
    m.makeMaze();

    BASIC_LENGTH = 70;
    if(BASIC_LENGTH*h>920)            //高23*40=920 宽度39*40=1560
          BASIC_LENGTH = 920/h;
    if(BASIC_LENGTH*w>1560)
          BASIC_LENGTH = 1560/w;

    //窗口变化大小
    if(h*BASIC_LENGTH+80<=600)
        this->setGeometry(40,40,300+w*BASIC_LENGTH,600);
    else
        this->setGeometry(40,40,300+w*BASIC_LENGTH,h*BASIC_LENGTH+80);
    ui->groupBox->move(w*BASIC_LENGTH+40,0);

    //显示迷宫图形
    for(int i=0;i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            mazeWidget[i][j]->setGeometry(40+j*BASIC_LENGTH,40+i*BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
            if(m.Maze[i][j]=='1')
            {
                mazeWidget[i][j]->setStyleSheet("border-image:url(:/picture/1.jpg);");
            }
            else if(m.Maze[i][j]=='0')
            {
                mazeWidget[i][j]->setStyleSheet("border-image:url(:/picture/2.jpg);");
            }
            mazeWidget[i][j]->show();

        }
    }

    ui->make->setEnabled(true);
    ui->show->setEnabled(true);
    ui->show->setStyleSheet("border-image:url(:/picture/find1.jpg);");

    mazeWidget[1][1]->setStyleSheet("border-image:url(:/picture/character1.jpg);");
    mazeWidget[h-2][w-2]->setStyleSheet("border-image:url(:/picture/character2.jpg);");
}

void MainWindow::on_show_clicked()//寻路
{
    ui->make->setEnabled(false);
    ui->show->setEnabled(false);
    ui->show->setStyleSheet("border-image:url(:/picture/find2.jpg);");

    clock_t start_time = clock();

    point a(1, 1);
    m.lu.push(a);

    while(!m.lu.empty())
    {
        point tem = m.lu.front();
        m.lu.pop();
        m.book[1][1] = true;
        mazeWidget[tem.x][tem.y]->setGeometry(40+tem.y*BASIC_LENGTH,40+tem.x*BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
        mazeWidget[tem.x][tem.y]->setStyleSheet("border-image:url(:/picture/2.jpg);");
        mazeWidget[tem.x][tem.y]->show();
        int tx, ty;
        for(int i = 0; i < 4; i++)
        {
            tx = tem.x + dir[i][0];
            ty = tem.y + dir[i][1];
            if(m.Maze[tx][ty] == '0' && !m.book[tx][ty] && tx <=m.getheight() - 2 && ty <=m.getwid() - 2)
            {
                m.book[tx][ty] = true;
                point b(tx, ty);
                m.lu.push(b);
                mazeWidget[tx][ty]->setGeometry(40+ty*BASIC_LENGTH,40+tx*BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
                mazeWidget[tx][ty]->setStyleSheet("border-image:url(:/picture/character3.jpg);");
                mazeWidget[tx][ty]->show();
                map[tx][ty] = tem;
            }
            if(tx == m.getheight() - 2 && ty == m.getwid() - 2)
            {
                break;
            }
         }
        if(tx == m.getheight() - 2 && ty == m.getwid() - 2)
        {
            break;
        }

        QEventLoop eventloop;
        QTimer::singleShot(100, &eventloop, SLOT(quit()));
        eventloop.exec();
        start_time +=100;
    }

    while(!m.lu.empty())
    {
        point tem = m.lu.front();
        m.lu.pop();
        mazeWidget[tem.x][tem.y]->setGeometry(40+tem.y*BASIC_LENGTH,40+tem.x*BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
        mazeWidget[tem.x][tem.y]->setStyleSheet("border-image:url(:/picture/2.jpg);");
        mazeWidget[tem.x][tem.y]->show();
    }

    clock_t end_time = clock();
    t = static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000;
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            m.book[i][j] = false;


    //更新按钮状态
    ui->show->setEnabled(true);
    ui->make->setEnabled(true);
    ui->show->setStyleSheet("border-image:url(:/picture/find1.jpg);");
    ui->save->show();
    ui->showRoad->show();

    mazeWidget[m.getheight()-2][m.getwid()-2]->setStyleSheet("border-image:url(:/picture/character4.jpg);");
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->hide();
    ui->pushButton->hide();
}

void MainWindow::on_showRoad_clicked()//显示路径
{
    mazeWidget[1][1]->setGeometry(40+BASIC_LENGTH,40+BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
    mazeWidget[1][1]->setStyleSheet("border-image:url(:/picture/character1.jpg);");
    mazeWidget[1][1]->show();
    point tem(m.getheight() - 2,m.getwid() - 2);
    number = 0;
    while(tem.x != 1 || tem.y != 1)
    {
        road.push(tem);
        mazeWidget[tem.x][tem.y]->setGeometry(40+tem.y*BASIC_LENGTH,40+ tem.x *BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
        mazeWidget[tem.x][tem.y]->setStyleSheet("border-image:url(:/picture/character3.jpg);");
        mazeWidget[tem.x][tem.y]->show();

        number++;
        tem = map[tem.x][tem.y];
    }
    mazeWidget[m.getheight()-2][m.getwid()-2]->setGeometry(40+(m.getwid()-2)*BASIC_LENGTH,40+(m.getheight()-2)*BASIC_LENGTH,BASIC_LENGTH,BASIC_LENGTH);
    mazeWidget[m.getheight()-2][m.getwid()-2]->setStyleSheet("border-image:url(:/picture/character4.jpg);");
    mazeWidget[m.getheight()-2][m.getwid()-2]->show();
}

void MainWindow::on_save_clicked()//保存数据
{
    ofstream b;

    QString pat =  ui->path->text();
    QByteArray ba = pat.toLatin1();

    char *ch=ba.data();
    b.open(ch, ios::out);
    if(!b.is_open())
    {
        QMessageBox::information(NULL, "警告", "<font color='red'>该文件未成功打开</font>",QMessageBox::Yes);
        return;
    }
    else
    {
        b<< "路径长度:" << number << "\n";
        b<< "运行时间:" <<  t << "ms" << "\n";

        int l = 0;

        b<< "路径沿途坐标：";
        while(!road.empty())
        {
                point t = road.top();
                if(l>15)
                {
                    b << "\n";
                    l = 0;
                }
                b<< "(" << t.x  << " , " << t.y << ")";
                b << "  ";
                l++;

                road.pop();
        }

        b << "\n";
         QMessageBox::information(NULL, "提示：", "保存成功！",QMessageBox::Yes);
    }

}
