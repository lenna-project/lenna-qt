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

#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include "plugins/inputplugin.h"
#include "image.h"
#include "widget.h"

namespace lenna{
namespace plugin{

class FileChooser : public InputPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lenna.filechooser" FILE "filechooser.json")
    Q_INTERFACES(lenna::plugin::InputPlugin)

public:
    FileChooser();
    ~FileChooser();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();


    void init();
    bool hasNext();
    Image *next();
    int getProgress();

private:
    Widget *widget;
    bool has_next;
    QStringList files;
    int position;

    QString getFolder(QString file);
    QString getName(QString file);
};

}
}

#endif // FILECHOOSER_H
