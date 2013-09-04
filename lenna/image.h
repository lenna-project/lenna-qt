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
#include <iostream>
#include <sstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Image : public QObject
{
    Q_OBJECT
public:
    Image();
    Image(QString file);
    QString getAlbum();
    QString getName();
    void setMat(cv::Mat *img);
    void setAlbum(QString album);
    void setName(QString name);
    Mat getImage();

    
signals:
    
public slots:

private:
    Mat image;
    QString name;
    QString album;
};

#endif // IMAGE_H
