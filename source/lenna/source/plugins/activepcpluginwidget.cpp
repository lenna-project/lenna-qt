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

#include "plugins/activepcpluginwidget.h"
#include "plugins/pluginloader.h"
#include "ui_activepcpluginwidget.h"

#include <QtGui/QPixmap>

using namespace lenna::plugin;

ActivePCPluginWidget::ActivePCPluginWidget(std::shared_ptr<Plugin> plugin)
    : ui(new Ui::ActivePCPluginWidget) {
  this->plugin = plugin;
  ui->setupUi(this);
  ui->titleLabel->setText(QString::fromStdString(plugin->getTitle()));
  ui->titleLabel->setToolTip(QString::fromStdString(plugin->getTitle()));
  ui->iconLabel->setPixmap(plugin->getIcon().pixmap(16, 16));
}

ActivePCPluginWidget::~ActivePCPluginWidget() { delete ui; }

std::shared_ptr<Plugin> ActivePCPluginWidget::getPlugin() {
  return this->plugin;
}

void ActivePCPluginWidget::on_checkBox_stateChanged(int arg1) {
  PluginLoader::getInstance().deactivatePlugin(plugin);
  emit pluginDeactivated(plugin->getUID());
}
