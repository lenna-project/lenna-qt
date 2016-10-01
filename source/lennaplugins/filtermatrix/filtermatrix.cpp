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

#include "filtermatrix.h"
#include "widget.h"

#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::filtermatrix;

FilterMatrix::FilterMatrix() { widget = 0; }

FilterMatrix::~FilterMatrix() {
  if (this->widget) delete this->widget;
}

QString FilterMatrix::getName() { return QString("filtermatrix"); }

QString FilterMatrix::getTitle() { return QString(tr("FilterMatrix")); }

QString FilterMatrix::getVersion() { return QString("0.1"); }

QString FilterMatrix::getAuthor() { return QString("FalseCAM"); }

QString FilterMatrix::getDescription() {
  return QString(tr("Plugin to filter images with custom matrix."));
}

QIcon FilterMatrix::getIcon() {
  return QIcon(":/plugins/filtermatrix/filtermatrix");
}

QWidget *FilterMatrix::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

void FilterMatrix::edit(std::shared_ptr<LennaImage> img) {
  if (widget->isFilter()) {
    cv::filter2D(img->getImage(), img->getImage(), -1, widget->getFilter());
    img->getImage() = img->getImage() * 255;  // TODO why * 255?
  }
}

std::shared_ptr<Plugin> FilterMatrix::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new FilterMatrix());
  plugin->setUID(uid);
  return plugin;
}
