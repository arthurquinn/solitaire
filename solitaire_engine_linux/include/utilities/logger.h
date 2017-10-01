#pragma once
#include "utility.h"

#define NEW_LINE            "\r\n"
#define LOG_FOLDER          "./logs/"
#define LOG_FILE            "solitaire"
#define _LOG_CLOSE          Logger::getInstance().close()
#define _LOG_ENABLE(val)    Logger::getInstance().enable_logging(val)
#define _LOG_INFO(msg)      Logger::getInstance().log(LogType::LOG_INFO, msg)
#define _LOG_WARNING(msg)   Logger::getInstance().log(LogType::LOG_WARNING, msg)
#define _LOG_ERROR(msg)     Logger::getInstance().log(LogType::LOG_ERROR, msg)

enum class LogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

class Logger
{
private:
  static Logger instance;

  std::ofstream log_file;

  size_t num_warnings;
  size_t num_errors;

  bool enabled;

public:
  explicit Logger();
  ~Logger();

  const void initialize();
  const void log(const LogType type, std::string text);
  const void enable_logging(const bool is_enabled);
  const void close();

  // Make it non-copyable
  Logger(const Logger& logger) = delete;
  Logger &operator= (const Logger& logger) = delete;

  // Singleton
  static Logger& getInstance();
};
