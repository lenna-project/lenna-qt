/**
    This file is part of program Lenna
    Copyright (C) 2013-2016  FalseCAM

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

#ifndef FLICKRDOWNLOADER_H
#define FLICKRDOWNLOADER_H

#include <QList>
#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtGui/QIcon>
#include <utility>
#include <vector>
#include "lenna/image.h"
#include "lenna/plugins/inputplugin.h"
#include "widget.h"

namespace lenna {
namespace plugin {

class FlickrDownloader : public InputPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "lenna.flickrdownloader" FILE "flickrdownloader.json")
  Q_INTERFACES(lenna::plugin::InputPlugin)

 public:
  FlickrDownloader();
  ~FlickrDownloader();
  QString getName();
  QString getTitle();
  QString getVersion();
  QString getAuthor();
  QString getDescription();
  QIcon getIcon();
  QWidget *getWidget();

  Plugin *getInstance(QString uid);

  void init();
  bool hasNext();
  std::shared_ptr<LennaImage> next();
  int getProgress();

  void startSearch();
  void parseSearchResponse(QByteArray json);
  QByteArray download(QUrl url);

 private:
  Widget *widget;
  bool has_next;
  unsigned int position;

  QString getFolder(QString file);
  QString getName(QString file);

  QString apiKey;
  QString searchText;
  int maxImages;

  std::vector<std::pair<QString, QString>> imageUrls;
};
}
}

#endif  // FLICKRDOWNLOADER_H
