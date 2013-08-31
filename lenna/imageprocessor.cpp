#include "imageprocessor.h"
#include "process.h"
#include "plugins/pluginloader.h"
ImageProcessor::ImageProcessor(Image *img)
{
    this->image = img;
}

void ImageProcessor::run(){
    edit(image);
    out(image);
}

void ImageProcessor::edit(Image *image){
    foreach(EditPlugin *editPlugin, PluginLoader::getInstance().getEditPlugins()){
        if(PluginLoader::getInstance().isActivatedPlugin(editPlugin)){
            editPlugin->edit(image);
        }
    }
}

void ImageProcessor::out(Image *image){
    foreach(OutputPlugin *outputPlugin, PluginLoader::getInstance().getOutputPlugins()){
        if(PluginLoader::getInstance().isActivatedPlugin(outputPlugin)){
            outputPlugin->out(image);
        }
    }
}
