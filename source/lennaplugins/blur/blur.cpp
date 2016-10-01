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

#include "blur.h"
#include "widget.h"

#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::blur;

Blur::Blur() { widget = 0; }

Blur::~Blur() {
  if (this->widget) delete this->widget;
}

QString Blur::getName() { return QString("blur"); }

QString Blur::getTitle() { return QString(tr("Blur")); }

QString Blur::getVersion() { return QString("0.1"); }

QString Blur::getAuthor() { return QString("FalseCAM"); }

QString Blur::getDescription() { return QString(tr("Plugin to blur images")); }

QIcon Blur::getIcon() { return QIcon(":/plugins/blur/blur"); }

QWidget *Blur::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

void Blur::edit(std::shared_ptr<LennaImage> img) {
  int size = widget->getRadius();
  cv::blur(img->getImage(), img->getImage(), cv::Size(size, size));
}

std::shared_ptr<Plugin> Blur::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Blur());
  plugin->setUID(uid);
  return plugin;
}
