/**
    This file is part of program Lenna
    Copyright (C) 2013-2016  FalseCAM

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

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <lenna/plugins/editplugin.h>
#include "widget.h"

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtGui/QIcon>

namespace lenna {
namespace plugin {
namespace timestamp {

class Timestamp : public EditPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "lenna.blur" FILE "timestamp.json")
  Q_INTERFACES(lenna::plugin::EditPlugin)

 public:
  Timestamp();
  ~Timestamp();
  std::string getName();
  std::string getTitle();
  std::string getVersion();
  std::string getAuthor();
  std::string getDescription();
  QIcon getIcon();
  QWidget *getWidget();

  void edit(std::shared_ptr<LennaImage> image);

  std::shared_ptr<Plugin> getInstance(QString uid);

 private:
  Widget *widget;
};
}  // namespace timestamp
}  // namespace plugin
}  // namespace lenna

#endif  // TIMESTAMP_H
