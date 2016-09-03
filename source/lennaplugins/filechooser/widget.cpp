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
#include <QtGui/QDragEnterEvent>
#include <QtGui/QImageReader>
#include <QtWidgets/QFileDialog>
#include "ui_widget.h"

using namespace lenna::plugin;

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  setAcceptDrops(true);
  loadState();
}

Widget::~Widget() {
  saveState();
  delete ui;
}

void Widget::loadState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Filechooser");

  this->lastFolder = QDir::homePath();
}

void Widget::saveState() {
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.beginGroup("plugins");
  settings.beginGroup("Filechooser");
}

QStringList Widget::getFiles() { return this->filesList; }

// Drag and Drop
void Widget::dragEnterEvent(QDragEnterEvent* event) {
  // Drag part
  const QMimeData* md = event->mimeData();
  if (event && (md->hasUrls())) event->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent* event) {
  // Drop part
  if (event && event->mimeData()) {
    const QMimeData* mData = event->mimeData();
    // Drop Images from FileManager into ImagesList
    if (mData->hasUrls()) {
      QList<QUrl> urls = mData->urls();
      for (int x = 0; x < urls.count(); ++x) {
        if (QFileInfo(urls.at(x).toLocalFile()).isDir()) {
        } else {
          this->addFiles(QStringList(urls.at(x).toLocalFile()));
        }
      }
    }
  }
}

void Widget::on_removeImagePushButton_clicked() {
  this->filesList.removeAt(ui->filesListWidget->currentRow());
  ui->filesListWidget->takeItem(ui->filesListWidget->currentRow());
}

void Widget::on_clearListPushButton_clicked() {
  this->filesList.clear();
  ui->filesListWidget->clear();
}

void Widget::on_addImagesPushButton_clicked() { addFiles(); }

void Widget::addFiles() {
  // Last open dir is last file dir
  if (filesList.count() > 0)
    this->lastFolder = QDir(filesList.last()).absolutePath();
  // supported image formats
  QString supportedFormats;
  foreach (QByteArray format, QImageReader::supportedImageFormats()) {
    supportedFormats.append(QString(" *.").append(format));
  }
  // Create File Dialog and open selected Files
  QStringList files = QFileDialog::getOpenFileNames(
      this, tr("Please select a file"), this->lastFolder,
      "All Supported Image Files (" + supportedFormats +
          ");;"
          "Joint Photographic Experts Group File (*.jpg *.jpeg);;"
          "All Files (*.*)");
  addFiles(files);
}

void Widget::addFiles(QStringList files) {
  // Check if a file exists
  if (!files.isEmpty()) {
    foreach (QString file, files) {
      if (QFile().exists(file) && !this->filesList.contains(file)) {
        filesList.append(file);
        addFileItem(file);
      }
    }
  }
}

void Widget::addFileItem(QString file) {
  QListWidgetItem* item = new QListWidgetItem(file);
  item->setToolTip("<img width=\"96\" src=\"" + file + "\">");
  if (ui->showPreviewCheckBox->isChecked()) {
    QIcon icon;
    QPixmap pixmap;
    // make copy of scaled image
    pixmap = QPixmap(file).scaledToHeight(48);
    // open Image to use it as Icon
    icon = QIcon(pixmap);
    // create List Item
    item->setIcon(icon);
  }
  ui->filesListWidget->addItem(item);
}

void Widget::on_showPreviewCheckBox_toggled(bool checked) {
  ui->filesListWidget->clear();
  foreach (QString file, filesList) { addFileItem(file); }
}
