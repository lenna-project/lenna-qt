/**
    This file is part of program Lenna
    Copyright (C) 2013-2016 FalseCAM

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

#ifndef LOGGER_H
#define LOGGER_H

#include <lenna-qt/lennaplugin/lennaplugin_api.h>

#include <QObject>
#include <QtCore/QStringList>

namespace lenna {
class LENNAPLUGIN_API Logger : public QObject {
  Q_OBJECT
 public:
  static Logger *instance();
  static void messageHandler(QtMsgType type, const QMessageLogContext &context,
                             const QString &msg);
  static QStringList getDebugMessages();
  static QStringList getWarningMessages();
  static QStringList getCriticalMessages();
  static QStringList getFatalMessages();
  static QStringList getInfoMessages();
  static QStringList getMessages();

 signals:
  void newDebug(QString msg);
  void newWarning(QString msg);
  void newCritical(QString msg);
  void newFatal(QString msg);
  void newInfo(QString msg);
  void newMessage(QString msg);

 public slots:
  static void debug(QString msg);
  static void warning(QString msg);
  static void critical(QString msg);
  static void fatal(QString msg);
  static void info(QString msg);

 private:
  explicit Logger(QObject *parent = 0);
  static Logger *singleton;

  QStringList msgs;
  QStringList debugMsgs;
  QStringList warningMsgs;
  QStringList criticalMsgs;
  QStringList fatalMsgs;
  QStringList infoMsgs;
};
}  // namespace lenna

#endif  // LOGGER_H
