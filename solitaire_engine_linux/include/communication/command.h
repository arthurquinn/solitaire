#pragma once
#include "constants.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Command
{
private:
  std::string method;
  size_t src;
  size_t src_idx;
  size_t dest;
  
public:
  Command(const std::string& cmd);
  ~Command();

  // Access stripped command elemends
  const std::string get_method() const;
  const size_t get_src() const;
  const size_t get_src_idx() const;
  const size_t get_dest() const;
};
