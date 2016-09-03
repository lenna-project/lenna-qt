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

#include "previewimagelabel.h"
#include <QtGui/QtGui>

PreviewImageLabel::PreviewImageLabel(QWidget *parent) : QLabel(parent) {
  setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
  setAlignment(Qt::AlignCenter);
  setAcceptDrops(true);
  setAutoFillBackground(true);
  setMaximumSize(256, 256);
  setScaledContents(true);
}

void PreviewImageLabel::dropEvent(QDropEvent *event) {
  // Drop part
  if (event && event->mimeData()) {
    const QMimeData *mData = event->mimeData();
    // Drop Images from FileManager into ImageList
    if (mData->hasUrls()) {
      QList<QUrl> urls = mData->urls();
      QString lastFile;
      for (int x = 0; x < urls.count(); ++x) {
        if (QFileInfo(urls.at(x).toLocalFile()).isDir())
          ;
        else
          lastFile = urls.at(x).toLocalFile();
      }
      emit imageDroped(lastFile);
    }
  }
}

void PreviewImageLabel::dragEnterEvent(QDragEnterEvent *event) {
  // setText(tr("<drop image file>"));
  // setBackgroundRole(QPalette::Highlight);
  event->acceptProposedAction();
}

void PreviewImageLabel::dragMoveEvent(QDragMoveEvent *event) {
  event->acceptProposedAction();
}

void PreviewImageLabel::dragLeaveEvent(QDragLeaveEvent *event) {
  event->accept();
}
