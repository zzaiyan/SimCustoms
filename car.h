#ifndef CAR_H
#define CAR_H

#include <QDebug>
#include <random>
#define random(a, b) (rand() % (b - a + 1) + a);

struct Car {
public:
  Car(int n, int time) : num(n), timeToQue(time) {}

  int waitTime() {
    if (status >= 1)
      return timeToPanel - timeToQue;
    return -114514;
  }
  int passTime() {
    if (status >= 2)
      return timeToPass - timeToPanel;
    return -114514;
  }

  void print() {
    qDebug() << QString("车辆 %1: [%2, %3, %4], 状态: %5")
                    .arg(num)
                    .arg(timeToQue)
                    .arg(timeToPanel)
                    .arg(timeToPass)
                    .arg(status);
  }

  int num;                // 编号
  int timeToQue = -123;   // 开始排队
  int timeToPanel = -333; // 开始检查
  int timeToPass = -555;  // 检查完成
  int panel = -1;
  int status = 0; // 0:排队, 1:处理, 2:离开
};

#endif // CAR_H
