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
#include "textoverlay.h"
#include "ui_widget.h"

#include <QtCore/QSettings>
#include <QtGui/QPainter>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QFontDialog>

using namespace lenna::plugin::textoverlay;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  color = 0;
  font = 0;
  ui->setupUi(this);
  setColor(new QColor(Qt::black));
  setFont(new QFont("Times", 10));
  loadState();
}

Widget::~Widget() {
  saveState();
  delete ui;
}

void Widget::loadState() {}

void Widget::saveState() {}

bool Widget::isActivated() { return ui->textCheckBox->isChecked(); }

QString Widget::getText() { return ui->textLineEdit->text(); }

int Widget::getX() { return ui->xSpinBox->value(); }

int Widget::getY() { return ui->ySpinBox->value(); }

void Widget::setFont(QFont *f) {
  if (font == f) return;
  delete font;
  font = new QFont(*f);
  ui->fontButton->setText(
      QString("%1 %2").arg(font->family()).arg(font->pointSize()));
}

void Widget::setColor(QColor *c) {
  if (color == c) return;
  delete color;
  color = new QColor(*c);
  QPixmap pixmap(16, 16);
  pixmap.fill(*color);
  ui->colorPushButton->setIcon(QIcon(pixmap));
}

void Widget::on_fontButton_clicked() {
  bool ok;
  QFont temp = QFontDialog::getFont(&ok, *font, this);
  if (ok) {
    setFont(&temp);
  } else {
  }
}

void Widget::on_colorPushButton_clicked() {
  QColor temp = QColorDialog::getColor(*color, this);
  setColor(&temp);
}

QColor *Widget::getColor() { return color; }

QFont *Widget::getFont() { return font; }
