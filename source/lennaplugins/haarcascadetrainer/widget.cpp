/**
    This file is part of program Lenna
    Copyright (C) 2016  FalseCAM

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

#include "widget.h"
#include <QDir>
#include <QFileDialog>
#include <QImageWriter>
#include <QSettings>
#include <QListWidget>
#include "ui_widget.h"

using namespace lenna::plugin;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  initFolder();
  loadState();
}

Widget::~Widget() {
  saveState();
  delete ui;
}

void Widget::loadState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("HaarcascadeTrainer");
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("HaarcascadeTrainer");
}

void Widget::initFolder() {
#if defined(Q_OS_WIN)
  ui->folderLineEdit->setText(QDir::homePath() + "/Pictures");
#elif defined(Q_OS_MAC)
  ui->folderLineEdit->setText(QDir::homePath());
#elif defined(Q_OS_LINUX)
  ui->folderLineEdit->setText(QDir::homePath());
#else
  ui->folderLineEdit->setText(QDir::homePath());
#endif
}

void Widget::on_selectFolderPushButton_clicked() {
  QString folder = ui->folderLineEdit->text();
  folder = QFileDialog::getExistingDirectory(
      this, tr("Please select directory where images will saved to."), folder);
  if (!folder.isEmpty() && QDir(folder).exists())
    ui->folderLineEdit->setText(folder);
}

QString Widget::getFolder() { return ui->folderLineEdit->text(); }

QStringList Widget::getPositiveAlbums()
{
    QStringList items;
    for(int i = 0; i < ui->positiveList->count() ;++i){
        QListWidgetItem *item = ui->positiveList->item(i);
        items.append(item->text());
    }
    return items;
}

void lenna::plugin::Widget::on_addAlbumButton_clicked()
{
    ui->positiveList->addItem(ui->albumLineEdit->text());
    ui->albumLineEdit->clear();
}

void lenna::plugin::Widget::on_removeAlbumButton_clicked()
{
    qDeleteAll(ui->positiveList->selectedItems());
}
