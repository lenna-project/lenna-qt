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

#include "widget.h"
#include "crop.h"
#include "ui_widget.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QGraphicsItem>
#include <QtCore/QSettings>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

using namespace lenna::plugin::crop;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  loadState();
  initScene();
  initCircles();
}

Widget::~Widget() {
  saveState();
  delete scene;
  delete ui;
}

void Widget::setImage(cv::Mat image) {
  this->image = image;
  actionDoneMutex.lock();
  this->actionDone = false;
  actionDoneMutex.unlock();
  updateImage();
}

void Widget::updateImage() {
  if (image.cols < 1) return;

  scene->setSceneRect(0, 0, image.cols, image.rows);

  cv::Mat tmp;

  cv::Size size;
  size.width = scene->sceneRect().width();
  size.height = scene->sceneRect().height();

  // cv::resize(image, tmp, size);
  cv::cvtColor(image, tmp, cv::COLOR_BGR2RGB);
  tmp.convertTo(tmp, CV_8U);

  QImage img = QImage((const unsigned char *)(tmp.data), tmp.cols, tmp.rows,
                      tmp.step, QImage::Format_RGB888);

  QPixmap pim = QPixmap::fromImage(img);
  scene->setBackgroundBrush(pim);

  circles[0]->moveBy(0, 0);
  circles[1]->moveBy(0, scene->sceneRect().height() - 60);
  circles[2]->moveBy(scene->sceneRect().width() - 60,
                     scene->sceneRect().height() - 60);
  circles[3]->moveBy(scene->sceneRect().width() - 60, 0);

  ui->graphicsView->fitInView(scene->sceneRect());
  ui->graphicsView->centerOn(scene->sceneRect().x() / 2,
                             scene->sceneRect().y() / 2);
}

bool Widget::isActionDone() {
  bool ret = false;
  actionDoneMutex.lock();
  ret = actionDone;
  actionDoneMutex.unlock();
  return ret;
}

bool Widget::isDoCrop() { return doCrop; }

std::vector<cv::Point2f> Widget::getPoints() {
  std::vector<cv::Point2f> points;
  for (int i = 0; i < 4; ++i) {
    int x = circles[i]->scenePos().x() + 15;
    int y = circles[i]->scenePos().y() + 15;
    points.push_back(cv::Point2f(x * image.cols / scene->sceneRect().width(),
                                 y * image.rows / scene->sceneRect().height()));
  }
  return points;
}

void Widget::loadState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Crop");
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Crop");
}

void Widget::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  updateImage();
}

void lenna::plugin::crop::Widget::on_cropPushButton_clicked() {
  actionDoneMutex.lock();
  this->actionDone = true;
  this->doCrop = true;
  actionDoneMutex.unlock();
}

void lenna::plugin::crop::Widget::on_cancelButton_clicked() {
  actionDoneMutex.lock();
  this->actionDone = true;
  this->doCrop = false;
  actionDoneMutex.unlock();
}

void Widget::initScene() {
  scene = new QGraphicsScene(0, 0, 1000, 1000);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->fitInView(scene->sceneRect());
}

void Widget::initCircles() {
  QPen pen;
  pen.setWidth(5);
  pen.setColor(QColor(Qt::cyan));

  for (int i = 0; i < 4; ++i) {
    circles[i] = scene->addEllipse(0, 0, 30, 30, pen);
    circles[i]->setFlag(QGraphicsItem::ItemIsMovable);
    circles[i]->setFlag(QGraphicsItem::ItemIsSelectable);
  }
}
