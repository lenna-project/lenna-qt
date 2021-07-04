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

#ifndef HAARCASCADECROP_H
#define HAARCASCADECROP_H

#include "lenna/plugins/editplugin.h"
#include "widget.h"

#include <opencv2/objdetect/objdetect.hpp>

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtGui/QIcon>

namespace lenna {
namespace plugin {
namespace haarcascadecrop {

class HaarcascadeCrop : public EditPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "lenna.haarcascadecrop" FILE "haarcascadecrop.json")
  Q_INTERFACES(lenna::plugin::EditPlugin)

 public:
  HaarcascadeCrop();
  ~HaarcascadeCrop();
  std::string getName();
  std::string getTitle();
  std::string getVersion();
  std::string getAuthor();
  std::string getDescription();
  QIcon getIcon();
  QWidget *getWidget();

  std::shared_ptr<Plugin> getInstance(QString uid);

  void loadCascade(std::string cascadeFile);

  void edit(std::shared_ptr<LennaImage> image);

 private:
  Widget *widget = nullptr;

  std::string cascadeFile = "data/haarcascadecrop/haarcascade_smile.xml";
  cv::CascadeClassifier cascade;
};
}  // namespace haarcascadecrop
}  // namespace plugin
}  // namespace lenna

#endif  // HAARCASCADECROP_H
