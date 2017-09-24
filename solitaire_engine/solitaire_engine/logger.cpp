#include "stdafx.h"
#include "logger.h"

Logger* Logger::instance = 0;

Logger::Logger(const char *file_name): num_errors(0U), num_warnings(0U) {
  #ifdef _DEBUG
    std::string datetime = Utility::get_datetime("%m%d%Y%H%M%S");
    const std::string full_path = "./Logs/" + std::string(file_name) + std::string("_") + datetime + ".log";
    log_file.open(full_path);

    if (log_file.is_open()) {
      log_file << "Solitaire Engine " << datetime << std::endl << std::endl;
    }
  #endif
}

Logger::~Logger() {
  if (log_file.is_open()) {
    log_file << std::endl;

    log_file << num_warnings << " warnings" << std::endl;
    log_file << num_errors << " errors" << std::endl;

    log_file.close();
  }
}

const void Logger::log(const LogType type, std::string text) {
  if (log_file.is_open()) {
    std::string datetime = Utility::get_datetime("%m/%d/%Y %H:%M:%S");

    switch (type) {
    case LogType::LOG_ERROR:
      log_file << datetime << " [ERROR]: " << text << std::endl;
      num_errors++;
      break;

    case LogType::LOG_WARNING:
      log_file << datetime << " [WARNING]: " << text << std::endl;
      num_warnings++;
      break;

    default:
      log_file << datetime << " [INFO]: " << text << std::endl;
      break;
    }
  }
}

const void Logger::close() {
  delete instance;
}

Logger* Logger::getInstance() {
  if (!instance) {
    instance = new Logger();
  }

  return instance;
}
