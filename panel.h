#ifndef PANEL_H
#define PANEL_H

#include "car.h"
#include <QDebug>

struct Panel {
  bool isUsing = false;
  Car *car = nullptr;
  int restTime = 0;
  int minTime, maxTime;

public:
  Panel(int a, int b) : minTime(a), maxTime(b) {}

  bool empty() { return !isUsing; }

  //  void setTime(int a, int b) { minTime = a, maxTime = b; }

  void join(Car *c) {
    if (isUsing) {
      qDebug() << "Try to Join when is using!";
      exit(1);
    }
    car = c;
    car->status = 1;
    isUsing = true;
    restTime = random(minTime, maxTime);
  }

  void end() {
    car->status = 2;
    car = nullptr;
    isUsing = false;
  }

  bool updata() { // 结束时返回1，否则返回0
    if (isUsing) {
      car->waitTime++;
      restTime--;
      if (restTime <= 0) {
        //        end();
        return true;
      }
    }
    return false;
  }
};

#endif // PANEL_H
