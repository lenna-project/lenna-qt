/**
    This file is part of program Lenna which is released under MIT License.
    See file LICENSE or go to https://github.com/lenna-project/lenna for full license details.
 */

#include "timestamp.h"
#include "widget.h"

#include <QtGui/QPainter>

using namespace lenna;
using namespace lenna::plugin;
using namespace lenna::plugin::timestamp;

Timestamp::Timestamp() { widget = 0; }

Timestamp::~Timestamp() {
  if (this->widget) delete this->widget;
}

std::string Timestamp::getName() { return std::string("timestamp"); }

std::string Timestamp::getTitle() { return tr("Timestamp").toStdString(); }

std::string Timestamp::getVersion() { return std::string("0.1"); }

std::string Timestamp::getAuthor() { return std::string("chriamue"); }

std::string Timestamp::getDescription() {
  return tr("Plugin to change timestamps of images").toStdString();
}

QIcon Timestamp::getIcon() { return QIcon(":/plugins/timestamp/timestamp"); }

QWidget *Timestamp::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

void Timestamp::edit(std::shared_ptr<LennaImage> img) {
  std::string time = widget->getTime();
  std::string date = widget->getDate();
  //cv::blur(img->getImage(), img->getImage(), cv::Size(size, size));
}

std::shared_ptr<Plugin> Timestamp::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Timestamp());
  plugin->setUID(uid);
  return plugin;
}
