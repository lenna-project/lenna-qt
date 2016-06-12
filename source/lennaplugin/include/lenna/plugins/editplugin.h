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

#ifndef EDITPLUGIN_H
#define EDITPLUGIN_H

#include "lenna/plugins/plugin.h"
#include "lenna/image.h"

#include <QtCore/QtPlugin>

namespace lenna{
namespace plugin{

class EditPlugin: public Plugin{
public:
    virtual ~EditPlugin() {
    }

    virtual void edit(Image *image) = 0;
};

}
}

Q_DECLARE_INTERFACE(lenna::plugin::EditPlugin,
                    "Lenna.EditPlugin/1.0");

#endif // EDITPLUGIN_H
