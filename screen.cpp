#include "screen.h"

Screen::Screen(const vector<int> &vec, QWidget *parent) : QWidget{parent} {
  setAttribute(Qt::WA_DeleteOnClose, true);

  a = vec[0], b = vec[1], c = vec[2], d = vec[3], k = vec[4], mode = vec[5];

  build();

  // CarMaker：定时生成车辆至que队列
  // Simulator：处理que中车辆

  sim = new Simulator(k, c, d, this);
  maker = new CarMaker(a, b, sim, this);

  maker->setQueNum((mode == 0) ? 1 : k); // 队列数量
  sim->setQue(maker->getQues());
  sim->start();
  maker->start();
  for (long long i = 0; i < 123456; i++) {
    mode *= -1;
  }
}

void Screen::build() { // 构建界面
  this->setWindowTitle("离散事件模拟");

  auto vLayout = new QVBoxLayout; // 垂直布局 - 总体

  auto gridLayout = new QGridLayout; // 网格布局 - 检查窗口
  for (int i = 0; i < k; i++) {
    panelVec.push_back(new Unit(this));
    panelVec[i]->label->setText(QString("检查通道 %1 :").arg(i + 1));
    panelVec[i]->edit->setReadOnly(1);
    gridLayout->addWidget(panelVec[i]->label, i, 0);
    gridLayout->addWidget(panelVec[i]->edit, i, 1);
  }
  panelGroup = new QGroupBox;
  panelGroup->setLayout(gridLayout);
  panelGroup->setTitle("检查通道");

  gridLayout = new QGridLayout; // 网格布局 - 队列窗口
  if (mode == 0) {
    queueVec.push_back(new Unit(this));
    queueVec[0]->label->setText("共享等待队列 :");
    queueVec[0]->edit->setReadOnly(1);
    gridLayout->addWidget(queueVec[0]->label, 0, 0);
    gridLayout->addWidget(queueVec[0]->edit, 0, 1);
  } else {
    for (int i = 0; i < k; i++) {
      queueVec.push_back(new Unit(this));
      queueVec[i]->label->setText(QString("等待队列 %1 :").arg(i + 1));
      queueVec[i]->edit->setReadOnly(1);
      gridLayout->addWidget(queueVec[i]->label, i, 0);
      gridLayout->addWidget(queueVec[i]->edit, i, 1);
    }
  }
  queueGroup = new QGroupBox;
  queueGroup->setLayout(gridLayout);
  queueGroup->setTitle("等待队列");

  gridLayout = new QGridLayout; // 网格布局 - 结果窗口

  passCar = new Unit(this);
  passCar->label->setText("通过车辆总数 :");
  passCar->edit->setText("0");
  passCar->edit->setReadOnly(1);
  waitTime = new Unit(this);
  waitTime->label->setText("平均排队时间 :");
  waitTime->edit->setText("0");
  waitTime->edit->setReadOnly(1);
  passTime = new Unit(this);
  passTime->label->setText("平均通过时间 :");
  passTime->edit->setText("0");
  passTime->edit->setReadOnly(1);

  gridLayout->addWidget(passCar->label, 0, 0);
  gridLayout->addWidget(passCar->edit, 0, 1);
  gridLayout->addWidget(waitTime->label, 1, 0);
  gridLayout->addWidget(waitTime->edit, 1, 1);
  gridLayout->addWidget(passTime->label, 2, 0);
  gridLayout->addWidget(passTime->edit, 2, 1);

  resultGroup = new QGroupBox;
  resultGroup->setLayout(gridLayout);
  resultGroup->setTitle("结果汇总");

  vLayout->addWidget(panelGroup);
  vLayout->addWidget(queueGroup);
  vLayout->addWidget(resultGroup);

  this->setLayout(vLayout);
}

Screen::~Screen() {
  maker->end();
  sim->end();
}

void Screen::setPanel(int panelNum, int carNum) {
  if (carNum > 0)
    panelVec.at(panelNum)->edit->setText(
        QString("正在检查 车辆 %1").arg(carNum));
  else
    panelVec.at(panelNum)->edit->setText(QString("空闲"));
}

void Screen::setQueue(int queueNum, int carCnt) {
  if (carCnt > 0)
    queueVec.at(queueNum)->edit->setText(
        QString("当前有 %1 辆车在排队").arg(carCnt));
  else
    queueVec.at(queueNum)->edit->setText(QString("空闲"));
}

void Screen::markDest(int wait, int pass) {
  carSum++, waitSum += wait, passSum += pass;
  passCar->edit->setText(QString::number(carSum));
  waitTime->edit->setText(QString::number(1.0 * waitSum / carSum));
  passTime->edit->setText(QString::number(1.0 * passSum / carSum));
}
