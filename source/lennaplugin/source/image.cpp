/**
    This file is part of program Lenna
    Copyright (C) 2013-2016  FalseCAM

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

#include "lenna/image.h"

using namespace lenna;
using namespace cv;

Image::Image() {}

Image::Image(Image &image) {
  this->name = image.name;
  this->album = image.album;
  image.getImage().copyTo(this->image);
  this->exifData = image.exifData;
}

Image::Image(QString file) {
  this->image = cv::imread(file.toStdString().c_str(), cv::IMREAD_UNCHANGED);
}

void Image::setMat(Mat img) { this->image = img; }

QString Image::getAlbum() { return this->album; }

QString Image::getName() { return this->name; }

void Image::setAlbum(QString album) { this->album = album; }

void Image::setName(QString name) { this->name = name; }

Mat Image::getImage() { return this->image; }

Mat *Image::getImagePointer() { return &this->image; }

void Image::convolve(Mat filter) {
  cv::filter2D(this->image, this->image, -1, filter);
}

QImage Image::toQImage() {
  return QImage((uchar *)image.data, image.cols, image.rows, image.step1(),
                QImage::Format_RGB32);
}

Exiv2::ExifData Image::readMetaData(std::string file) {
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file.c_str());
  image->readMetadata();
  this->exifData = image->exifData();
  return image->exifData();
}

Exiv2::ExifData *Image::getMetaData() { return &this->exifData; }
