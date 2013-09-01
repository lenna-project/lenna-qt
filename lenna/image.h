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

#ifndef IMAGE_H
#define IMAGE_H

#include <QtCore/QObject>
#include <QtGui/QImage>
#include <opencv2/core/core.hpp>

class Image : public QObject
{
    Q_OBJECT
public:
    explicit Image();
    QString getAlbum();
    QString getName();
    void setAlbum(QString album);
    void setName(QString name);

    
signals:
    
public slots:

private:
    IplImage *image;
    QString name;
    QString album;
};

#endif // IMAGE_H
