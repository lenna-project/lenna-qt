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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "process.h"
#include "worker.h"

namespace Ui {
class MainWindow;
}

namespace lenna{

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionPlugins_triggered();

    void on_startStopButton_clicked();

    void on_inputTabWidget_tabCloseRequested(int index);

    void on_editTabWidget_tabCloseRequested(int index);

    void on_outputTabWidget_tabCloseRequested(int index);

    void on_actionTips_triggered();

    void on_actionLogger_triggered();

private:
    Ui::MainWindow *ui;
    Process *process;
    Worker *worker;

    void loadInputPluginWidgets();
    void loadEditPluginWidgets();
    void loadOutputPluginWidgets();
    void initWorker();
};

}

#endif // MAINWINDOW_H
