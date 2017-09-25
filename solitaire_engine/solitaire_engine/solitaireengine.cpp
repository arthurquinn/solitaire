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
  _LOG_INFO("Logging start.");
  Engine engine;
  engine.init();
  engine.deal();
  std::cout << Response::make_response(ENGINE_RESPONSE_READY) << std::endl;
  for (std::string line; std::getline(std::cin, line);) {
    Command cmd(line);
    _LOG_INFO("Received: " + line);
    std::cout << cmd.get_method() << cmd.get_dest() << cmd.get_src() << cmd.get_src_idx() << std::endl;
    CommandResult cr = engine.run(cmd);
    const std::string response = cr.stringify();
    std::cout << response << std::endl;
    _LOG_INFO("Written: " + response);
  }
  return 0;
}