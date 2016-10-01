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

#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QIcon>
#include <QObject>
#include <QtPlugin>
#include "lenna/plugins/outputplugin.h"
#include "widget.h"

namespace lenna {
namespace plugin {

class SaveFile : public OutputPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "lenna.savefile" FILE "savefile.json")
  Q_INTERFACES(lenna::plugin::OutputPlugin)

 public:
  SaveFile();
  ~SaveFile();
  QString getName();
  QString getTitle();
  QString getVersion();
  QString getAuthor();
  QString getDescription();
  QIcon getIcon();
  QWidget *getWidget();

  std::shared_ptr<Plugin> getInstance(QString uid);

  void out(std::shared_ptr<LennaImage> image);
  void finnish();

 private:
  Widget *widget;
};
}
}

#endif  // SAVEFILE_H
