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

#include "haarcascadecrop.h"
#include <lenna/logger.h>
#include "widget.h"

#include <chrono>
#include <thread>

#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>

using namespace lenna;
using namespace lenna::plugin::haarcascadecrop;

HaarcascadeCrop::HaarcascadeCrop() { loadCascade(this->cascadeFile); }

HaarcascadeCrop::~HaarcascadeCrop() {
  if (this->widget) {
    // delete this->widget;
    this->widget = nullptr;
  }
}

std::string HaarcascadeCrop::getName() {
  return std::string("haarcascadecrop");
}

std::string HaarcascadeCrop::getTitle() {
  return tr("Haarcascade Crop").toStdString();
}

std::string HaarcascadeCrop::getVersion() { return std::string("0.1"); }

std::string HaarcascadeCrop::getAuthor() { return std::string("FalseCAM"); }

std::string HaarcascadeCrop::getDescription() {
  return tr("Plugin to crop images based on the boundaries the haarcascade "
            "classifier detects.")
      .toStdString();
}

QIcon HaarcascadeCrop::getIcon() {
  return QIcon(":/plugins/haarcascadecrop/haarcascadecrop");
}

QWidget *HaarcascadeCrop::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
    this->widget->setHaarcascadeCrop(this);
    this->widget->setHaarcascade(QString::fromStdString(this->cascadeFile));
  }
  return this->widget;
}

std::shared_ptr<plugin::Plugin> HaarcascadeCrop::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin =
      std::shared_ptr<Plugin>(new HaarcascadeCrop());
  plugin->setUID(uid);
  return plugin;
}

void HaarcascadeCrop::edit(std::shared_ptr<LennaImage> img) {
  cv::Mat image = img->getImage();
  if (this->widget->isCrop()) {
    try {
      std::vector<cv::Rect> objects;
      cv::Mat frame_gray;
      cv::cvtColor(image, frame_gray, cv::COLOR_BGR2GRAY);
      cv::equalizeHist(frame_gray, frame_gray);
      cascade.detectMultiScale(frame_gray, objects, 1.1, 2,
                               0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

      for (size_t i = 0; i < objects.size() && i <= 1; i++) {
        image = image(objects[i]);
      }
    } catch (std::exception &e) {
      Logger::warning(QString::fromLocal8Bit(e.what()));
    }
  }
  img->setMat(image);
}

void HaarcascadeCrop::loadCascade(std::string cascadeFile) {
  try {
    cascade.load(cascadeFile);
    this->cascadeFile = cascadeFile;
    if (widget)
      this->widget->setHaarcascade(QString::fromStdString(cascadeFile));
  } catch (std::exception &e) {
  }
}
