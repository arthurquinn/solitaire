#pragma once
#include "constants.h"

class Utility
{
public:
  Utility();
  ~Utility();

  static const std::vector<std::string> split(const std::string str, const char delimeter);
  static const std::string get_datetime(const char* format, const bool get_ms);
  static const bool create_folder(const char* folder_path);
};
