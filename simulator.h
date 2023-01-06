#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Queue.hpp"
#include "panel.h"
#include "screen.h"
#include <QTimer>
#include <vector>
using std::vector;

class CarMaker;
class Home;
class Screen;

struct Simulator : QObject { // k条通道，耗时c到d分钟
  Q_OBJECT

  vector<Panel> panels;
  vector<Car *> dest;
  vector<Queue<Car *>> *ques;
  QTimer *timer;
  Screen *screen;
  const int inertval = 1000;
  int queNum = 1;

public:
  int localTime = 0;

  Simulator(int k, int c, int d, Screen *p)
      : panels(k, {c, d}), timer(new QTimer(this)), screen(p) {
    timer->setInterval(inertval);
    connect(timer, SIGNAL(timeout()), this, SLOT(upEvent()));

    for (int i = 0; i < k; i++) // init Panel's Index
      panels.at(i).num = i + 1;
  }

public slots:
  void upEvent() {
    localTime++;
    qDebug() << "————SimEvent";
    upPanel();
    check();
  }

public:
  void upPanel() {
    for (auto &pa : panels) { // 处理已完成车辆
      pa.updata();
    }
  }

  void check();

  void setQue(vector<Queue<Car *>> *q) {
    ques = q;
    queNum = ques->size();
  }

  void start() {
    timer->start();
    qDebug() << "Simulator.start();";
  }

  void end() {
    timer->stop();
    qDebug() << "Simulator.end();";
  }

  void reset(int k, int c, int d) {
    end();

    for (auto &e : dest)
      delete e;

    dest.clear();

    for (auto e : panels)
      if (e.isUsing && e.car)
        delete e.car;

    panels = decltype(panels)(k, {c, d});
  }
};

#endif // SIMULATOR_H
