/**
    This file is part of program Lenna which is released under MIT License.
    See file LICENSE or go to https://github.com/lenna-project/lenna for full license details.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class Widget;
}

namespace lenna {
namespace plugin {

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

  bool isBlur();
  std::string getTime();
  std::string getDate();

 private slots:

 private:
  Ui::Widget *ui;
  void loadState();
  void saveState();

  void timestamp(QImage *image);
};
}  // namespace plugin
}  // namespace lenna

#endif  // WIDGET_H
