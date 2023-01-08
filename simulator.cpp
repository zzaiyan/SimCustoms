#include "simulator.h"

Simulator::Simulator(int k, int c, int d, Screen *p)
    : panels(k, {c, d}), timer(new QTimer(this)), screen(p) {
  timer->setInterval(inertval);
  connect(timer, SIGNAL(timeout()), this, SLOT(upEvent()));

  for (int i = 0; i < k; i++) // init Panel's Index
    panels.at(i).num = i + 1;
}

void Simulator::check() {
  for (auto &pa : panels) { // 处理已完成车辆
                            //      pa.updata();
    if (pa.check()) {       // 若恰好结束
      auto car = pa.car;
      pa.end();                    // 更新状态
      car->timeToPass = localTime; // update timeToPass

      qDebug() << QString("[%1] 车辆 %2 通过检查，离开通道 %3，排队时间 %4 s"
                          "，通过时间 %5 s.")
                      .arg(localTime)
                      .arg(car->num)
                      .arg(pa.num)
                      .arg(car->waitTime())
                      .arg(car->passTime());
      screen->setPanel(pa.num - 1, 0);

//      car->print();

      dest.push_back(car);

      screen->markDest(car->waitTime(), car->passTime());
    }
  }

  if (queNum == 1) {
    auto que = ques->begin();              // 迭代器
    for (auto &pa : panels)                // 遍历所有检查通道
      if (pa.empty() && que->size() > 0) { // 若有通道空闲，且有车排队
        pa.join(que->dequeue());           // 队首车辆进入通道
        pa.car->timeToPanel = localTime;   // update timeToPanel
        qDebug() << QString(
                        "[%1] 车辆 %2 进入检查通道 %3 开始检查，排队时间 %4 s")
                        .arg(localTime)
                        .arg(pa.car->num)
                        .arg(pa.num)
                        .arg(pa.car->waitTime());
        screen->setPanel(pa.num - 1, pa.car->num);
        screen->setQueue(0, que->size());
      }
  } else {
    for (int i = 0; i < queNum; i++) { // 遍历所有队列
      auto que = &ques->at(i);
      auto pa = &panels.at(i);
      if (que->size() > 0 && pa->empty()) {
        pa->join(que->dequeue());
        pa->car->timeToPanel = localTime; // update timeToPanel
        qDebug() << QString(
                        "[%1] 车辆 %2 进入检查通道 %3 开始检查，排队时间 %4 s")
                        .arg(localTime)
                        .arg(pa->car->num)
                        .arg(pa->num)
                        .arg(pa->car->waitTime());
        screen->setPanel(pa->num - 1, pa->car->num);
        screen->setQueue(pa->num - 1, que->size());
      }
    }
  }
}
