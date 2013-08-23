#include "lenna.h"
#include <QtCore/QCoreApplication>

void Lenna::setApplicationName(QString name){
    QCoreApplication::setApplicationName(name);
}

void Lenna::setApplicationVersion(QString version){
    QCoreApplication::setApplicationVersion(version);
}

void Lenna::setOrganizationName(QString organization_name){
    QCoreApplication::setOrganizationName(organization_name);
}

QString Lenna::applicationName(){
    return QCoreApplication::applicationName();
}

QString Lenna::applicationVersion(){
    return QCoreApplication::applicationVersion();
}

QString Lenna::organizationName(){
    return QCoreApplication::organizationName();
}

QIcon Lenna::applicationIcon(){
    return QIcon(":/logo/lenna_logo");
}

QString Lenna::applicationDirPath(){
    return QCoreApplication::applicationDirPath();
}

void Lenna::installTranslator(QTranslator *file){
    QCoreApplication::installTranslator(file);
}

void Lenna::destroy(){
}
