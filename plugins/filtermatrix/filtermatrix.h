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

#ifndef FILTERMATRIX_H
#define FILTERMATRIX_H

#include "plugins/editplugin.h"
#include "widget.h"

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>


class FilterMatrix : public EditPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lenna.filtermatrix" FILE "filtermatrix.json")
    Q_INTERFACES(EditPlugin)

public:
    FilterMatrix();
    ~FilterMatrix();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void edit(Image *image);

private:
    Widget *widget;
};

#endif // FILTERMATRIX_H
