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
#include "worker.h"
#include <QtCore/QThread>
#include <QtCore/QThreadPool>
#include "imageprocessor.h"
#include "plugins/pluginloader.h"

#include <lenna/logger.h>

using namespace lenna;
using namespace lenna::plugin;

Worker::Worker() { stopped = true; }

Worker::~Worker() {}

void Worker::process() {
  stopped = false;
  emit process(0);
  foreach (std::shared_ptr<InputPlugin> inputPlugin,
           PluginLoader::getInstance().getActiveInputPlugins()) {
    inputPlugin->init();

    Logger::info(QString::fromStdString(inputPlugin->getTitle()) + " initialized");

    QThreadPool threadPool(this);
    threadPool.setMaxThreadCount(QThread::idealThreadCount());

    while (inputPlugin->hasNext()) {
      std::shared_ptr<LennaImage> img = inputPlugin->next();
      ImageProcessor *imageProcessor = new ImageProcessor(img);
      threadPool.start(imageProcessor);

      emit process(inputPlugin->getProgress());
      if (stopped) {
        emit process(100);
        break;
      }
    }
    threadPool.waitForDone();
    if (stopped) {
      break;
    }
  }
  finish();
  emit finished();
}

void Worker::stop() { this->stopped = true; }

void Worker::finish() {
  emit process(100);
  foreach (std::shared_ptr<OutputPlugin> outputPlugin,
           PluginLoader::getInstance().getActiveOutputPlugins()) {
    outputPlugin->finnish();
  }
}
