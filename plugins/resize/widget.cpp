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
#include "ui_widget.h"
#include "resize.h"

#include <QtCore/QSettings>
#include <QtGui/QPainter>

using namespace lenna::plugin::resize;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    loadState();
}

Widget::~Widget()
{
    saveState();
    delete ui;
}

void Widget::loadState(){
}

void Widget::saveState(){

}

bool Widget::resizePixel(){
    return ui->pixelRadioButton->isChecked();
}

bool Widget::resizePercent(){
    return ui->percentRadioButton->isChecked();
}

int Widget::percentWidth(){
    return ui->percentWidthSpinBox->value();
}

int Widget::percentHeight(){
    return ui->percentHeightSpinBox->value();
}

int Widget::pixelWidth(){
    return ui->pixelWidthSpinBox->value();
}

int Widget::pixelHeight(){
    return ui->pixelHeightSpinBox->value();
}
