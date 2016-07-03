/**
    This file is part of program Lenna
    Copyright (C) 2016 FalseCAM

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

#include "crop.h"
#include "widget.h"

#include <chrono>
#include <thread>

#include <QtGui/QPainter>
#include <opencv2/calib3d/calib3d.hpp>

using namespace lenna;
using namespace lenna::plugin::crop;

Crop::Crop() {}

Crop::~Crop() {
  if (this->widget) {
    // delete this->widget;
    this->widget = nullptr;
  }
}

QString Crop::getName() { return QString("crop"); }

QString Crop::getTitle() { return QString(tr("Crop")); }

QString Crop::getVersion() { return QString("0.1"); }

QString Crop::getAuthor() { return QString("FalseCAM"); }

QString Crop::getDescription() { return QString(tr("Plugin to crop images")); }

QIcon Crop::getIcon() { return QIcon(":/plugins/crop/crop"); }

QWidget *Crop::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

void Crop::edit(std::shared_ptr<LennaImage> img) {
  cv::Mat image = img->getImage();

  widget->setImage(image);
  while (!widget->isActionDone()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  // 4 corners of image
  std::vector<cv::Point2f> image_points;
  image_points.push_back(cv::Point2f(float(0), float(0)));
  image_points.push_back(cv::Point2f(float(0), float(image.rows)));
  image_points.push_back(cv::Point2f(float(image.cols), float(image.rows)));
  image_points.push_back(cv::Point2f(float(image.cols), float(0)));

  std::vector<cv::Point2f> points = widget->getPoints();
  cv::Mat h = cv::findHomography(points, image_points);

  cv::Size s;
  s.width = image.cols;
  s.height = image.rows;
  cv::warpPerspective(image, image, h, s);

  img->setMat(image);
}
