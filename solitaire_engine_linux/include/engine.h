#include <iostream>
#include <vector>
#include "stock.h"

class Engine
{
private:
  Stock stock;
public:
  Engine();
  void init();
  void deal();
  void run();
  ~Engine();
};

