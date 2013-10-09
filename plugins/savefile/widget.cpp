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
#include <QDir>
#include <QFileDialog>
#include <QImageWriter>
#include <QSettings>

using namespace lenna::plugin;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initFolder();
    initImageFormats();
    loadState();
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
    settings.beginGroup("SaveFile");

    ui->formatComboBox->setCurrentIndex(
                ui->formatComboBox->findText(settings.value("ImageFormat", "jpg").toString()));
    ui->metadataCheckBox->setChecked(settings.value("CopyMetaData", true).toBool());
    ui->qualityCheckBox->setChecked(settings.value("ChangeQuality", false).toBool());
    ui->qualitySpinBox->setValue(settings.value("Quality", 0).toInt());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("SaveFile");

    settings.setValue("ChangeQuality", ui->qualityCheckBox->isChecked());
    settings.setValue("Quality", ui->qualitySpinBox->value());
    settings.setValue("CopyMetaData", ui->metadataCheckBox->isChecked());
    settings.setValue("ImageFormat", ui->formatComboBox->currentText());
}

void Widget::initFolder(){
#if defined(Q_OS_WIN)
    ui->folderLineEdit->setText(QDir::homePath()+"/Pictures");
#elif defined(Q_OS_MAC)
    ui->folderLineEdit->setText(QDir::homePath());
#elif defined(Q_OS_LINUX)
    ui->folderLineEdit->setText(QDir::homePath());
#else
    ui->folderLineEdit->setText(QDir::homePath());
#endif
}

void Widget::initImageFormats(){
    foreach(const QByteArray &fmt, QImageWriter::supportedImageFormats()){
        ui->formatComboBox->addItem(QString(fmt));
    }
}

void Widget::on_selectFolderPushButton_clicked()
{
    QString folder = ui->folderLineEdit->text();
    folder = QFileDialog::getExistingDirectory(this, tr("Please select directory where images will saved to."), folder);
    if(!folder.isEmpty() && QDir(folder).exists())
        ui->folderLineEdit->setText(folder);
}
// returns 0 if not chosen
int Widget::getImageQuality(){
    if(ui->qualityCheckBox){
        return ui->qualitySpinBox->value();
    }else{
        return 0;
    }
}

QString Widget::getImageFormat(){
    return ui->formatLineEdit->text();
}

bool Widget::getCopyMetaData(){
    return ui->metadataCheckBox->isChecked();
}

QString Widget::getFolder(){
    return ui->folderLineEdit->text();
}
