#ifndef CARMAKER_H
#define CARMAKER_H

#include "Queue.hpp"
#include "car.h"
#include "simulator.h"
#include <QDebug>
#include <QTimer>

struct Simulator;

class CarMaker : public QObject {
  Q_OBJECT
public:
  Simulator *sim;
  int restTime = 0;
  int minTime, maxTime;
  QTimer *timer;
  Queue<Car *> que;
  const int interval = 1000;

  CarMaker(int a, int b)
      : sim(nullptr), minTime(a), maxTime(b), timer(new QTimer(this)) {
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
  }

  void setSim(Simulator *p) { sim = p; }

  auto getQue() { return &que; }

  void start() { timer->start(); }

  void end() { timer->stop(); }

  void make() {
    que.enqueue(new Car);
    restTime = random(minTime, maxTime);
    qDebug() << "Car enqueue!";
  }

public slots:
  void check() {
    restTime--;
    if (restTime <= 0)
      make();
  }
};

#endif // CARMAKER_H
