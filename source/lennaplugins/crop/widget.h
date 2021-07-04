/**
    This file is part of program Lenna
    Copyright (C) 2016  FalseCAM

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

#ifndef WIDGET_H
#define WIDGET_H

#include <mutex>
#include <vector>

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QtWidgets/QWidget>
#include <opencv2/core/core.hpp>

namespace Ui {
class Widget;
}

namespace lenna {
namespace plugin {
namespace crop {

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

  void setImage(cv::Mat image);
  void updateImage();

  bool isActionDone();
  bool isDoCrop();

  std::vector<cv::Point2f> getPoints();

 private slots:

  void on_cropPushButton_clicked();

  void on_cancelButton_clicked();

 private:
  Ui::Widget *ui;
  void initScene();
  void initCircles();

  void loadState();
  void saveState();

  void crop(QImage *image);

  std::mutex actionDoneMutex;
  bool actionDone = false;
  bool doCrop = false;

  cv::Mat image;
  QGraphicsScene *scene;
  QGraphicsEllipseItem *circles[4];

 protected:
  void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
};
}  // namespace crop
}  // namespace plugin
}  // namespace lenna

#endif  // WIDGET_H
