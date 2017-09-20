#include <stdio.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>
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
	~Engine();
};

