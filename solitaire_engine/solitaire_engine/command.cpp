#include "stdafx.h"
#include "command.h"

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

const std::string Command::get_method() {
  return method;
}

const int Command::get_src() {
  return src;
}

const int Command::get_src_idx() {
  return src_idx;
}

const int Command::get_dest() {
  return dest;
}


Command::~Command() {
}
