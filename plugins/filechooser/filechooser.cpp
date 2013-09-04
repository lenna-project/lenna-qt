/**
    This file is part of program Reihenaufnahme
    Copyright (C) 2012  FalseCAM

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

#include "filechooser.h"
#include "widget.h"
#include <QtWidgets/QProxyStyle>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>

FileChooser::FileChooser()
{
    this->widget = 0;
    has_next = false;
	this->position = 0;
}

FileChooser::~FileChooser()
{
}

QString FileChooser::getName(){
    return QString("filechooser");
}

QString FileChooser::getTitle(){
    return QString(tr("Filechooser"));
}

QString FileChooser::getVersion(){
    return QString("1.0");
}

QString FileChooser::getAuthor(){
    return QString("FalseCAM");
}

QString FileChooser::getDescription(){
    return QString(tr("Plugin to load images from desktop."));
}

QIcon FileChooser::getIcon(){
    QProxyStyle s;
    return s.standardIcon (QStyle::SP_FileIcon);
}

QWidget *FileChooser::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void FileChooser::init(){
    this->files = widget->getFiles();
    this->position = 0;

    if(!(position >= files.size())){
        has_next = true;
    } else {
        has_next = false;
    }
}

bool FileChooser::hasNext(){
    return has_next;
}

Image *FileChooser::next(){
    if(has_next){
        QString file = this->files.at(this->position);
        //QImage *image = new QImage(file);
        QString album = getFolder(file);
        QString name = getName(file);
        position++;
        if(position >= this->files.size()){
            has_next = false;
        }
        // TODO
        Image *img = new Image(file);
        img->setName(name);
        img->setAlbum(album);
        return img;
    }

    return 0;
}

int FileChooser::getProgress(){
    int progress = 0;
    if(files.size()>0)
        progress = 100 * position / files.size();
    return progress;
}

QString FileChooser::getName(QString file){
    QString name;
    name = QFileInfo(file).baseName();
    return name;
}

QString FileChooser::getFolder(QString file){
    QString folder;
    folder = QDir(QFileInfo(file).absoluteDir()).dirName();
    return folder;
}
