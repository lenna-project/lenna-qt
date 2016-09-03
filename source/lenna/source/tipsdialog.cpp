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

#include "tipsdialog.h"
#include "ui_tipsdialog.h"

#include "lenna/lenna.h"
#include "translation.h"

#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>
#include <QtWidgets/QStyle>

using namespace lenna;

TipsDialog::TipsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TipsDialog) {
  tips = new QStringList();
  ui->setupUi(this);
  this->setWindowIcon(
      this->style()->standardIcon(QStyle::SP_MessageBoxQuestion));
  ui->previousButton->setIcon(
      this->style()->standardIcon(QStyle::SP_ArrowLeft));
  ui->nextButton->setIcon(this->style()->standardIcon(QStyle::SP_ArrowRight));
  loadState();
  loadTips();
  loadTip();
}

TipsDialog::~TipsDialog() {
  saveState();
  delete ui;
}

void TipsDialog::loadTip() {
  QString tip = QString(tips->at(counter % tips->size()));
  ui->tipsBrowser->setText(tip);
}

void TipsDialog::loadTips() {
  /* Loads tips from languages tips file (/tips/tips_*locale*.txt) */

  QString tipsFile(Lenna::applicationDirPath() + "/data/tips/" + "tips_" +
                   Translation::locale() + ".txt");
  /* if tips dont exist in your language use en. */
  if (!QFile().exists(tipsFile)) {
    tipsFile =
        QString(Lenna::applicationDirPath() + "/data/tips/" + "tips_en.txt");
  }

  QFile file(tipsFile);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    /* if file couldnt be read, use some standard tips */
    tips->append("<b>No</b> Tips!");
  } else {
    QTextStream in(&file);
    /* read line by line */
    /* each line is ONE tip */
    QString line = in.readLine();
    while (!line.isNull()) {
      tips->append(line);
      line = in.readLine();
    }
  }
}

void TipsDialog::showOnStartup() {
  // Use .exec() if you want to show this dialog definitally
  if (ui->startupCheckBox->isChecked()) {
    // Show this Dialog only if counter in config not 0
    this->exec();
  }
}

void TipsDialog::loadState() {
  /* Loads counter from saved config */
  QSettings settings(Lenna::organizationName(), Lenna::applicationName());
  settings.beginGroup(QString("TipsDialog"));
  counter = settings.value(QString::fromUtf8("counter"), 1).toInt();
  ui->startupCheckBox->setChecked(
      settings.value(QString::fromUtf8("showonstartup"), true).toBool());
  settings.endGroup();
}

void TipsDialog::saveState() {
  QSettings settings(Lenna::organizationName(), Lenna::applicationName());
  settings.beginGroup(QString("TipsDialog"));
  settings.setValue(QString::fromUtf8("counter"), counter);
  settings.setValue(QString::fromUtf8("showonstartup"),
                    ui->startupCheckBox->isChecked());
  settings.endGroup();
}

void TipsDialog::on_okButton_clicked() { this->close(); }

void TipsDialog::on_nextButton_clicked() {
  counter++;
  loadTip();
}

void TipsDialog::on_previousButton_clicked() {
  counter--;
  loadTip();
}
