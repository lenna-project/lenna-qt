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

#include "rename.h"
#include "widget.h"

#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin::rename;

Rename::Rename() { widget = 0; }

Rename::~Rename() {}

std::string Rename::getName() { return std::string("rename"); }

std::string Rename::getTitle() { return tr("Rename").toStdString(); }

std::string Rename::getVersion() { return std::string("0.1"); }

std::string Rename::getAuthor() { return std::string("FalseCAM"); }

std::string Rename::getDescription() {
  return tr("Plugin to rename image files").toStdString();
}

QIcon Rename::getIcon() { return QIcon(":/plugins/rename/rename"); }

QWidget *Rename::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

std::shared_ptr<plugin::Plugin> Rename::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Rename());
  plugin->setUID(uid);
  return plugin;
}

void Rename::edit(std::shared_ptr<LennaImage> img) {
  getWidget();
  if (widget->isRename()) {
    QString name = widget->prefix();
    if (widget->isNewName()) {
      name.append(widget->newName());
    } else {
      name.append(img->getName());
    }
    name.append(widget->suffix());
    img->setName(name);
  }
}
