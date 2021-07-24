/**
    This file is part of program Lenna which is released under MIT License.
    See file LICENSE or go to https://github.com/lenna-project/lenna for full license details.
 */

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <lenna/plugins/editplugin.h>
#include "widget.h"

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtGui/QIcon>

namespace lenna {
namespace plugin {
namespace timestamp {

class Timestamp : public EditPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "lenna.blur" FILE "timestamp.json")
  Q_INTERFACES(lenna::plugin::EditPlugin)

 public:
  Timestamp();
  ~Timestamp();
  std::string getName();
  std::string getTitle();
  std::string getVersion();
  std::string getAuthor();
  std::string getDescription();
  QIcon getIcon();
  QWidget *getWidget();

  void edit(std::shared_ptr<LennaImage> image);

  std::shared_ptr<Plugin> getInstance(QString uid);

 private:
  Widget *widget;
};
}  // namespace timestamp
}  // namespace plugin
}  // namespace lenna

#endif  // TIMESTAMP_H
