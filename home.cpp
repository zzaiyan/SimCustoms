#include "home.h"
#include "Queue.hpp"
#include "ui_home.h"
#include <QDebug>

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  this->setFixedSize(this->size());

  int a, b, c, d, k;
  a = 1, b = 3, c = 2, d = 4, k = 4;

  // CarMaker：定时生成车辆至que队列
  // Simulator：处理que中车辆

  maker = new CarMaker(a, b);
  sim = new Simulator(k, c, d);
  maker->setSim(sim);
  sim->setQue(maker->getQue());

  maker->start();
  sim->start();
}

Home::~Home() { delete ui; }
