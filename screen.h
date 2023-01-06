#ifndef SCREEN_H
#define SCREEN_H

#include "carmaker.h"
#include "simulator.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>
using std::vector;

class Screen : public QWidget {
  Q_OBJECT

  struct Unit {
    QLabel *label;
    QLineEdit *edit;
    Unit(Screen *p) : label(new QLabel(p)), edit(new QLineEdit(p)) {
      edit->setAlignment(Qt::AlignCenter);
      edit->setText("空闲");
    }
  };

public:
  explicit Screen(const vector<int> &vec, QWidget *parent = nullptr);
  ~Screen();
  void build();

  void setPanel(int panelNum, int carNum);
  void setQueue(int queueNum, int carCnt);
  void markDest(int wait, int pass);

  CarMaker *maker;
  Simulator *sim;

  int a, b, c, d, k, mode; // 参数
  int carSum = 0, waitSum = 0, passSum = 0;

  vector<Unit *> panelVec;
  vector<Unit *> queueVec;
  Unit *passCar, *waitTime, *passTime;
  QGroupBox *panelGroup;
  QGroupBox *queueGroup;
  QGroupBox *resultGroup;

signals:
};

#endif // SCREEN_H
