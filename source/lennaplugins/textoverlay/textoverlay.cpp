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

#include "textoverlay.h"
#include "widget.h"
#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin::textoverlay;

Textoverlay::Textoverlay()
{
    widget = 0;
}

Textoverlay::~Textoverlay()
{
}

QString Textoverlay::getName(){
    return QString("textoverlay");
}

QString Textoverlay::getTitle(){
    return QString(tr("Textoverlay"));
}

QString Textoverlay::getVersion(){
    return QString("0.1");
}

QString Textoverlay::getAuthor(){
    return QString("FalseCAM");
}

QString Textoverlay::getDescription(){
    return QString(tr("Plugin to put text onto images"));
}

QIcon Textoverlay::getIcon(){
    return QIcon(":/plugins/textoverlay/textoverlay");
}

QWidget *Textoverlay::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Textoverlay::edit(Image *img){
    getWidget();
    if(widget->isActivated()){
        int cols = img->getImage().cols;
        int rows = img->getImage().rows;
        QImage * overlay = new QImage(img->getImage().data, img->getImage().cols,
                                      img->getImage().rows,
                                      img->getImage().step,
                                      QImage::Format_RGB888);
        QPainter painter(overlay);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        int x = (int) ((double) cols * ((double) widget->getX()/ 100.0));
        int y = (int) ((double) rows * ((double) widget->getY()/ 100.0));
        painter.setPen(*widget->getColor());
        QFont tempFont = *widget->getFont();
        tempFont.setPointSize((int) (tempFont.pointSize() * cols / 100));
        painter.setFont(tempFont);
        painter.drawText(x, y, widget->getText());
        painter.end();

    }
}
