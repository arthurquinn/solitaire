#include "stdafx.h"
#include "logger.h"

Logger Logger::instance;

Logger::Logger(const char *file_name): num_errors(0U), num_warnings(0U) {
  #ifdef _DEBUG
    std::string datetime_name = Utility::get_datetime("%m%d%Y%H%M%S", false);
    std::string datetime_text = Utility::get_datetime("%m/%d/%Y %H:%M:%S", true);
    const std::string full_path = "./Logs/" + std::string(file_name) + std::string("_") + datetime_name + ".log";
    log_file.open(full_path);

    if (log_file.is_open()) {
      log_file << "Solitaire Engine " << datetime_text << std::endl << std::endl;
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
    std::string datetime = Utility::get_datetime("%H:%M:%S", true);

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

Logger& Logger::getInstance() {
  return instance;
}
