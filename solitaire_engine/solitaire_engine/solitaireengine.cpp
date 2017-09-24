// solitaireengine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "engine.h"
#include "constants.h"
#include "command_result.h"
#include "command.h"
#include "response.h"
#include "logger.h"

// TODO: Delete all print() methods from classes as they are only used for debugging
// TODO: Alternatively, switch these print methods into log messages for easier debugging which can be turned off in deployment

int main()
{
  Logger::getInstance()->log(LogType::LOG_WARNING, "Test warning.");

  //std::cout << "Running..." << std::endl;

  Engine engine;
  engine.init();
  engine.deal();
  std::cout << Response::make_response(ENGINE_RESPONSE_READY) << std::endl;

  // TODO: Fix error thrown somewhere in here after pressing a key
  /*for (std::string line; std::getline(std::cin, line);) {
    Command cmd(line);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << cmd.get_method() << cmd.get_dest() << cmd.get_src() << cmd.get_src_idx() << std::endl;
    CommandResult* cr = engine.run(cmd);
    std::cout << cr->stringify() << std::endl;
    delete cr;
  }*/

  Command cmd1("{\"cmd\": \"move\", \"src\": 1, \"src_idx\": 0, \"dest\": 7}");
  CommandResult* cr = engine.run(cmd1);
  std::cout << cr->stringify() << std::endl;
  delete(cr);


  //std::cout << "Exiting..." << std::endl;
  std::cin.get();
  //std::cout << std::endl;

  //CommandResult cr(true, "bad stuff");
  //cr.update_push(0, "cq");
  //cr.update_push(0, "ck");
  //cr.update_push(0, "ca");
  //cr.update_pop(0, 4);
  //cr.update_push(1, "hq");
  //cr.update_push(0, "hk");
  //cr.update_pop(1, 5);
  //const std::string str = cr.stringify();
  //std::cout << str << std::endl;
  //std::cin.get();
  return 0;
}