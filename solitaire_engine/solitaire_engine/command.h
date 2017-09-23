#pragma once
#include "constants.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Command
{
private:
  std::string method;
  int src;
  int src_len;
  int dest;

public:
  Command(const std::string& cmd);

  // Access stripped command elemends
  const std::string get_method();
  const int get_src();
  const int get_src_len();
  const int get_dest();

  ~Command();
};

