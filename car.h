#ifndef CAR_H
#define CAR_H

#include <random>
#define random(a, b) (rand() % (b - a + 1) + a);

struct Car {
public:
  Car() = default;

  int waitTime = 0;
  int panel = -1;
  int status = 0; // 0:排队, 1:处理, 2:离开
};

#endif // CAR_H
