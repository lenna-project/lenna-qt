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

#include "camera.h"
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtWidgets/QProxyStyle>
#include "widget.h"

using namespace lenna;
using namespace lenna::plugin::camera;

Camera::Camera() {
  this->widget = 0;
  this->frames = 0;
  this->position = 0;
}

Camera::~Camera() {}

QString Camera::getName() { return QString("camera"); }

QString Camera::getTitle() { return QString(tr("Camera")); }

QString Camera::getVersion() { return QString("1.0"); }

QString Camera::getAuthor() { return QString("FalseCAM"); }

QString Camera::getDescription() {
  return QString(tr("Plugin to get images from camera."));
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
    camera = cvCaptureFromCAM(widget->selectedDevice());
    cv::Mat *frame = 0;
    while (frame == 0 || frame->empty()) {
      frame = new cv::Mat(cv::cvarrToMat(cvQueryFrame(camera), true));
    }
  }
}

bool Camera::hasNext() { return frames > position; }

std::shared_ptr<LennaImage> Camera::next() {
  if (hasNext()) {
    cv::Mat frame = cv::cvarrToMat(cvQueryFrame(camera), true);
    if (!frame.empty()) {
      std::shared_ptr<LennaImage> img(new LennaImage());
      position++;
      img->setMat(frame);
      img->setName(QString("Frame%1").arg(position));
      img->setAlbum("Camera");
      if (!hasNext()) {
        cvReleaseCapture(&camera);
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
