/**
    This file is part of program Lenna which is released under MIT License.
    See file LICENSE or go to https://github.com/lenna-project/lenna for full license details.
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
