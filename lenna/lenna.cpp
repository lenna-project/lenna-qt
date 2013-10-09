/**
    This file is part of program Lenna
    Copyright (C) 2013  FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lenna.h"
#include <QtCore/QCoreApplication>

using namespace lenna;

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
