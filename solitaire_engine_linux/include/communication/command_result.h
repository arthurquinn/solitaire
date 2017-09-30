#pragma once
#include "constants.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

typedef std::map<const size_t, std::vector<std::string>> push_map_t;
typedef std::map<const size_t, size_t> pop_map_t;

class CommandResult {
private:
  const bool status;
  const std::string reason;
  push_map_t push_map;
  pop_map_t pop_map;
  
public:
  CommandResult(const bool status, const std::string reason);
  ~CommandResult();

  void update_push(const size_t pile, const std::string card_str);
  void update_pop(const size_t pile, const size_t pop_num);
  const std::string stringify();
};
