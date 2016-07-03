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

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <lenna/image.h>

#include <memory>

#include <QRunnable>


namespace lenna {

class ImageProcessor : public QRunnable {
 public:
  ImageProcessor(std::shared_ptr<LennaImage> img);

 protected:
  void run();

 private:
  std::shared_ptr<LennaImage> image;
  void edit(std::shared_ptr<LennaImage> image);
  void out(std::shared_ptr<LennaImage> image);
};
}

#endif  // IMAGEPROCESSOR_H
