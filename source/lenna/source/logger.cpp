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

#include "logger.h"
#include <stdio.h>
#include <QtCore/QMutex>

using namespace lenna;

Logger *Logger::singleton = 0;

Logger::Logger(QObject *parent) : QObject(parent) {}

Logger *Logger::instance() {
  static QMutex mutex;
  if (!singleton) {
    mutex.lock();

    if (!singleton) singleton = new Logger(0);

    mutex.unlock();
  }

  return singleton;
}

void Logger::debug(QString msg) {
  instance()->debugMsgs.append(msg);
  instance()->msgs.append("Debug: " + msg);
  emit instance()->newDebug(msg);
  emit instance()->newMessage(msg);
}

void Logger::warning(QString msg) {
  instance()->warningMsgs.append(msg);
  instance()->msgs.append("Warning: " + msg);
  emit instance()->newWarning(msg);
  emit instance()->newMessage(msg);
}

void Logger::critical(QString msg) {
  instance()->criticalMsgs.append(msg);
  instance()->msgs.append("Critical: " + msg);
  emit instance()->newCritical(msg);
  emit instance()->newMessage(msg);
}

void Logger::fatal(QString msg) {
  instance()->fatalMsgs.append(msg);
  instance()->msgs.append("Fatal: " + msg);
  emit instance()->newFatal(msg);
  emit instance()->newMessage(msg);
}

void Logger::info(QString msg) {
  instance()->infoMsgs.append(msg);
  instance()->msgs.append("Info: " + msg);
  emit instance()->newInfo(msg);
  emit instance()->newMessage(msg);
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context,
                            const QString &msg) {
  QByteArray localMsg = msg.toLocal8Bit();
  switch (type) {
    case QtDebugMsg:
      debug(msg);
      fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      break;
    case QtWarningMsg:
      warning(msg);
      fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      break;
    case QtCriticalMsg:
      critical(msg);
      fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      break;
    case QtFatalMsg:
      fatal(msg);
      fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      break;
    case QtInfoMsg:
      debug(msg);
      fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      break;
    default:
      break;
  }
}

QStringList Logger::getDebugMessages() { return instance()->debugMsgs; }

QStringList Logger::getWarningMessages() { return instance()->warningMsgs; }

QStringList Logger::getCriticalMessages() { return instance()->criticalMsgs; }

QStringList Logger::getFatalMessages() { return instance()->fatalMsgs; }

QStringList Logger::getInfoMessages() { return instance()->infoMsgs; }

QStringList Logger::getMessages() { return instance()->msgs; }
