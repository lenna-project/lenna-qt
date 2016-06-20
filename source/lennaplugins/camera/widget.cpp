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

#include "widget.h"
#include "ui_widget.h"
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtWidgets/QFileDialog>
#include <QtGui/QImageReader>
#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace lenna::plugin::camera;
using namespace cv;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    listCameras();
}

Widget::~Widget()
{
    delete ui;
}

int Widget::getFrames(){
    return ui->framesSpinBox->value();
}

void Widget::listCameras(){

    for(int device = 0; device<3; device++)
    {
        VideoCapture cap(device);
        if (!cap.isOpened())
            return;
        ui->camerasComboBox->addItem(QString("device %1").arg(device));
    }

}

int Widget::selectedDevice(){
    return ui->camerasComboBox->currentIndex();
}

void Widget::on_cameraOnCheckBox_toggled(bool checked)
{
    int key;
    CvCapture *camera;
    Mat frame;
    camera = cvCaptureFromCAM(selectedDevice());
    cvNamedWindow("Camera", 0);
    while(ui->cameraOnCheckBox->isChecked()){
        frame = cv::cvarrToMat(cvQueryFrame(camera), true);
        if(!frame.empty())
            imshow( "Camera", frame );
        key = cvWaitKey(10);
        if(key == 27 /* ESC */)
            break;
    }
    cvReleaseCapture(&camera);
    cvDestroyWindow("Camera");
}
