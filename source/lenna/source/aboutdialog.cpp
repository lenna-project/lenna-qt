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

#include "aboutdialog.h"
#include <QDesktopServices>
#include <QtCore/QEventLoop>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include "defines.h"
#include "lenna/lenna.h"
#include "ui_aboutdialog.h"

using namespace lenna;

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutDialog) {
  ui->setupUi(this);
  ui->versionLabel->setText(Lenna::applicationVersion() + " - " +
                            QString::fromStdString(PROJECT_REVISION));
  manager = 0;
  initAbout();
  initAuthors();
  initThanksto();
  initLicense();
}

AboutDialog::~AboutDialog() { delete ui; }

void AboutDialog::initLicense() {
  ui->licenseBrowser->setAlignment(Qt::AlignCenter);

  QFile file(":/about/license.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  } else {
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
      ui->licenseBrowser->insertPlainText(line);
      ui->licenseBrowser->insertPlainText("\n");
      line = in.readLine();
    }
    ui->licenseBrowser->moveCursor(QTextCursor::Start);
  }
}

void AboutDialog::initAbout() {
  ui->aboutLabel->setAlignment(Qt::AlignCenter);

  QFile file(":/about/about.html");
  QString text;
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  } else {
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
      text.append(line);
      text.append("\n");
      line = in.readLine();
    }
  }
  ui->aboutLabel->setText(text);
}

void AboutDialog::initAuthors() {
  ui->authorsLabel->setAlignment(Qt::AlignCenter);

  QFile file(":/about/authors.html");
  QString text;
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  } else {
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
      text.append(line);
      text.append("\n");
      line = in.readLine();
    }
  }
  ui->authorsLabel->setText(text);
}

void AboutDialog::initThanksto() {
  ui->thankstoLabel->setAlignment(Qt::AlignCenter);

  QFile file(":/about/thanksto.html");
  QString text;
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  } else {
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
      text.append(line);
      text.append("\n");
      line = in.readLine();
    }
  }
  ui->thankstoLabel->setText(text);
}

void AboutDialog::initUpdates() {
  ui->thisVersionLabel->setText(tr("This Version: ") +
                                Lenna::applicationVersion());
  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(
      "https://raw.githubusercontent.com/lenna-project/lenna/main/VERSION")));
  QEventLoop loop;
  QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();
  ui->htmlVersionLabel->setText(tr("Online Version: ") + reply->readAll());
  QObject::disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  delete reply;
  delete manager;
}

void AboutDialog::on_pushButton_clicked() { this->close(); }

void AboutDialog::on_tabWidget_currentChanged(int index) {
  // When tab for updates is selected, download update information from website.
  initUpdates();
}

void AboutDialog::on_commandLinkButton_clicked() {
  QDesktopServices::openUrl(QUrl("https://lenna.app", QUrl::TolerantMode));
}
