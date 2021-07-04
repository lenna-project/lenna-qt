/**
    This file is part of program Lenna
    Copyright (C) 2013-2016 FalseCAM

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

#include "camera.h"
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtWidgets/QProxyStyle>
#include <opencv2/imgproc.hpp>
#include "widget.h"

using namespace lenna;
using namespace lenna::plugin::camera;

Camera::Camera() {
  this->widget = 0;
  this->frames = 0;
  this->position = 0;
}

Camera::~Camera() {}

std::string Camera::getName() { return std::string("camera"); }

std::string Camera::getTitle() { return tr("Camera").toStdString(); }

std::string Camera::getVersion() { return std::string("1.0"); }

std::string Camera::getAuthor() { return std::string("FalseCAM"); }

std::string Camera::getDescription() {
  return tr("Plugin to get images from camera.").toStdString();
}

QIcon Camera::getIcon() {
  QProxyStyle s;
  return s.standardIcon(QStyle::SP_FileIcon);
}

QWidget *Camera::getWidget() {
  if (!widget) {
    widget = new Widget();
  }
  return widget;
}

void Camera::init() {
  frames = widget->getFrames();
  position = 0;
  if (hasNext()) {
    camera = new cv::VideoCapture();
    int deviceID = 0;         // 0 = open default camera
    int apiID = cv::CAP_ANY;  // 0 = autodetect default API
    // open selected camera using selected API
    camera->open(deviceID, apiID);
    cv::Mat *frame = 0;
    while (frame == 0 || frame->empty()) {
      camera->read(*frame);
    }
  }
}

bool Camera::hasNext() { return frames > position; }

std::shared_ptr<LennaImage> Camera::next() {
  if (hasNext()) {
    cv::Mat frame;
    camera->read(frame);
    if (!frame.empty()) {
      std::shared_ptr<LennaImage> img(new LennaImage());
      position++;
      img->setMat(frame);
      img->setName(QString("Frame%1").arg(position));
      img->setAlbum("Camera");
      if (!hasNext()) {
        camera->release();
      }
      return img;
    }
  }
  return 0;
}

int Camera::getProgress() {
  int progress = 0;
  if (hasNext()) progress = 100 * position / frames;
  return progress;
}

std::shared_ptr<plugin::Plugin> Camera::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Camera());
  plugin->setUID(uid);
  return plugin;
}
