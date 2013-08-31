#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "image.h"
#include <QRunnable>

class ImageProcessor : public QRunnable
{
public:
    ImageProcessor(Image *img);
protected:
    void run();

private:
    Image *image;
    void edit(Image *image);
    void out(Image *image);

};

#endif // IMAGEPROCESSOR_H
