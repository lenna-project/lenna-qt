/**
    This file is part of program Lenna
    Copyright (C) 2013 - 2016  FalseCAM

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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class Widget;
}

namespace lenna {
namespace plugin {

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget* parent = 0);
  ~Widget();

  QString getApiKey();
  QString getSearchText();
  int getMaxImages();
  void setPreview(QImage &image);

 private slots:

  void on_getApiKeyLinkButton_clicked();

private:
  Ui::Widget* ui;
  void loadState();
  void saveState();
};
}
}

#endif  // WIDGET_H
