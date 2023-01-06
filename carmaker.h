#ifndef CARMAKER_H
#define CARMAKER_H

#include "Queue.hpp"
#include "car.h"
#include "simulator.h"
#include <QDebug>
#include <QTimer>
#include <vector>
using std::vector;

struct Simulator;

class CarMaker : public QObject {
  Q_OBJECT
public:
  Simulator *sim;
  int restTime = 0;
  int minTime, maxTime;
  int panelSize = 1; // 队伍数（1或k）
  QTimer *timer;
  vector<Queue<Car *>> ques;
  const int interval = 1000;

  CarMaker(int a, int b)
      : sim(nullptr), minTime(a), maxTime(b), timer(new QTimer(this)) {
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
  }

  ~CarMaker() {}

  void setSim(Simulator *p) { sim = p; }

  auto &getQues() { return ques; } // Pass by Reference of Vector

  auto minQue() { // Get the index of Que with min size
    int m = 0;
    for (int i = 1; i < panelSize; i++)
      if (ques.at(i).size() < ques.at(m).size())
        m = i;
    return m;
  }

  void start() { timer->start(); }

  void end() { timer->stop(); }

  void make() { // 重置倒计时，生成车辆，加入当前最短的队列
    if (panelSize == 1) {
      ques.front().enqueue(new Car);
      restTime = random(minTime, maxTime);
      qDebug() << "Car Join Panel 1";
    } else {
      auto index = minQue();
      ques.at(index).enqueue(new Car);
      qDebug() << "Car Join Panel" << index + 1;
    }
  }

public slots:
  void check() {
    restTime--;
    if (restTime <= 0)
      make();
  }
};

#endif // CARMAKER_H
