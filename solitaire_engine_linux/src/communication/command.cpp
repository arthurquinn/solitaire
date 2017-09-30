#include "stdafx.h"
#include "communication/command.h"

using namespace rapidjson;

Command::Command(const std::string& raw_cmd) {
  const char* raw = raw_cmd.c_str();

  Document document;
  if (document.Parse(raw).HasParseError()) {
    method = COMMAND_PARSE_ERROR;
  }

  method = document["cmd"].GetString();
  src = document["src"].GetInt();
  src_idx = document["src_idx"].GetInt();
  dest = document["dest"].GetInt();
}

const std::string Command::get_method() const {
  return method;
}

const size_t Command::get_src() const {
  return src;
}

const size_t Command::get_src_idx() const {
  return src_idx;
}

const size_t Command::get_dest() const {
  return dest;
}

Command::~Command() {}
