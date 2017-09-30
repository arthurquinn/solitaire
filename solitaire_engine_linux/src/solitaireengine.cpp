// solitaireengine.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "constants.h"
#include "gameplay/engine.h"
#include "communication/command_result.h"
#include "communication/command.h"
#include "communication/response.h"

// TODO: Delete all print() methods from classes as they are only used for debugging
// TODO: Alternatively, switch these print methods into log messages for easier debugging which can be turned off in deployment

int main(int argc, char* argv[])
{
  // Enable logging if debug
  if(argc == 2 && std::string(argv[1]) == "--debug") {
    Logger::getInstance().enable_logging(true);
  }

  // Start game
  _LOG_INFO("Logging start.");
  Engine engine;
  engine.init();
  CommandResult deal = engine.deal();
  const std::string deal_str = deal.stringify();

  std::cout << deal_str << std::endl;
  _LOG_INFO("Deal: " + deal_str);

  for (std::string line; std::getline(std::cin, line);) {
    Command cmd(line);
    _LOG_INFO("Received: " + line);
    CommandResult cr = engine.run(cmd);
    const std::string response = cr.stringify();
    std::cout << response << std::endl;
    _LOG_INFO("Written: " + response);
  }

  return 0;
}
