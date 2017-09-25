#pragma once
#include "constants.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Response
{
private:
  Response();
  ~Response();
public:
  static std::string make_response(const char* text);
};
