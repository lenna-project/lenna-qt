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
#include "resize.h"
#include "ui_widget.h"

#include <QtCore/QSettings>
#include <QtGui/QPainter>

using namespace lenna::plugin::resize;

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
  settings.beginGroup("Resize");

  ui->percentRadioButton->setChecked(
      settings.value("PercentUse", false).toBool());
  ui->pixelRadioButton->setChecked(settings.value("PixelUse", false).toBool());

  ui->pixelWidthSpinBox->setValue(settings.value("PixelX", 1920).toInt());
  ui->pixelHeightSpinBox->setValue(settings.value("PixelY", 1080).toInt());
  ui->percentWidthSpinBox->setValue(settings.value("PercentX", 100).toInt());
  ui->percentHeightSpinBox->setValue(settings.value("PercentY", 100).toInt());
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Resize");

  settings.setValue("PercentUse", ui->percentRadioButton->isChecked());
  settings.setValue("PixelUse", ui->pixelRadioButton->isChecked());
  settings.setValue("PixelX", ui->pixelWidthSpinBox->value());
  settings.setValue("PixelY", ui->pixelHeightSpinBox->value());
  settings.setValue("PercentX", ui->percentWidthSpinBox->value());
  settings.setValue("PercentY", ui->percentHeightSpinBox->value());
}

bool Widget::resizePixel() { return ui->pixelRadioButton->isChecked(); }

bool Widget::resizePercent() { return ui->percentRadioButton->isChecked(); }

int Widget::percentWidth() { return ui->percentWidthSpinBox->value(); }

int Widget::percentHeight() { return ui->percentHeightSpinBox->value(); }

int Widget::pixelWidth() { return ui->pixelWidthSpinBox->value(); }

int Widget::pixelHeight() { return ui->pixelHeightSpinBox->value(); }

void Widget::on_sizeRatioComboBox_currentIndexChanged(const QString &arg1) {
  if (ui->percentRadioButton->isChecked()) {
    if (arg1 == "1:1") {
      ui->percentHeightSpinBox->setValue(ui->percentWidthSpinBox->value() *
                                         (1.0 / 1));
    } else if (arg1 == "5:4") {
      ui->percentHeightSpinBox->setValue(ui->percentWidthSpinBox->value() *
                                         (4.0 / 5));
    } else if (arg1 == "4:3") {
      ui->percentHeightSpinBox->setValue(ui->percentWidthSpinBox->value() *
                                         (3.0 / 4));
    } else if (arg1 == "16:9") {
      ui->percentHeightSpinBox->setValue(ui->percentWidthSpinBox->value() *
                                         (9.0 / 16));
    }
  } else {
    if (arg1 == "1:1") {
      ui->pixelHeightSpinBox->setValue(ui->pixelWidthSpinBox->value() *
                                       (1.0 / 1));
    } else if (arg1 == "5:4") {
      ui->pixelHeightSpinBox->setValue(ui->pixelWidthSpinBox->value() *
                                       (4.0 / 5));
    } else if (arg1 == "4:3") {
      ui->pixelHeightSpinBox->setValue(ui->pixelWidthSpinBox->value() *
                                       (3.0 / 4));
    } else if (arg1 == "16:9") {
      ui->pixelHeightSpinBox->setValue(ui->pixelWidthSpinBox->value() *
                                       (9.0 / 16));
    }
  }
}

void Widget::on_pixelComboBox_currentIndexChanged(const QString &arg1) {
  ui->pixelRadioButton->setChecked(true);
  if (arg1 == "VGA (640x480)") {
    ui->pixelWidthSpinBox->setValue(640);
    ui->pixelHeightSpinBox->setValue(480);
  } else if (arg1 == "XGA (1024x768)") {
    ui->pixelWidthSpinBox->setValue(1024);
    ui->pixelHeightSpinBox->setValue(768);
  } else if (arg1 == "NTSC (576x486)") {
    ui->pixelWidthSpinBox->setValue(576);
    ui->pixelHeightSpinBox->setValue(486);
  } else if (arg1 == "PAL (720x486)") {
    ui->pixelWidthSpinBox->setValue(720);
    ui->pixelHeightSpinBox->setValue(486);
  } else if (arg1 == "HD (1920x1080)") {
    ui->pixelWidthSpinBox->setValue(1920);
    ui->pixelHeightSpinBox->setValue(1080);
  } else if (arg1 == "Flickr large (768x1024)") {
    ui->pixelWidthSpinBox->setValue(768);
    ui->pixelHeightSpinBox->setValue(1024);
  } else if (arg1 == "iPhone landscape (480x320)") {
    ui->pixelWidthSpinBox->setValue(480);
    ui->pixelHeightSpinBox->setValue(320);
  } else if (arg1 == "160x160") {
    ui->pixelWidthSpinBox->setValue(160);
    ui->pixelHeightSpinBox->setValue(160);
  } else if (arg1 == "HD 720 (1280x720)") {
    ui->pixelWidthSpinBox->setValue(1280);
    ui->pixelHeightSpinBox->setValue(720);
  } else if (arg1 == "SVGA (800x600)") {
    ui->pixelWidthSpinBox->setValue(800);
    ui->pixelHeightSpinBox->setValue(600);
  } else if (arg1 == "PSP (480x272)") {
    ui->pixelWidthSpinBox->setValue(480);
    ui->pixelHeightSpinBox->setValue(272);
  } else if (arg1 == "2K (2048x1080)") {
    ui->pixelWidthSpinBox->setValue(2048);
    ui->pixelHeightSpinBox->setValue(1080);
  }
}
