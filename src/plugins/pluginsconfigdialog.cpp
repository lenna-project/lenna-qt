/**
    This file is part of program Lenna
    Copyright (C) 2013  FalseCAM

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

#include "pluginsconfigdialog.h"
#include "ui_pluginsconfigdialog.h"
#include "pluginloader.h"
#include "pcpluginwidget.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidgetItem>

using namespace lenna::plugin;

PluginsConfigDialog::PluginsConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsConfigDialog)
{
    ui->setupUi(this);
    loadInputPlugins();
    loadEditPlugins();
    loadOutputPlugins();

    connect(this, SIGNAL(finished(int)), this, SLOT(orderInputPlugins()));
    connect(this, SIGNAL(finished(int)), this, SLOT(orderEditPlugins()));
    connect(this, SIGNAL(finished(int)), this, SLOT(orderOutputPlugins()));
}

PluginsConfigDialog::~PluginsConfigDialog()
{
    delete ui;
}

void PluginsConfigDialog::loadInputPlugins(){
    ui->inputPluginsListWidget->clear();
    foreach(InputPlugin *plugin, PluginLoader::getInstance().getInputPlugins()){
        PCPluginWidget *widget = new PCPluginWidget(plugin);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,150));
        ui->inputPluginsListWidget->addItem(item);
        ui->inputPluginsListWidget->setItemWidget(item, widget);
    }
}

void PluginsConfigDialog::orderInputPlugins(){
    for(int i = 0; i< ui->inputPluginsListWidget->count(); i++){
        PCPluginWidget *widget = (PCPluginWidget*)ui->inputPluginsListWidget->itemWidget(ui->inputPluginsListWidget->item(i));
        InputPlugin *plugin = (InputPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveInputPlugin(plugin, i);
    }
}

void PluginsConfigDialog::loadEditPlugins(){
    ui->editPluginsListWidget->clear();
    foreach(EditPlugin *plugin, PluginLoader::getInstance().getEditPlugins()){
        PCPluginWidget *widget = new PCPluginWidget(plugin);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,150));
        ui->editPluginsListWidget->addItem(item);
        ui->editPluginsListWidget->setItemWidget(item, widget);
    }
}

void PluginsConfigDialog::orderEditPlugins(){
    for(int i = 0; i< ui->editPluginsListWidget->count(); i++){
        PCPluginWidget *widget = (PCPluginWidget*)ui->editPluginsListWidget->itemWidget(ui->editPluginsListWidget->item(i));
        EditPlugin *plugin = (EditPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveEditPlugin(plugin, i);
    }
}

void PluginsConfigDialog::loadOutputPlugins(){
    ui->outputPluginsListWidget->clear();
    foreach(OutputPlugin *plugin, PluginLoader::getInstance().getOutputPlugins()){
        PCPluginWidget *widget = new PCPluginWidget(plugin);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,150));
        ui->outputPluginsListWidget->addItem(item);
        ui->outputPluginsListWidget->setItemWidget(item, widget);
    }
}

void PluginsConfigDialog::orderOutputPlugins(){
    for(int i = 0; i< ui->outputPluginsListWidget->count(); i++){
        PCPluginWidget *widget = (PCPluginWidget*)ui->outputPluginsListWidget->itemWidget(ui->outputPluginsListWidget->item(i));
        OutputPlugin *plugin = (OutputPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveOutputPlugin(plugin, i);
    }
}

void PluginsConfigDialog::on_pushButton_clicked()
{
    this->accept();
}

void PluginsConfigDialog::on_inputUpButton_clicked()
{
    int currentRow = ui->inputPluginsListWidget->currentRow();
    if(currentRow > 0){
        PCPluginWidget *widget = (PCPluginWidget*)ui->inputPluginsListWidget->itemWidget(ui->inputPluginsListWidget->item(currentRow));
        InputPlugin *plugin = (InputPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveInputPlugin(plugin, currentRow - 1);
        loadInputPlugins();
        ui->inputPluginsListWidget->setCurrentRow(currentRow - 1);
    }
}
void PluginsConfigDialog::on_inputDownButton_clicked()
{
    int currentRow = ui->inputPluginsListWidget->currentRow();
    int count = ui->inputPluginsListWidget->count();
    if( currentRow >= 0 && currentRow < count - 1){
        PCPluginWidget *widget = (PCPluginWidget*)ui->inputPluginsListWidget->itemWidget(ui->inputPluginsListWidget->item(currentRow));
        InputPlugin *plugin = (InputPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveInputPlugin(plugin, currentRow + 1);
        loadInputPlugins();
        ui->inputPluginsListWidget->setCurrentRow(currentRow + 1);
    }
}
void PluginsConfigDialog::on_editUpButton_clicked()
{
    int currentRow = ui->editPluginsListWidget->currentRow();
    if(currentRow > 0){
        PCPluginWidget *widget = (PCPluginWidget*)ui->editPluginsListWidget->itemWidget(ui->editPluginsListWidget->item(currentRow));
        EditPlugin *plugin = (EditPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveEditPlugin(plugin, currentRow - 1);
        loadEditPlugins();
        ui->editPluginsListWidget->setCurrentRow(currentRow - 1);
    }
}

void PluginsConfigDialog::on_editDownButton_clicked()
{
    int currentRow = ui->editPluginsListWidget->currentRow();
    int count = ui->editPluginsListWidget->count();
    if( currentRow >= 0 && currentRow < count - 1){
        PCPluginWidget *widget = (PCPluginWidget*)ui->editPluginsListWidget->itemWidget(ui->editPluginsListWidget->item(currentRow));
        EditPlugin *plugin = (EditPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveEditPlugin(plugin, currentRow + 1);
        loadEditPlugins();
        ui->editPluginsListWidget->setCurrentRow(currentRow + 1);
    }
}



void PluginsConfigDialog::on_outputUpButton_clicked()
{
    int currentRow = ui->outputPluginsListWidget->currentRow();
    if(currentRow > 0){
        PCPluginWidget *widget = (PCPluginWidget*)ui->outputPluginsListWidget->itemWidget(ui->outputPluginsListWidget->item(currentRow));
        OutputPlugin *plugin = (OutputPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveOutputPlugin(plugin, currentRow - 1);
        loadOutputPlugins();
        ui->outputPluginsListWidget->setCurrentRow(currentRow - 1);
    }
}

void PluginsConfigDialog::on_outputDownButton_clicked()
{
    int currentRow = ui->outputPluginsListWidget->currentRow();
    int count = ui->outputPluginsListWidget->count();
    if( currentRow >= 0 && currentRow < count - 1){
        PCPluginWidget *widget = (PCPluginWidget*)ui->outputPluginsListWidget->itemWidget(ui->outputPluginsListWidget->item(currentRow));
        OutputPlugin *plugin = (OutputPlugin *)widget->getPlugin();
        PluginLoader::getInstance().moveOutputPlugin(plugin, currentRow + 1);
        loadOutputPlugins();
        ui->outputPluginsListWidget->setCurrentRow(currentRow + 1);
    }
}
