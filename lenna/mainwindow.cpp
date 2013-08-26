#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lenna.h"
#include "splashscreen.h"
#include "plugins/pluginsconfigdialog.h"
#include "plugins/pluginloader.h"
#include "aboutdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    SplashScreen splash(this);
    splash.show();
    splash.setMessage("Starting " + QCoreApplication::applicationName());
    ui->setupUi(this);
    splash.setMessage("Loading config ...");
    this->setWindowTitle(Lenna::applicationName() + " " + Lenna::applicationVersion());
    splash.setMessage("Loading Plugins ...");
    loadInputPluginWidgets();
    loadEditPluginWidgets();
    loadOutputPluginWidgets();
    splash.finish(this);
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

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_actionPlugins_triggered()
{
    PluginsConfigDialog dialog;
    dialog.exec();
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
