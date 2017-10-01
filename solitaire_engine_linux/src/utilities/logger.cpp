#include "stdafx.h"
#include "utilities/logger.h"

Logger Logger::instance;

Logger::Logger(): num_errors(0), num_warnings(0) {
  enabled = false;
}

const void Logger::initialize() {
  if(enabled && Utility::create_folder(LOG_FOLDER)) {
    std::string datetime_name = Utility::get_datetime("%m%d%Y%H%M%S", false);
    std::string datetime_text = Utility::get_datetime("%m/%d/%Y %H:%M:%S", true);

    const std::string full_path = std::string(LOG_FOLDER) + std::string(LOG_FILE) + std::string("_") + datetime_name + ".log";
    log_file.open(full_path, std::ofstream::binary);

    if (log_file.is_open()) {
      log_file << "Solitaire Engine " << datetime_text << NEW_LINE << NEW_LINE;
    }
  }
}

const void Logger::log(const LogType type, std::string text) {
  if(enabled && !log_file.is_open()) {
    initialize();
  }

  if (enabled && log_file.is_open()) {
    std::string datetime = Utility::get_datetime("%H:%M:%S", true);

    switch (type) {
    case LogType::LOG_ERROR:
      log_file << datetime << " [ERROR]: " << text << NEW_LINE;
      num_errors++;
      break;

    case LogType::LOG_WARNING:
      log_file << datetime << " [WARNING]: " << text << NEW_LINE;
      num_warnings++;
      break;

    default:
      log_file << datetime << " [INFO]: " << text << NEW_LINE;
      break;
    }
  }
}

const void Logger::close() {
  if (enabled && log_file.is_open()) {
    _LOG_INFO("Logging end.");
    log_file << NEW_LINE;

    log_file << num_warnings << " warnings" << NEW_LINE;
    log_file << num_errors << " errors" << NEW_LINE;

    log_file.close();
  }
}

const void Logger::enable_logging(const bool is_enabled) {
  enabled = is_enabled;
}

Logger& Logger::getInstance() {
  return instance;
}

Logger::~Logger() {}
