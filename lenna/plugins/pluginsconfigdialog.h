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

#ifndef PLUGINSCONFIGDIALOG_H
#define PLUGINSCONFIGDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>

namespace Ui {
class PluginsConfigDialog;
}

class PluginsConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PluginsConfigDialog(QWidget *parent = 0);
    ~PluginsConfigDialog();
    
private:
    Ui::PluginsConfigDialog *ui;
    void loadInputPlugins();
    void loadEditPlugins();
    void loadOutputPlugins();

private slots:
    void orderInputPlugins();
    void orderEditPlugins();
    void orderOutputPlugins();
    void on_pushButton_clicked();
    void on_inputUpButton_clicked();
    void on_editUpButton_clicked();
    void on_editDownButton_clicked();
    void on_inputDownButton_clicked();
    void on_outputUpButton_clicked();
    void on_outputDownButton_clicked();
};

#endif // PLUGINSCONFIGDIALOG_H
