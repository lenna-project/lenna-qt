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

#ifndef TIPSDIALOG_H
#define TIPSDIALOG_H

#include <QtCore/QStringList>
#include <QtWidgets/QDialog>

namespace Ui {
class TipsDialog;
}

class TipsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit TipsDialog(QWidget *parent = 0);
  void showOnStartup();
  ~TipsDialog();

 private slots:
  void on_okButton_clicked();

  void on_nextButton_clicked();

  void on_previousButton_clicked();

 private:
  void loadTip();
  void loadTips();
  void loadState();
  void saveState();

  Ui::TipsDialog *ui;
  QStringList *tips;
  int counter;
};

#endif  // TIPSDIALOG_H
