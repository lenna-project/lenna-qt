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
#include <QDesktopServices>
#include "mainwindow.h"
#include <lenna/lenna.h>
#include <lenna/logger.h>
#include "aboutdialog.h"
#include "loggerdialog.h"
#include "plugins/pluginloader.h"
#include "plugins/pluginsconfigdialog.h"
#include "splashscreen.h"
#include "tipsdialog.h"
#include "ui_mainwindow.h"

using namespace lenna;
using namespace lenna::plugin;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  startStopButtonIsStart = true;
  SplashScreen splash(this);
  qDebug("showing Splashscreen");
  splash.show();
  splash.setMessage("Starting " + QCoreApplication::applicationName());
  ui->setupUi(this);
  splash.setMessage("Loading config ...");
  this->setWindowTitle(Lenna::applicationName() + " " +
                       Lenna::applicationVersion());
  splash.setMessage("Loading Plugins ...");
  qDebug("loading Input Plugin Widgets");
  loadInputPluginWidgets();
  qDebug("loading Edit Plugin Widgets");
  loadEditPluginWidgets();
  qDebug("loading Output Plugin Widgets");
  loadOutputPluginWidgets();
  process = new Process(this);
  initWorker();
  initToolbar();
  // connect infoLineEdit to Logger info signal
  connect(Logger::instance(), SIGNAL(newInfo(QString)), ui->infoLineEdit,
          SLOT(setText(QString)));
  splash.finish(this);
  qDebug("showing Tips");
  TipsDialog tips;
  tips.showOnStartup();
}

MainWindow::~MainWindow() {
  delete ui;
  PluginLoader::destroyInstance();
}

void MainWindow::initWorker() {
  worker = new Worker();

  connect(worker, SIGNAL(process(int)), ui->progressBar, SLOT(setValue(int)));
  connect(worker, SIGNAL(finished()), this, SLOT(stopProcess()));
  worker->moveToThread(process);
  connect(process, SIGNAL(started()), worker, SLOT(process()));
}

void MainWindow::on_actionQuit_triggered() { this->close(); }

void lenna::MainWindow::on_actionLogger_triggered() {
  LoggerDialog loggerDialog;
  loggerDialog.exec();
}

void lenna::MainWindow::on_actionTips_triggered() {
  TipsDialog tips;
  tips.exec();
}

void MainWindow::on_actionAbout_triggered() {
  AboutDialog dialog;
  dialog.exec();
}

void MainWindow::on_actionPlugins_triggered() {
  PluginsConfigDialog dialog;
  dialog.exec();
  loadInputPluginWidgets();
  loadEditPluginWidgets();
  loadOutputPluginWidgets();
}

void MainWindow::loadInputPluginWidgets() {
  ui->inputTabWidget->clear();
  for (std::shared_ptr<InputPlugin> plugin :
       PluginLoader::getInstance().getActiveInputPlugins()) {
    assert(plugin);
    ui->inputTabWidget->addTab(plugin->getWidget(), plugin->getIcon(),
                               QString::fromStdString(plugin->getTitle()));
  }
}

void MainWindow::loadEditPluginWidgets() {
  ui->editTabWidget->clear();
  for (std::shared_ptr<EditPlugin> plugin :
       PluginLoader::getInstance().getActiveEditPlugins()) {
    assert(plugin);
    ui->editTabWidget->addTab(plugin->getWidget(), plugin->getIcon(),
                              QString::fromStdString(plugin->getTitle()));
  }
}

void MainWindow::loadOutputPluginWidgets() {
  ui->outputTabWidget->clear();
  for (std::shared_ptr<OutputPlugin> plugin :
       PluginLoader::getInstance().getActiveOutputPlugins()) {
    ui->outputTabWidget->addTab(plugin->getWidget(), plugin->getIcon(),
                                QString::fromStdString(plugin->getTitle()));
  }
}

void MainWindow::on_startStopButton_clicked() {
  if (startStopButtonIsStart) {
    startProcess();
  } else {
    stopProcess();
  }
}

void MainWindow::startProcess() {
  ui->startStopButton->setText(tr("Stop"));
  startStopButtonIsStart = false;
  process->start();
}

void MainWindow::stopProcess() {
  ui->startStopButton->setText(tr("Start"));
  worker->stop();
  startStopButtonIsStart = true;
}

void lenna::MainWindow::on_inputTabWidget_tabCloseRequested(int index) {
  int counter = -1;
  for (std::shared_ptr<InputPlugin> plugin :
       PluginLoader::getInstance().getActiveInputPlugins()) {
    counter++;
    if (counter == index) {
      PluginLoader::getInstance().deactivatePlugin(plugin);
      break;
    }
  }
  loadInputPluginWidgets();
}

void lenna::MainWindow::on_editTabWidget_tabCloseRequested(int index) {
  int counter = -1;
  for (std::shared_ptr<EditPlugin> plugin :
       PluginLoader::getInstance().getActiveEditPlugins()) {
    counter++;
    if (counter == index) {
      PluginLoader::getInstance().deactivatePlugin(plugin);
      break;
    }
  }
  loadEditPluginWidgets();
}

void lenna::MainWindow::on_outputTabWidget_tabCloseRequested(int index) {
  int counter = -1;
  for (std::shared_ptr<OutputPlugin> plugin :
       PluginLoader::getInstance().getActiveOutputPlugins()) {
    counter++;
    if (counter == index) {
      PluginLoader::getInstance().deactivatePlugin(plugin);
    }
  }
  loadOutputPluginWidgets();
}

void lenna::MainWindow::on_actionWebApp_triggered()
{
    QDesktopServices::openUrl(QUrl("https://lenna.app", QUrl::TolerantMode));
}

void lenna::MainWindow::initToolbar(){
    QAction * webAppAction = ui->mainToolBar->addAction(QIcon(":/logo/lenna_logo"), "WebApp", this, SLOT(on_actionWebApp_triggered()));
    QAction * pluginsAction = ui->mainToolBar->addAction(QIcon(":/lenna/plugins.png"), "Plugins", this, SLOT(on_actionPlugins_triggered()));
}
