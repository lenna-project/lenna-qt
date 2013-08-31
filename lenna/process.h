#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>

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

#endif // PROCESS_H
