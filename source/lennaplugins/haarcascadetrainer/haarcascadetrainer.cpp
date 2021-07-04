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

#include "haarcascadetrainer.h"

#include <QDir>
#include <QProxyStyle>
#include <QTextStream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::haarcascadetrainer;

HaarcascadeTrainer::HaarcascadeTrainer() { this->widget = 0; }

HaarcascadeTrainer::~HaarcascadeTrainer() {}

std::string HaarcascadeTrainer::getName() {
  return std::string("haarcascadetrainer");
}

std::string HaarcascadeTrainer::getTitle() {
  return tr("Haarcascade Trainer").toStdString();
}

std::string HaarcascadeTrainer::getVersion() { return std::string("1.0"); }

std::string HaarcascadeTrainer::getAuthor() { return std::string("FalseCAM"); }

std::string HaarcascadeTrainer::getDescription() {
  return tr("Plugin to save images in a format able to train an opencv "
            "haarcascade")
      .toStdString();
}

QIcon HaarcascadeTrainer::getIcon() {
  QProxyStyle s;
  return s.standardIcon(QStyle::SP_TrashIcon);
}

QWidget *HaarcascadeTrainer::getWidget() {
  if (!widget) {
    widget = new Widget();
  }
  return widget;
}

std::shared_ptr<Plugin> HaarcascadeTrainer::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin =
      std::shared_ptr<Plugin>(new HaarcascadeTrainer());
  plugin->setUID(uid);
  return plugin;
}

void HaarcascadeTrainer::out(std::shared_ptr<LennaImage> image) {
  getWidget();
  QString folder = this->widget->getFolder();
  if (isPositiveAlbum(image->getAlbum())) {
    folder.append("/positive_images/");
  } else {
    folder.append("/negative_images/");
  }

  QString file = folder + image->getName() + ".jpg";
  if (!QDir(folder).exists()) {
    QDir().mkdir(folder);
  }

  cv::imwrite(file.toStdString().c_str(), image->getImage());

  if (isPositiveAlbum(image->getAlbum())) {
    addPositiveFile(file);
  } else {
    addNegativeFile(file);
  }
}

void HaarcascadeTrainer::finnish() {}

bool HaarcascadeTrainer::isPositiveAlbum(QString album) {
  return widget->getPositiveAlbums().contains(album);
}

void HaarcascadeTrainer::addPositiveFile(QString imagefile) {
  QString folder = this->widget->getFolder();
  QFile file(folder + "/" + "positives.txt");
  if (file.open(QFile::WriteOnly | QFile::Append)) {
    QTextStream stream(&file);
    stream << imagefile << "\n";
    file.close();
  }
}

void HaarcascadeTrainer::addNegativeFile(QString imagefile) {
  QString folder = this->widget->getFolder();
  QFile file(folder + "/" + "negatives.txt");
  if (file.open(QFile::WriteOnly | QFile::Append)) {
    QTextStream stream(&file);
    stream << imagefile << "\n";
    file.close();
  }
}
