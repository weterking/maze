#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "my_stack.h"
#include <QMainWindow>
#include <QWidget>
#include <time.h>
#include "Matrix.h"

#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QSplashScreen>
#include <QDateTime>
#include <QLabel>
#include <QMovie>
const int constLong = 100;
extern double BASIC_LENGTH;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initWidget();
    QWidget* mazeWidget[constLong][constLong];
    void startCartoon(QSplashScreen *);

private slots:


    void on_show_clicked();

    void on_make_clicked();

    void on_pushButton_clicked();

    void on_showRoad_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    mystack road;
    QWidget* BInterface;
    Matrix m;
    double t;
    point map[100][100];
    int number;
};

#endif // MAINWINDOW_H
