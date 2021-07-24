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

#include "timestamp.h"
#include "widget.h"

#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::timestamp;

Timestamp::Timestamp() { widget = 0; }

Timestamp::~Timestamp() {
  if (this->widget) delete this->widget;
}

std::string Timestamp::getName() { return std::string("timestamp"); }

std::string Timestamp::getTitle() { return tr("Timestamp").toStdString(); }

std::string Timestamp::getVersion() { return std::string("0.1"); }

std::string Timestamp::getAuthor() { return std::string("chriamue"); }

std::string Timestamp::getDescription() {
  return tr("Plugin to change timestamps of images").toStdString();
}

QIcon Timestamp::getIcon() { return QIcon(":/plugins/timestamp/timestamp"); }

QWidget *Timestamp::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

void Timestamp::edit(std::shared_ptr<LennaImage> img) {
  std::string time = widget->getTime();
  std::string date = widget->getDate();
  //cv::blur(img->getImage(), img->getImage(), cv::Size(size, size));
}

std::shared_ptr<Plugin> Timestamp::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Timestamp());
  plugin->setUID(uid);
  return plugin;
}
