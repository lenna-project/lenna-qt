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

#include "widget.h"
#include "timestamp.h"
#include "ui_widget.h"

#include <QtCore/QSettings>
#include <QtGui/QPainter>

using namespace lenna::plugin;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
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
  settings.beginGroup("Timestamp");

  ui->useCheckBox->setChecked(settings.value("TimestampUse", false).toBool());
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Timestamp");

  settings.setValue("TimestampUse", ui->useCheckBox->isChecked());
}

std::string Widget::getTime() {
  if(ui->keepTimeCheckBox->isEnabled()) {
    return "";
  }
  return ui->dateTimeEdit->dateTime().toUTC().toString().toStdString();
}

std::string Widget::getDate() {
  if(ui->keepDateCheckBox->isEnabled()) {
    return "";
  }
  return ui->dateTimeEdit->dateTime().toUTC().toString().toStdString();
}

// Function
void Widget::timestamp(QImage *image) {
}
