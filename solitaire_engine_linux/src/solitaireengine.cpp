// solitaireengine.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "constants.h"
#include "gameplay/engine.h"
#include "communication/command_result.h"
#include "communication/command.h"
#include "communication/response.h"

// TODO: Delete all print() methods from classes as they are only used for debugging
// TODO: Alternatively, switch these print methods into log messages for easier debugging which can be turned off in deployment

void signalHandler(int signum) {
  _LOG_CLOSE;
  exit(signum);  
}

int main(int argc, char* argv[])
{
  // Handle terminations
  signal(SIGINT, signalHandler);

  // Enable logging if debug
  if(argc == 2 && std::string(argv[1]) == "--debug") {
    _LOG_ENABLE(true);
  }

  try {
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
  } catch (std::exception& e) {
    std::stringstream error;
    error << "Uncaught exception: " << e.what();
    _LOG_ERROR(error.str());
  }

  return 0;
}
