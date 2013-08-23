#include "splashscreen.h"
#include <QtGui/QPixmap>

SplashScreen::SplashScreen(QWidget *parent) :
    QSplashScreen(parent)
{
    //setPixmap(QPixmap(":/logo/lenna_logo"));
}


void SplashScreen::setMessage(QString message){
    showMessage(message, Qt::AlignTop | Qt::AlignRight, Qt::red);
}
