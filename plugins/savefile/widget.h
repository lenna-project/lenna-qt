#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    int getImageQuality(); // returns 0 if not chosen
    QString getImageFormat();
    bool getCopyMetaData();
    QString getFolder();
    
private slots:
    void on_selectFolderPushButton_clicked();

private:
    Ui::Widget *ui;
    void loadState();
    void saveState();

    void initFolder();
    void initImageFormats();
};

#endif // WIDGET_H
