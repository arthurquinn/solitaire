// solitaireengine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "engine.h"
#include "constants.h"
#include "command_result.h"


/// TODO: Delete all print() methods from classes as they are only used for debugging
/// TODO: Alternatively, switch these print methods into log messages for easier debugging which can be turned off in deployment

int main()
{
  Engine engine;
  engine.init();
  engine.deal();
  
  std::cout << std::endl;
  
  CommandResult cr(true, "bad stuff");
  cr.update_push(0, "cq");
  cr.update_push(0, "ck");
  cr.update_push(0, "ca");
  cr.update_pop(0, 4);
  cr.update_push(1, "hq");
  cr.update_push(0, "hk");
  cr.update_pop(1, 5);
  const std::string str = cr.stringify();
  std::cout << str << std::endl;
  std::cin.get();
  return 0;
}