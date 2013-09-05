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

#include "image.h"

Image::Image() {

}

Image::Image(Image &image){
    this->name = image.name;
    this->album = image.album;
    image.getImage().copyTo(this->image);
}

Image::Image(QString file){
    this->image = imread(file.toStdString().c_str(), 1);
}

void Image::setMat(cv::Mat *img){

}

QString Image::getAlbum() {
    return this->album;
}

QString Image::getName() {
    return this->name;
}

void Image::setAlbum(QString album) {
    this->album = album;
}

void Image::setName(QString name) {
    this->name = name;
}

Mat Image::getImage(){
    return this->image;
}

Mat *Image::getImagePointer(){
    return &this->image;
}

void Image::convolve(Mat filter){
    cv::filter2D(this->image,this->image,-1, filter);
}

QImage Image::toQImage(){
    return QImage((uchar*)image.data, image.cols, image.rows, image.step1(), QImage::Format_RGB32);
}
