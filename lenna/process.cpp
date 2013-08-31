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
