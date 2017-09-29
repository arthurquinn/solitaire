#pragma once
#include "utility.h"

#define _LOG_INFO(msg) Logger::getInstance().log(LogType::LOG_INFO, msg)
#define _LOG_WARNING(msg) Logger::getInstance().log(LogType::LOG_WARNING, msg)
#define _LOG_ERROR(msg) Logger::getInstance().log(LogType::LOG_ERROR, msg)

enum class LogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

class Logger
{
private:
  static Logger instance;

  std::ofstream log_file;

  unsigned int num_warnings;
  unsigned int num_errors;

public:
  explicit Logger(const char *file_name = "solitaire");
  ~Logger();

  const void log(const LogType type, std::string text);

  // Make it non-copyable
  Logger(const Logger& logger) = delete;
  Logger &operator= (const Logger& logger) = delete;

  // Singleton
  static Logger& getInstance();
};
