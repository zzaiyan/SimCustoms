#ifndef HOME_H
#define HOME_H

#include "carmaker.h"
#include "simulator.h"
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

private:
  Ui::Home *ui;
  Simulator *sim;
  CarMaker *maker;
};
#endif // HOME_H
