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

#include "widget.h"
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QMimeData>
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QImageReader>
#include <QtWidgets/QFileDialog>
#include "ui_widget.h"

using namespace lenna::plugin;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  loadState();
}

Widget::~Widget() {
  saveState();
  delete ui;
}

QString Widget::getApiKey() { return ui->apiKeyLineEdit->text(); }

QString Widget::getSearchText() { return ui->searchTextLineEdit->text(); }

int Widget::getMaxImages() { return ui->maxImagesSpinBox->value(); }

void Widget::setPreview(QImage &image) {
  ui->previewLabel->setPixmap(QPixmap::fromImage(image));
}

void Widget::loadState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Flickrdownloader");
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Flickrdownloader");
}

void lenna::plugin::Widget::on_getApiKeyLinkButton_clicked() {
  QDesktopServices::openUrl(
      QUrl("https://www.flickr.com/services/api/misc.api_keys.html"));
}
