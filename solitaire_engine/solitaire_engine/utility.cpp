#include "stdafx.h"
#include "utility.h"

Utility::Utility() {}
Utility::~Utility() {}

std::vector<const char*> Utility::split(const std::string str, const char delimeter) {
  std::vector<const char*> result;

  if (str != NO_REASON) {
    std::istringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimeter)) {
      result.push_back(token.c_str());
    }
  }
  else {
    result.push_back("xx");
  }

  return result;
}

const std::string Utility::get_datetime(const char* format) {
  time_t rawtime;
  struct tm timeinfo;
  time(&rawtime);
  localtime_s(&timeinfo, &rawtime);

  std::ostringstream oss;
  oss << std::put_time(&timeinfo, format);
  std::string str = oss.str();
  
  return str;
}

const void Utility::create_folder(const char* folder_path) {
  // TODO: Cross platform way to create directory if it doesn't exist
}