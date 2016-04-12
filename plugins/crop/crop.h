/**
    This file is part of program Lenna
    Copyright (C) 2016  FalseCAM

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

#ifndef CROP_H
#define CROP_H

#include "plugins/editplugin.h"
#include "widget.h"

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>

namespace lenna{
namespace plugin{
namespace crop{

class Crop : public EditPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lenna.crop" FILE "crop.json")
    Q_INTERFACES(lenna::plugin::EditPlugin)

public:
    Crop();
    ~Crop();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void edit(Image *image);

private:
    Widget *widget = nullptr;
};

}
}
}

#endif // CROP_H
