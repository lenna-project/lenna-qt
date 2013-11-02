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

#include "loggerdialog.h"
#include "ui_loggerdialog.h"
#include <QtCore/QStringList>
#include <QtCore/QStringBuilder>
#include "logger.h"

LoggerDialog::LoggerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoggerDialog)
{
    ui->setupUi(this);
    setText(ui->messagesTextBrowser, Logger::getMessages());
    setText(ui->infoTextBrowser, Logger::getInfoMessages());
    setText(ui->debugTextBrowser, Logger::getDebugMessages());
    setText(ui->warningTextBrowser, Logger::getWarningMessages());
    setText(ui->criticalTextBrowser, Logger::getCriticalMessages());
    setText(ui->fatalTextBrowser, Logger::getFatalMessages());
}

LoggerDialog::~LoggerDialog()
{
    delete ui;
}

void LoggerDialog::setText(QTextBrowser *textBrowser, QStringList list){
    QString text;
    for(int i = 0; i < list.length(); i++){
        text.append(list.at(i)).append("\n");
    }
    textBrowser->setText(text);
}
