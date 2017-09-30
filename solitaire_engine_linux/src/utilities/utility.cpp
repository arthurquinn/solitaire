#include "stdafx.h"
#include "utilities/utility.h"

Utility::Utility() {}
Utility::~Utility() {}

const std::vector<std::string> Utility::split(const std::string str, const char delimeter) {
  std::vector<std::string> result;

  if (str != NO_REASON && str != EMPTY_RESPONSE) {
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
  struct tm* timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  
  // Convert time to string with given format
  std::ostringstream oss;
  oss << std::put_time(timeinfo, format);
  std::string str = oss.str();
  
  // Add ms if wanted
  if (get_ms) {
    long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    str += ":" + std::to_string(ms);
  }

  return str;
}

const bool Utility::create_folder(const char* folder_path) {
  bool is_created = false;

  #ifdef __linux__
    struct stat info;
    stat(folder_path, &info);

    if(info.st_mode & S_IFDIR) {
      is_created = true;
    }
    else {
      mkdir(folder_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      is_created = true;
    }
  #endif

  return is_created;
}
