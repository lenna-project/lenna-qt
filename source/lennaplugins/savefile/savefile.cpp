/**
    This file is part of program Lenna
    Copyright (C) 2013-2016 FalseCAM

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

#include "savefile.h"

#include <QDir>
#include <QProxyStyle>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace lenna;
using namespace lenna::plugin;

SaveFile::SaveFile() { this->widget = 0; }

SaveFile::~SaveFile() {}

QString SaveFile::getName() { return QString("savefile"); }

QString SaveFile::getTitle() { return QString(tr("Save File")); }

QString SaveFile::getVersion() { return QString("1.0"); }

QString SaveFile::getAuthor() { return QString("FalseCAM"); }

QString SaveFile::getDescription() {
  return QString(tr("Plugin to save images to desktop."));
}

QIcon SaveFile::getIcon() {
  QProxyStyle s;
  return s.standardIcon(QStyle::SP_FileDialogNewFolder);
}

QWidget *SaveFile::getWidget() {
  if (!widget) {
    widget = new Widget();
  }
  return widget;
}

std::shared_ptr<Plugin> SaveFile::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new SaveFile());
  plugin->setUID(uid);
  return plugin;
}

void SaveFile::out(std::shared_ptr<LennaImage> image) {
  getWidget();
  QString folder = this->widget->getFolder();
  folder.append("/");
  folder.append(image->getAlbum());
  folder.append("/");
  QString file = folder + image->getName() + "." + widget->getImageFormat();
  if (!QDir(folder).exists()) {
    QDir().mkdir(folder);
  }
  std::vector<int> params;

  if (widget->getImageQuality() != 0) {
    if (widget->getImageFormat().toLower() == "png") {
      params.push_back(cv::IMWRITE_PNG_COMPRESSION);
      params.push_back(widget->getImageQuality() / 100);
    } else if (widget->getImageFormat().toLower() == "jpg" ||
               widget->getImageFormat().toLower() == "jpeg") {
      params.push_back(cv::IMWRITE_JPEG_QUALITY);
      params.push_back(widget->getImageQuality());
    }
  }
  cv::imwrite(file.toStdString().c_str(), image->getImage(), params);
}

void SaveFile::finnish() {}
