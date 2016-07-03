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

#include "imageprocessor.h"
#include "process.h"

#include <plugins/pluginloader.h>

using namespace lenna;
using namespace lenna::plugin;

ImageProcessor::ImageProcessor(std::shared_ptr<LennaImage> img) {
  this->image = img;
}

void ImageProcessor::run() {
  edit(image);
  out(image);
}

void ImageProcessor::edit(std::shared_ptr<LennaImage> image) {
  foreach (EditPlugin *editPlugin,
           PluginLoader::getInstance().getEditPlugins()) {
    if (PluginLoader::getInstance().isActivatedPlugin(editPlugin)) {
      editPlugin->edit(image);
    }
  }
}

void ImageProcessor::out(std::shared_ptr<LennaImage> image) {
  foreach (OutputPlugin *outputPlugin,
           PluginLoader::getInstance().getOutputPlugins()) {
    if (PluginLoader::getInstance().isActivatedPlugin(outputPlugin)) {
      outputPlugin->out(image);
    }
  }
}
