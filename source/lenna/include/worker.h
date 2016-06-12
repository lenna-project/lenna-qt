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
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
namespace lenna{
class Worker : public QObject
{
    Q_OBJECT
public:
    Worker();
    ~Worker();

public slots:
    void process();
    void stop();

signals:
    void finished();
    void process(int value);

private:
    bool stopped;

    void finish();

};
}

#endif // WORKER_H
