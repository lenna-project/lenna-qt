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

#include "resize.h"
#include <QtGui/QPainter>
#include "widget.h"

using namespace lenna;
using namespace lenna::plugin::resize;

Resize::Resize() { widget = 0; }

Resize::~Resize() {}

QString Resize::getName() { return QString("resize"); }

QString Resize::getTitle() { return QString(tr("Resize")); }

QString Resize::getVersion() { return QString("0.1"); }

QString Resize::getAuthor() { return QString("FalseCAM"); }

QString Resize::getDescription() {
  return QString(tr("Plugin to resize images"));
}

QIcon Resize::getIcon() { return QIcon(":/plugins/resize/resize"); }

QWidget *Resize::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

std::shared_ptr<plugin::Plugin> Resize::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Resize());
  plugin->setUID(uid);
  return plugin;
}

void Resize::edit(std::shared_ptr<LennaImage> img) {
  getWidget();
  if (this->widget->resizePercent() || this->widget->resizePixel()) {
    cv::Size size = img->getImage().size();
    if (this->widget->resizePercent()) {
      size.width *= widget->percentWidth() / 100.0;
      size.height *= widget->percentHeight() / 100.0;
    } else if (this->widget->resizePixel()) {
      size.width = widget->pixelWidth();
      size.height = widget->pixelHeight();
    }
    cv::Mat dst;
    cv::resize(img->getImage(), dst, size, 0, 0, cv::INTER_CUBIC);
    img->setMat(dst);
  }
}
