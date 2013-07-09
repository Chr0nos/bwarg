#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator trad;
    if (trad.load("./lang_" + locale)) a.installTranslator(&trad);
    else if (trad.load("/usr/share/bwarg/lang_" + locale)) a.installTranslator(&trad);

    MainWindow w;
    w.show();
    
    return a.exec();
}
