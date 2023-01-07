#ifndef HOME_H
#define HOME_H

#include "screen.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
  Q_OBJECT

public:
  Home(QWidget *parent = nullptr);
  ~Home();

private slots:
  void on_setBtn_clicked();

private:
  Ui::Home *ui;
  Screen *screen;
};
#endif // HOME_H
