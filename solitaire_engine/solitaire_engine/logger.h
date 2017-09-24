#pragma once
#include "utility.h"

enum class LogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

class Logger
{
private:
  static Logger* Logger::instance;

  std::ofstream log_file;

  unsigned int num_warnings;
  unsigned int num_errors;

public:
  explicit Logger(const char *file_name = "solitaire");
  ~Logger();

  const void log(const LogType type, const char *text);

  // Make it non-copyable
  Logger(const Logger& logger) = delete;
  Logger &operator= (const Logger& logger) = delete;

  // Singleton
  static Logger* getInstance();
};
