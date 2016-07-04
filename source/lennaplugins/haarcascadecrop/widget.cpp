/**
    This file is part of program Lenna
    Copyright (C) 2016 FalseCAM

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
#include "haarcascadecrop.h"
#include "ui_widget.h"

#include <QGraphicsItem>
#include <QtCore/QSettings>
#include <QtGui/QPainter>
#include <QtWidgets/QFileDialog>

using namespace lenna::plugin::haarcascadecrop;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  loadState();
}

Widget::~Widget() {
  saveState();
  delete ui;
}

void Widget::setHaarcascade(QString haarcascade) {
  ui->haarcascadeLineEdit->setText(haarcascade);
}

void Widget::setHaarcascadeCrop(HaarcascadeCrop *haarcascadecrop) {
  this->haarcascadecrop = haarcascadecrop;
}

bool Widget::isCrop() { return ui->cropCheckBox->isChecked(); }

void Widget::loadState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("HaarcascadeCrop");
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("HaarcascadeCrop");
}

void lenna::plugin::haarcascadecrop::Widget::
    on_selectHaarcascadePushButton_clicked() {
  QString file = QFileDialog::getOpenFileName(this, tr("Please select a file"),
                                              ui->haarcascadeLineEdit->text(),
                                              "Haarcascade File (*.xml);;"
                                              "All Files (*.*)");
  this->haarcascadecrop->loadCascade(file.toStdString());
}
