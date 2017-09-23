#pragma once
#include "constants.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

typedef std::map<const int, std::vector<const char*>> push_map_t;
typedef std::map<const int, int> pop_map_t;

class CommandResult {
private:
  const bool status;
  const char* reason;
  push_map_t push_map;
  pop_map_t pop_map;
public:
  CommandResult(const bool status, const char* reason);
  void update_push(const int pile, const char* card_str);
  void update_pop(const int pile, const int pop_num);
  const std::string stringify();
  ~CommandResult();
};

