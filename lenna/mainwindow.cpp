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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lenna.h"
#include "splashscreen.h"
#include "plugins/pluginsconfigdialog.h"
#include "plugins/pluginloader.h"
#include "aboutdialog.h"
#include "loggerdialog.h"
#include "tipsdialog.h"

using namespace lenna;
using namespace lenna::plugin;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    SplashScreen splash(this);
    qDebug("showing Splashscreen");
    splash.show();
    splash.setMessage("Starting " + QCoreApplication::applicationName());
    ui->setupUi(this);
    splash.setMessage("Loading config ...");
    this->setWindowTitle(Lenna::applicationName() + " " + Lenna::applicationVersion());
    splash.setMessage("Loading Plugins ...");
    qDebug("loading Input Plugin Widgets");
    loadInputPluginWidgets();
    qDebug("loading Edit Plugin Widgets");
    loadEditPluginWidgets();
    qDebug("loading Output Plugin Widgets");
    loadOutputPluginWidgets();
    process = new Process();
    connect(process, SIGNAL(process(int)), ui->progressBar, SLOT(setValue(int)));
    splash.finish(this);
    qDebug("showing Tips");
    TipsDialog tips;
    tips.showOnStartup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    Lenna::destroy();
    this->close();
}

void lenna::MainWindow::on_actionLogger_triggered()
{
    LoggerDialog loggerDialog;
    loggerDialog.exec();
}

void lenna::MainWindow::on_actionTips_triggered()
{
    TipsDialog tips;
    tips.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_actionPlugins_triggered()
{
    PluginsConfigDialog dialog;
    dialog.exec();
    loadInputPluginWidgets();
    loadEditPluginWidgets();
    loadOutputPluginWidgets();
}


void MainWindow::loadInputPluginWidgets(){
    ui->inputTabWidget->clear();
    foreach (InputPlugin *plugin, PluginLoader::getInstance().getInputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            ui->inputTabWidget->addTab(plugin->getWidget(), plugin->getIcon(), plugin->getTitle());
        }
    }
}

void MainWindow::loadEditPluginWidgets(){
    ui->editTabWidget->clear();
    foreach (EditPlugin *plugin, PluginLoader::getInstance().getEditPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            ui->editTabWidget->addTab(plugin->getWidget(), plugin->getIcon(), plugin->getTitle());
        }
    }
}

void MainWindow::loadOutputPluginWidgets(){
    ui->outputTabWidget->clear();
    foreach (OutputPlugin *plugin, PluginLoader::getInstance().getOutputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            ui->outputTabWidget->addTab(plugin->getWidget(), plugin->getIcon(), plugin->getTitle());
        }
    }
}

void MainWindow::on_startStopButton_clicked()
{
    process->start();
}

void lenna::MainWindow::on_inputTabWidget_tabCloseRequested(int index)
{
    int counter = -1;
    foreach (InputPlugin *plugin, PluginLoader::getInstance().getInputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            counter++;
            if(counter == index){
                PluginLoader::getInstance().deactivatePlugin(plugin);
            }
        }
    }
    loadInputPluginWidgets();
}

void lenna::MainWindow::on_editTabWidget_tabCloseRequested(int index)
{
    int counter = -1;
    foreach (EditPlugin *plugin, PluginLoader::getInstance().getEditPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            counter++;
            if(counter == index){
                PluginLoader::getInstance().deactivatePlugin(plugin);
            }
        }
    }
    loadEditPluginWidgets();
}

void lenna::MainWindow::on_outputTabWidget_tabCloseRequested(int index)
{
    int counter = -1;
    foreach (OutputPlugin *plugin, PluginLoader::getInstance().getOutputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            counter++;
            if(counter == index){
                PluginLoader::getInstance().deactivatePlugin(plugin);
            }
        }
    }
    loadOutputPluginWidgets();
}




