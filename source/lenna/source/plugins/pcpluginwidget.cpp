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

#include "plugins/pcpluginwidget.h"
#include "plugins/pluginloader.h"
#include "ui_pcpluginwidget.h"

#include <QtGui/QPixmap>

using namespace lenna::plugin;

PCPluginWidget::PCPluginWidget(std::shared_ptr<Plugin> plugin)
    : ui(new Ui::PCPluginWidget) {
  this->plugin = plugin;
  ui->setupUi(this);
  ui->nameLabel->setText(plugin->getName());
  ui->nameLabel->setToolTip(plugin->getName() + " " + plugin->getVersion());
  ui->titleLabel->setText(plugin->getTitle());
  ui->titleLabel->setToolTip(plugin->getTitle());
  ui->versionLabel->setText(plugin->getVersion());
  ui->descriptionBrowser->setText(plugin->getDescription());
  ui->iconLabel->setPixmap(plugin->getIcon().pixmap(32, 32));
  ui->authorLabel->setText(plugin->getAuthor());
  // if (PluginLoader::getInstance().isActivatedPlugin(plugin)) {
  // ui->checkBox->setChecked(true);
  //}

  // connect(ui->checkBox, SIGNAL(toggled(bool)), this,
  // SLOT(checkBoxChanged()));
}

PCPluginWidget::~PCPluginWidget() { delete ui; }

void PCPluginWidget::checkBoxChanged() {
  // if (ui->checkBox->isChecked()) {
  //  PluginLoader::getInstance().activatePlugin(plugin);
  //} else {
  //  PluginLoader::getInstance().deactivatePlugin(plugin);
  //}
}

std::shared_ptr<Plugin> PCPluginWidget::getPlugin() { return this->plugin; }

void lenna::plugin::PCPluginWidget::on_addButton_clicked() {
  QString uid = QUuid::createUuid().toString();
  PluginLoader::getInstance().activatePlugin(uid, plugin->getName());
  emit pluginActivated(uid);
}
