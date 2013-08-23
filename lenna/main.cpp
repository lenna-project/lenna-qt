#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "lenna.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lenna::setApplicationName("Lenna");
    Lenna::setApplicationVersion("0.1");
    Lenna::setOrganizationName("FalseCAM");
    a.setWindowIcon(Lenna::applicationIcon());
    MainWindow w;
    w.show();
    
    return a.exec();
}
