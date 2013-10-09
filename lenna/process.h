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

#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>

namespace lenna{

class Process : public QThread
{
    Q_OBJECT
public:
    explicit Process(QObject *parent = 0);
    void stop();

signals:
    void process(int value);

public slots:
protected:
    void run();

private:
    bool stopped;
    void finnish();
    
};

}

#endif // PROCESS_H
