#pragma once
#include "constants.h"

class Utility
{
public:
  Utility();
  ~Utility();

  static std::vector<const char*> split(const std::string str, const char delimeter);
  static const std::string get_datetime(const char* format);
  static const void create_folder(const char* folder_path);
};
