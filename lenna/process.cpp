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

#include "process.h"
#include "plugins/pluginloader.h"
#include "imageprocessor.h"
#include <QtCore/QThread>
#include <QtCore/QThreadPool>

Process::Process(QObject *parent) :
    QThread(parent)
{
    stopped = true;
}

void Process::run(){
    stopped = false;
    emit process(0);
    foreach(InputPlugin *inputPlugin, PluginLoader::getInstance().getInputPlugins()){
        if(PluginLoader::getInstance().isActivatedPlugin(inputPlugin)){
            inputPlugin->init();
            QThreadPool threadPool(this);
            threadPool.setMaxThreadCount(QThread::idealThreadCount());

            while(inputPlugin->hasNext()){
                Image *img = inputPlugin->next();
                ImageProcessor *imageProcessor = new ImageProcessor(img);
                threadPool.start(imageProcessor);

                emit process(inputPlugin->getProgress());
                if(stopped){
                    emit process(100);
                    return;
                }
            }
            threadPool.waitForDone();
        }
    }
    finnish();
}

void Process::stop(){
    this->stopped = true;
}

void Process::finnish(){
    emit process(100);
    foreach(OutputPlugin *outputPlugin, PluginLoader::getInstance().getOutputPlugins()){
        if(stopped){
            return;
        }
        if(PluginLoader::getInstance().isActivatedPlugin(outputPlugin)){
            outputPlugin->finnish();
        }
    }
}
