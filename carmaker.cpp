#include "carmaker.h"

void CarMaker::make() { // 重置倒计时，生成车辆，加入当前最短的队列
  restTime = random(minTime, maxTime);

  auto car = new Car(++carCnt, sim->localTime); // make Car, then enQueue

  if (queNum == 1) {
    ques.front().enqueue(car);

    qDebug() << QString("[%1] 车辆 %2 进入 共享队伍 排队")
                    .arg(sim->localTime)
                    .arg(car->num);
    screen->setQueue(0, ques.front().size());
  } else {
    auto index = minQue();
    ques.at(index).enqueue(car);

    qDebug() << QString("[%1] 车辆 %2 进入 队伍 %3 排队")
                    .arg(sim->localTime)
                    .arg(car->num)
                    .arg(index + 1);
    screen->setQueue(index, ques.at(index).size());
  }
  sim->check(); // 手动调用刷新
}
