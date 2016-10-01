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

#ifndef PLUGIN_H
#define PLUGIN_H
#include <QtCore/QObject>
#include <QtCore/QUuid>
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>
#include <memory>

namespace lenna {
namespace plugin {

class Plugin : public QObject {
 public:
  virtual QString getName() { return QString("unknown"); }
  virtual QString getTitle() = 0;
  virtual QString getVersion() = 0;
  virtual QString getAuthor() = 0;
  virtual QString getDescription() = 0;
  virtual QIcon getIcon() = 0;
  virtual QWidget* getWidget() = 0;

  virtual std::shared_ptr<Plugin> getInstance(QString uid) = 0;

  virtual QString getUID() { return this->id.toString(); }
  virtual void setUID(QString uid) { this->id = QUuid(uid); }

 private:
  QUuid id;
};
}
}

#endif  // PLUGIN_H
