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
#include "rename.h"
#include "ui_widget.h"

#include <QtCore/QSettings>
#include <QtGui/QPainter>

using namespace lenna::plugin::rename;

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
  settings.beginGroup("Rename");

  ui->renameRadioButton->setChecked(
      settings.value("RenameUse", false).toBool());
  ui->newNameCheckBox->setChecked(settings.value("NewName", false).toBool());
  ui->nameLineEdit->setText(settings.value("Name", "").toString());
  ui->prefixLineEdit->setText(settings.value("Prefix", "").toString());
  ui->suffixLineEdit->setText(settings.value("Suffix", "").toString());
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Rename");

  settings.setValue("RenameUse", ui->renameRadioButton->isChecked());
  settings.setValue("NewName", ui->newNameCheckBox->isChecked());
  settings.setValue("Name", ui->nameLineEdit->text());
  settings.setValue("Prefix", ui->prefixLineEdit->text());
  settings.setValue("Suffix", ui->suffixLineEdit->text());
}

bool Widget::isRename() { return ui->renameRadioButton->isChecked(); }

bool Widget::isNewName() { return ui->newNameCheckBox->isChecked(); }

QString Widget::newName() { return ui->nameLineEdit->text(); }

QString Widget::prefix() { return ui->prefixLineEdit->text(); }

QString Widget::suffix() { return ui->suffixLineEdit->text(); }
