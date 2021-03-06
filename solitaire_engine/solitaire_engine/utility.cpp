#include "stdafx.h"
#include "utility.h"

Utility::Utility() {}
Utility::~Utility() {}

std::vector<std::string> Utility::split(const std::string str, const char delimeter) {
  std::vector<std::string> result;

  if (str != NO_REASON && str != EMPTY_LIST) {
    std::istringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimeter)) {
      result.push_back(token);
    }
  }
  else {
    result.push_back("");
  }

  return result;
}

const std::string Utility::get_datetime(const char* format, const bool get_ms) {
  time_t rawtime;
  struct tm timeinfo;
  time(&rawtime);
  localtime_s(&timeinfo, &rawtime);
  
  // Convert time to string with given format
  std::ostringstream oss;
  oss << std::put_time(&timeinfo, format);
  std::string str = oss.str();
  
  // Add ms if wanted
  if (get_ms) {
    __int64 ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    str += ":" + std::to_string(ms);
  }

  return str;
}

const void Utility::create_folder(const char* folder_path) {
  // TODO: Cross platform way to create directory if it doesn't exist
}
