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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QDialog>

namespace Ui {
class AboutDialog;
}

namespace lenna {

class AboutDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AboutDialog(QWidget *parent = 0);
  ~AboutDialog();

 private slots:
  void on_pushButton_clicked();
  void on_tabWidget_currentChanged(int index);

 private:
  Ui::AboutDialog *ui;
  QNetworkAccessManager *manager;
  void initLicense();
  void initAbout();
  void initAuthors();
  void initThanksto();
  void initUpdates();
};
}

#endif  // ABOUTDIALOG_H
