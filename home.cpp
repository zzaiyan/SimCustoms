#include "home.h"
#include "ui_home.h"
#include <QDebug>
#include <QMessageBox>

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  //  this->setFixedSize(this->size());
}

Home::~Home() { delete ui; }

void Home::on_setBtn_clicked() {
  vector<int> vec;

  auto li = ui->intputEdit->text().split(' ');
  for (auto &i : li)
    if (int tmp = i.toInt(); tmp != 0)
      vec.push_back(tmp);

  vec.push_back(ui->comboBox->currentIndex());

  if (vec.size() != 6) {
    qDebug() << "数据非法";
    QMessageBox::warning(nullptr, "警告", "数据非法！");
    return;
  }
  screen = new Screen(vec);
  screen->show();
}
