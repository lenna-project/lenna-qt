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

#ifndef ACTIVEPCPLUGINWIDGET_H
#define ACTIVEPCPLUGINWIDGET_H

#include <lenna/plugins/plugin.h>

#include <QtWidgets/QWidget>

namespace Ui {
class ActivePCPluginWidget;
}

namespace lenna {
namespace plugin {

class ActivePCPluginWidget : public QWidget {
  Q_OBJECT

 public:
  ActivePCPluginWidget(std::shared_ptr<Plugin> plugin);
  ~ActivePCPluginWidget();
  std::shared_ptr<Plugin> getPlugin();

 signals:
  void pluginDeactivated(QString uid);

 private:
  Ui::ActivePCPluginWidget *ui;
  std::shared_ptr<Plugin> plugin;

 private slots:
  void on_checkBox_stateChanged(int arg1);
};
}  // namespace plugin
}  // namespace lenna

#endif  // ACTIVEPCPLUGINWIDGET_H
