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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtGui/QIcon>

class Plugin: virtual public QObject{
public:
    virtual QString getName() = 0;
    virtual QString getTitle() = 0;
    virtual QString getVersion() = 0;
    virtual QString getAuthor() = 0;
    virtual QString getDescription() = 0;
    virtual QIcon getIcon() = 0;
    virtual QWidget* getWidget() = 0;
};

#endif // PLUGIN_H
