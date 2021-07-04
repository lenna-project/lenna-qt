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

#include "widget.h"
#include "ui_widget.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QMimeData>
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QImageReader>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace lenna::plugin::camera;
using namespace cv;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  listCameras();
}

Widget::~Widget() { delete ui; }

int Widget::getFrames() { return ui->framesSpinBox->value(); }

void Widget::listCameras() {
  for (int device = 0; device < 3; device++) {
    try {
      cv::VideoCapture cap(device);
      if (!cap.isOpened()) return;
      ui->camerasComboBox->addItem(QString("device %1").arg(device));
    } catch (std::exception &e) {
    }
  }
}

int Widget::selectedDevice() { return ui->camerasComboBox->currentIndex(); }

void Widget::on_cameraOnCheckBox_toggled(bool checked) {
  int key;
  cv::VideoCapture camera;
  int deviceID = 0;         // 0 = open default camera
  int apiID = cv::CAP_ANY;  // 0 = autodetect default API
  // open selected camera using selected API
  camera.open(deviceID, apiID);
  Mat frame;
  while (ui->cameraOnCheckBox->isChecked()) {
    camera.read(frame);
    if (!frame.empty()) cv::imshow("Camera", frame);
    key = cv::waitKey(10);
    if (key == 27 /* ESC */) break;
  }
}
