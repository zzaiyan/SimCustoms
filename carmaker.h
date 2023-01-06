#ifndef CARMAKER_H
#define CARMAKER_H

#include "Queue.hpp"
#include "car.h"
#include "screen.h"
#include "simulator.h"
#include <QDebug>
#include <QString>
#include <QTimer>
#include <vector>
using std::vector;

struct Simulator;
class Home;
class Screen;

class CarMaker : public QObject {
  Q_OBJECT

public:
  Simulator *sim;
  int restTime = 0;
  int minTime, maxTime;
  int queNum = 1; // 队伍数（1或k）
  QTimer *timer;
  Screen *screen;
  vector<Queue<Car *>> ques;
  const int interval = 1000;

  int carCnt = 0;
  //  int localTime = 0;

  CarMaker(int a, int b, Simulator *s, Screen *p)
      : sim(s), minTime(a), maxTime(b), timer(new QTimer(this)), screen(p) {
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
  }

  ~CarMaker() {}

  void setQueNum(int m) {
    queNum = m;
    ques.resize(m);
  }

  void setSim(Simulator *p) { sim = p; }

  auto getQues() { return &ques; } // Pass by Pointer of Vector

  int minQue() { // Get the index of Que with min size
    QString buf("Ques: ");
    for (int i = 0; i < queNum; i++)
      buf.append(QString("%1 ").arg(ques.at(i).size()));
    qDebug() << buf;

    int m = 0;
    for (int i = 0; i < queNum; i++)
      if (ques.at(i).size() < ques.at(m).size())
        m = i;
    return m; // 0 ~ n-1
  }

  void start() {
    timer->start();
    qDebug() << "CarMaker.start();";
  }

  void end() {
    timer->stop();
    qDebug() << "CarMaker.end();";
  }

  void make(); // 重置倒计时，生成车辆，加入当前最短的队列

public slots:
  void check() {
    qDebug() << "————CarEvent";
    //    localTime++; // 时间戳
    restTime--; // 生成倒计时
    if (restTime <= 0)
      make();
  }
};

#endif // CARMAKER_H
