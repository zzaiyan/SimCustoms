#include "home.h"
#include "Queue.hpp"
#include "ui_home.h"
#include <QDebug>

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  //  this->setFixedSize(this->size());
}

Home::~Home() { delete ui; }

void Home::on_setBtn_clicked() {
  auto li = ui->intputEdit->text().split(' ');
  vector<int> vec;
  for (auto &i : li)
    vec.push_back(i.toInt());
  vec.push_back(ui->comboBox->currentIndex());
  if (vec.size() != 6 || vec[2] < 1 || vec[3] < 1) {
    qDebug() << "数据非法！";
    return;
  }
  screen = new Screen(vec);
  screen->show();
}
