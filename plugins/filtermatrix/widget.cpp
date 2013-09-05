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
#include "filtermatrix.h"

#include <QtCore/QSettings>
#include <QtGui/QPainter>
#include <QtDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->previewImage = 0;
    ui->setupUi(this);

    previewImageLabel = new PreviewImageLabel(this);
    ui->imageGridLayout->addWidget(previewImageLabel);
    on_resetPushButton_clicked();

    loadState();
    connect(previewImageLabel, SIGNAL(imageDroped(QString)), this, SLOT(setPreviewImage(QString)));
    updateImage();
    ui->tableWidget->resizeColumnsToContents();
}

Widget::~Widget()
{
    saveState();
    delete ui;
}

void Widget::loadState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("FilterMatrix");
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("FilterMatrix");
}



void Widget::updateImage(){

    Image image = Image(*previewImage);

    if(ui->filterCheckBox->isChecked()){
        filter(&image);
    }
    this->previewImageLabel->setPixmap(QPixmap::fromImage(QImage(image.toQImage())));

}

void Widget::setPreviewImage(QString img){
        this->previewImageSrc = img;
        if(this->previewImage)
            delete this->previewImage;
        this->previewImage = new Image(img);
        updateImage();
}

void Widget::on_resetPushButton_clicked()
{
    setPreviewImage(QString(":/logo/lenna_logo"));
}

// Function blurs a rect of image by percentage
void Widget::filter(Image *image){
    cv::filter2D(image->getImage(), image->getImage(), -1, getFilter());
    image->getImage() = image->getImage()*255; // TODO why * 255?
}

bool Widget::isFilter(){
    return ui->filterCheckBox->isChecked();
}

Mat Widget::getFilter(){
    Mat filter = Mat::eye(ui->tableWidget->rowCount(),ui->tableWidget->columnCount(),CV_32S);
    for(int row = 0; row < ui->tableWidget->rowCount(); row++){
        for(int col = 0; col < ui->tableWidget->columnCount(); col++){

            //
            if( ui->tableWidget->item(row, col)!= 0){
                filter.at<int>(row, col) = ui->tableWidget->item(row, col)->text().toInt();

            }else {
                filter.at<int>(row, col) = 0;
            }
        }
    }
    return filter;
}

void Widget::on_addRowButton_clicked()
{
    ui->tableWidget->insertRow(0);
}

void Widget::on_removeRowButton_clicked()
{
    ui->tableWidget->removeRow(0);
}

void Widget::on_addColButton_clicked()
{
    ui->tableWidget->insertColumn(0);
}

void Widget::on_removeColButton_clicked()
{
    ui->tableWidget->removeColumn(0);
}
