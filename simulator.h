#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Queue.hpp"
#include "panel.h"
#include <QTimer>
#include <vector>
using std::vector;

class CarMaker;

struct Simulator : QObject { // k条通道，耗时c到d分钟
  Q_OBJECT

  vector<Panel> panels;
  vector<Car *> dest;
  Queue<Car *> *que;
  QTimer *timer;
  const int inertval = 1000;

public:
  Simulator(int k, int c, int d) : panels(k, {c, d}), timer(new QTimer(this)) {
    timer->setInterval(inertval);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePanels()));
  }

public slots:
  void updatePanels() {
    qDebug() << "update";
    for (auto &pa : panels) {
      if (pa.updata()) { // 若恰好结束
        auto car = pa.car;
        pa.end();
        dest.push_back(car);
      }
    }
  }

public:
  void setQue(Queue<Car *> *q) { que = q; }

  void start() { timer->start(); }

  void end() { timer->stop(); }

  void reset(int k, int c, int d) {
    end();
    for (auto e : panels)
      if (e.isUsing && e.car)
        delete e.car;
    panels = decltype(panels)(k, {c, d});
  }
};

#endif // SIMULATOR_H
