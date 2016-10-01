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

#include "plugins/pluginsconfigdialog.h"

#include "plugins/pcpluginwidget.h"
#include "plugins/pluginloader.h"
#include "ui_pluginsconfigdialog.h"

#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QWidget>

using namespace lenna::plugin;

PluginsConfigDialog::PluginsConfigDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::PluginsConfigDialog) {
  ui->setupUi(this);
  loadInputPlugins();
  loadEditPlugins();
  loadOutputPlugins();

  loadActiveInputPlugins();
  loadActiveEditPlugins();
  loadActiveOutputPlugins();

  connect(this, SIGNAL(finished(int)), this, SLOT(orderInputPlugins()));
  connect(this, SIGNAL(finished(int)), this, SLOT(orderEditPlugins()));
  connect(this, SIGNAL(finished(int)), this, SLOT(orderOutputPlugins()));
}

PluginsConfigDialog::~PluginsConfigDialog() { delete ui; }

void PluginsConfigDialog::loadInputPlugins() {
  ui->inputPluginsListWidget->clear();
  foreach (std::shared_ptr<InputPlugin> plugin,
           PluginLoader::getInstance().getInputPlugins()) {
    PCPluginWidget *widget = new PCPluginWidget(plugin);
    connect(widget, SIGNAL(pluginActivated(QString)), this,
            SLOT(on_plugin_activated(QString)));
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 150));
    ui->inputPluginsListWidget->addItem(item);
    ui->inputPluginsListWidget->setItemWidget(item, widget);
  }
}

void PluginsConfigDialog::orderInputPlugins() {
  for (int i = 0; i < ui->inputPluginsListWidget->count(); i++) {
    PCPluginWidget *widget =
        (PCPluginWidget *)ui->inputPluginsListWidget->itemWidget(
            ui->inputPluginsListWidget->item(i));
    std::shared_ptr<InputPlugin> plugin =
        std::static_pointer_cast<InputPlugin>(widget->getPlugin());
    PluginLoader::getInstance().moveInputPlugin(plugin, i);
  }
}

void PluginsConfigDialog::loadEditPlugins() {
  ui->editPluginsListWidget->clear();
  foreach (std::shared_ptr<EditPlugin> plugin,
           PluginLoader::getInstance().getEditPlugins()) {
    PCPluginWidget *widget = new PCPluginWidget(plugin);
    connect(widget, SIGNAL(pluginActivated(QString)), this,
            SLOT(on_plugin_activated(QString)));
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 150));
    ui->editPluginsListWidget->addItem(item);
    ui->editPluginsListWidget->setItemWidget(item, widget);
  }
}

void PluginsConfigDialog::orderEditPlugins() {
  for (int i = 0; i < ui->editPluginsListWidget->count(); i++) {
    PCPluginWidget *widget =
        (PCPluginWidget *)ui->editPluginsListWidget->itemWidget(
            ui->editPluginsListWidget->item(i));
    std::shared_ptr<EditPlugin> plugin =
        std::static_pointer_cast<EditPlugin>(widget->getPlugin());
    PluginLoader::getInstance().moveEditPlugin(plugin, i);
  }
}

void PluginsConfigDialog::loadOutputPlugins() {
  ui->outputPluginsListWidget->clear();
  foreach (std::shared_ptr<OutputPlugin> plugin,
           PluginLoader::getInstance().getOutputPlugins()) {
    PCPluginWidget *widget = new PCPluginWidget(plugin);
    connect(widget, SIGNAL(pluginActivated(QString)), this,
            SLOT(on_plugin_activated(QString)));
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 150));
    ui->outputPluginsListWidget->addItem(item);
    ui->outputPluginsListWidget->setItemWidget(item, widget);
  }
}

void PluginsConfigDialog::loadActiveInputPlugins() {
  ui->activeInputPluginsList->clear();
  for (std::shared_ptr<Plugin> plugin :
       PluginLoader::getInstance().getActiveInputPlugins()) {
    ui->activeInputPluginsList->addItem(plugin->getName());
  }
}

void PluginsConfigDialog::loadActiveEditPlugins() {
  ui->activeEditPluginsList->clear();
  for (std::shared_ptr<Plugin> plugin :
       PluginLoader::getInstance().getActiveEditPlugins()) {
    ui->activeEditPluginsList->addItem(plugin->getName());
  }
}

void PluginsConfigDialog::loadActiveOutputPlugins() {
  ui->activeOutputPluginsList->clear();
  for (std::shared_ptr<Plugin> plugin :
       PluginLoader::getInstance().getActiveOutputPlugins()) {
    ui->activeOutputPluginsList->addItem(plugin->getName());
  }
}

void PluginsConfigDialog::on_plugin_activated(QString uid) {
  loadActiveInputPlugins();
  loadActiveEditPlugins();
  loadActiveOutputPlugins();
}

void PluginsConfigDialog::orderOutputPlugins() {
  for (int i = 0; i < ui->outputPluginsListWidget->count(); i++) {
    PCPluginWidget *widget =
        (PCPluginWidget *)ui->outputPluginsListWidget->itemWidget(
            ui->outputPluginsListWidget->item(i));
    std::shared_ptr<OutputPlugin> plugin =
        std::static_pointer_cast<OutputPlugin>(widget->getPlugin());
    PluginLoader::getInstance().moveOutputPlugin(plugin, i);
  }
}

void PluginsConfigDialog::on_pushButton_clicked() { this->accept(); }

void PluginsConfigDialog::on_inputUpButton_clicked() {
  int currentRow = ui->activeInputPluginsList->currentRow();
  if (currentRow > 0) {
    std::shared_ptr<InputPlugin> plugin = std::static_pointer_cast<InputPlugin>(
        PluginLoader::getInstance().getActivePlugin(PluginLoader::getInstance()
                                                        .getActiveInputPlugins()
                                                        .at(currentRow)
                                                        ->getUID()));
    PluginLoader::getInstance().moveInputPlugin(plugin, currentRow - 1);
    loadActiveInputPlugins();
    ui->activeInputPluginsList->setCurrentRow(currentRow - 1);
  }
}
void PluginsConfigDialog::on_inputDownButton_clicked() {
  int currentRow = ui->activeInputPluginsList->currentRow();
  int count = ui->activeInputPluginsList->count();
  if (currentRow >= 0 && currentRow < count - 1) {
    std::shared_ptr<InputPlugin> plugin = std::static_pointer_cast<InputPlugin>(
        PluginLoader::getInstance().getActivePlugin(PluginLoader::getInstance()
                                                        .getActiveInputPlugins()
                                                        .at(currentRow)
                                                        ->getUID()));
    PluginLoader::getInstance().moveInputPlugin(plugin, currentRow + 1);
    loadActiveInputPlugins();
    ui->activeInputPluginsList->setCurrentRow(currentRow + 1);
  }
}
void PluginsConfigDialog::on_editUpButton_clicked() {
  int currentRow = ui->activeEditPluginsList->currentRow();
  if (currentRow > 0) {
    std::shared_ptr<EditPlugin> plugin = std::static_pointer_cast<EditPlugin>(
        PluginLoader::getInstance().getActivePlugin(PluginLoader::getInstance()
                                                        .getActiveEditPlugins()
                                                        .at(currentRow)
                                                        ->getUID()));
    PluginLoader::getInstance().moveEditPlugin(plugin, currentRow - 1);
    loadActiveEditPlugins();
    ui->activeEditPluginsList->setCurrentRow(currentRow - 1);
  }
}

void PluginsConfigDialog::on_editDownButton_clicked() {
  int currentRow = ui->activeEditPluginsList->currentRow();
  int count = ui->activeEditPluginsList->count();
  if (currentRow >= 0 && currentRow < count - 1) {
    std::shared_ptr<EditPlugin> plugin = std::static_pointer_cast<EditPlugin>(
        PluginLoader::getInstance().getActivePlugin(PluginLoader::getInstance()
                                                        .getActiveEditPlugins()
                                                        .at(currentRow)
                                                        ->getUID()));
    PluginLoader::getInstance().moveEditPlugin(plugin, currentRow + 1);
    loadActiveEditPlugins();
    ui->activeEditPluginsList->setCurrentRow(currentRow + 1);
  }
}

void PluginsConfigDialog::on_outputUpButton_clicked() {
  int currentRow = ui->activeOutputPluginsList->currentRow();
  if (currentRow > 0) {
    std::shared_ptr<OutputPlugin> plugin =
        std::static_pointer_cast<OutputPlugin>(
            PluginLoader::getInstance().getActivePlugin(
                PluginLoader::getInstance()
                    .getActiveOutputPlugins()
                    .at(currentRow)
                    ->getUID()));
    PluginLoader::getInstance().moveOutputPlugin(plugin, currentRow - 1);
    loadActiveOutputPlugins();
    ui->activeOutputPluginsList->setCurrentRow(currentRow - 1);
  }
}

void PluginsConfigDialog::on_outputDownButton_clicked() {
  int currentRow = ui->activeOutputPluginsList->currentRow();
  int count = ui->activeOutputPluginsList->count();
  if (currentRow >= 0 && currentRow < count - 1) {
    std::shared_ptr<OutputPlugin> plugin =
        std::static_pointer_cast<OutputPlugin>(
            PluginLoader::getInstance().getActivePlugin(
                PluginLoader::getInstance()
                    .getActiveOutputPlugins()
                    .at(currentRow)
                    ->getUID()));
    PluginLoader::getInstance().moveOutputPlugin(plugin, currentRow + 1);
    loadActiveOutputPlugins();
    ui->activeOutputPluginsList->setCurrentRow(currentRow + 1);
  }
}
