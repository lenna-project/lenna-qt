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

#include "flickrdownloader.h"
#include <QCoreApplication>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtWidgets/QProxyStyle>
#include "widget.h"

using namespace lenna;
using namespace lenna::plugin;

FlickrDownloader::FlickrDownloader() {
  this->widget = 0;
  has_next = false;
  this->position = 0;
}

FlickrDownloader::~FlickrDownloader() {}

QString FlickrDownloader::getName() { return QString("flickrdownloader"); }

QString FlickrDownloader::getTitle() {
  return QString(tr("Flickr Downloader"));
}

QString FlickrDownloader::getVersion() { return QString("0.9"); }

QString FlickrDownloader::getAuthor() { return QString("FalseCAM"); }

QString FlickrDownloader::getDescription() {
  return QString(tr("Plugin to load images from desktop."));
}

QIcon FlickrDownloader::getIcon() {
  QProxyStyle s;
  return s.standardIcon(QStyle::SP_DriveNetIcon);
}

QWidget *FlickrDownloader::getWidget() {
  if (!widget) {
    widget = new Widget();
  }
  return widget;
}

Plugin *FlickrDownloader::getInstance(QString uid) {
  Plugin *plugin = new FlickrDownloader();
  plugin->setUID(uid);
  return plugin;
}

void FlickrDownloader::init() {
  this->apiKey = widget->getApiKey();
  this->searchText = widget->getSearchText();
  this->maxImages = widget->getMaxImages();

  startSearch();
  this->position = 0;
  has_next = this->position < this->imageUrls.size();
}

bool FlickrDownloader::hasNext() { return has_next; }

std::shared_ptr<LennaImage> FlickrDownloader::next() {
  std::shared_ptr<LennaImage> image(new LennaImage());
  if (has_next) {
    QByteArray imageData = download(this->imageUrls.at(this->position).second);
    QImage img = QImage::fromData(imageData, "JPG");
    img = img.convertToFormat(QImage::Format_RGB888);
    this->widget->setPreview(img);
    cv::Mat mat;
    cv::cvtColor(cv::Mat(img.height(), img.width(), CV_8UC3,
                         (uchar *)img.bits(), img.bytesPerLine()),
                 mat, CV_BGR2RGB);
    image->setMat(mat);
    image->setAlbum(this->searchText);
    image->setName(this->imageUrls.at(this->position).first);
    this->position++;
    has_next = this->position < this->imageUrls.size();
  }

  return image;
}

int FlickrDownloader::getProgress() {
  int progress = 0;
  progress = this->position * 100 / this->imageUrls.size();
  return progress;
}

void FlickrDownloader::startSearch() {
  QByteArray response = download(
      QUrl(QString("https://api.flickr.com/services/rest/"
                   "?method=flickr.photos.search&api_key=%1&text=%2&per_page=%"
                   "3&format=json&nojsoncallback=1")
               .arg(this->apiKey)
               .arg(this->searchText)
               .arg(this->maxImages)));
  parseSearchResponse(response);
}

void FlickrDownloader::parseSearchResponse(QByteArray json) {
  this->imageUrls.clear();
  QJsonDocument d = QJsonDocument::fromJson(json);
  QJsonObject root = d.object();
  QJsonObject jPhotos = root.value("photos").toObject();
  QJsonArray jPhoto = jPhotos.value("photo").toArray();
  for (QJsonValue vphoto : jPhoto) {
    QJsonObject ophoto = vphoto.toObject();
    int farm = ophoto.value("farm").toInt(1);
    QString server = ophoto.value("server").toString();
    QString id = ophoto.value("id").toString();
    QString secret = ophoto.value("secret").toString();
    QString imageUrl = QString("http://farm%1.staticflickr.com/%2/%3_%4_n.jpg")
                           .arg(farm)
                           .arg(server)
                           .arg(id)
                           .arg(secret);
    this->imageUrls.push_back(std::make_pair(id, imageUrl));
  }
}

QByteArray FlickrDownloader::download(QUrl url) {
  QByteArray response;
  QEventLoop eventLoop;

  // "quit()" the event-loop, when the network request "finished()"
  QNetworkAccessManager mgr;
  QObject::connect(&mgr, SIGNAL(finished(QNetworkReply *)), &eventLoop,
                   SLOT(quit()));

  // the HTTP request
  QNetworkRequest req(url);
  QNetworkReply *reply = mgr.get(req);
  eventLoop.exec();  // blocks stack until "finished()" has been called

  if (reply->error() == QNetworkReply::NoError) {
    // success
    response = reply->readAll();
    delete reply;
  } else {
    // failure
    qDebug() << "Failure" << reply->errorString();
    delete reply;
  }
  return response;
}

QString FlickrDownloader::getName(QString file) {
  QString name;
  name = QFileInfo(file).baseName();
  return name;
}

QString FlickrDownloader::getFolder(QString file) {
  QString folder;
  folder = QDir(QFileInfo(file).absoluteDir()).dirName();
  return folder;
}
