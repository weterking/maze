#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QSplashScreen>
#include <QDateTime>
#include <QLabel>
#include <QMovie>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSplashScreen *splash=new QSplashScreen;
    w.startCartoon(splash);
    w.show();
    splash->finish(&w);
    return a.exec();
}
