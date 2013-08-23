#ifndef LENNA_H
#define LENNA_H

#include <QObject>
#include <QtCore/QTranslator>
#include <QtGui/QIcon>

class Lenna : public QObject
{
public:

    static void setApplicationName(QString name);
    static void setApplicationVersion(QString version);
    static void setOrganizationName(QString organization_name);

    static QString applicationName();
    static QString applicationVersion();
    static QString organizationName();
    static QIcon applicationIcon();

    static QString applicationDirPath();

    static void installTranslator(QTranslator *file);

    static void destroy();

signals:

public slots:
};

#endif // LENNA_H
