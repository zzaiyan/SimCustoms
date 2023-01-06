#ifndef PANEL_H
#define PANEL_H

#include "car.h"
#include <QDebug>
#include <ctime>

struct Panel {
  bool isUsing = false;
  Car *car = nullptr;
  int restTime = 0;
  int minTime, maxTime;
  int num = -1;

  //  int localTime = 0;

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
    //    car->timeToPanel = localTime;
    car->status = 1;
    isUsing = true;
    restTime = random(minTime, maxTime);
  }

  void end() {
    car->status = 2;
    //    car->timeToPass = localTime;
    car = nullptr;
    isUsing = false;
  }

  void updata() { // 结束时返回1，否则返回0
    if (isUsing) {
      //      localTime++;

      restTime--;
      //      if (restTime <= 0) {
      //        //        end();
      //        return true;
      //      }
    }
    //    return false;
  }
  bool check() { return isUsing && restTime <= 0; }
};

#endif // PANEL_H
