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

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QtCore/QMultiMap>
#include <QtCore/QObject>
#include <QtCore/QStringList>

namespace lenna {

class Translation : public QObject {
  Q_OBJECT
 public:
  explicit Translation(QObject *parent = 0);
  QStringList getLanguages();
  QString language();
  static QString locale();
  void loadLanguageFile();
  static void installPluginTranslation(QString pluginName);
  ~Translation();

 signals:

 public slots:
  void setLanguage(QString language);

 private:
  QStringList qmFiles();
  QString languageName(const QString &qmFile);
  void loadLanguage();

  QMultiMap<QString, QString> *languages;
  QString currentLanguage;
};
}

#endif  // TRANSLATION_H
